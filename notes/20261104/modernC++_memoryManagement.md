# A Guide to Modern C++ Memory Management

In modern C++ (C++11 and later), raw pointers (`*`) and manual memory management (`new` and `delete`) are largely replaced by **smart pointers**. Smart pointers are wrappers around raw pointers that automatically manage memory deallocation, ensuring your programs are free from memory leaks and dangling pointers.

The `<memory>` library provides three main types of smart pointers:

1. **`std::unique_ptr`**: Exclusively owns the object it points to. No two `unique_ptr`s can point to the same object.

2. **`std::shared_ptr`**: Shares ownership of an object with other `shared_ptr`s. The object is destroyed only when the last `shared_ptr` is destroyed.

3. **`std::weak_ptr`**: Observes an object managed by a `shared_ptr` without increasing its reference count. Used to break circular dependencies.

## 1. std::unique_ptr

A `unique_ptr` implements **strict, exclusive ownership**. It is the default smart pointer you should reach for. When a `unique_ptr` goes out of scope, the memory it manages is immediately and automatically freed. Because it is strictly unique, you cannot copy a `unique_ptr`—you can only *move* it, transferring ownership from one pointer to another.

### Example: Exclusive Ownership

```cpp
#include <iostream>
#include <memory>
#include <array>
#include <string>

using namespace std;

class Card {
public:
    string name;
    Card(string n) : name(n) { cout << "Card created: " << name << endl; }
    ~Card() { cout << "Card destroyed: " << name << endl; }
    void play() { cout << "Playing " << name << endl; }
};

void playHand() {
    // make_unique safely allocates the memory and wraps it in a unique_ptr
    array<unique_ptr<Card>, 2> hand = {
        make_unique<Card>("Ace of Spades"),
        make_unique<Card>("King of Hearts")
    };

    for (const auto& card : hand) {
        card->play();
    }
    // No delete needed. Memory is freed as 'hand' goes out of scope.
}
```

### Alternative Creation: Wrapping `new`

Before C++14 introduced `std::make_unique`, the only way to create a smart pointer was by explicitly calling `new` and passing the resulting raw pointer into the smart pointer's constructor. 

```cpp
// The older, explicit way to create a unique_ptr
unique_ptr<Card> joker(new Card("Joker")); 

// The older, explicit way to create a shared_ptr
shared_ptr<Card> wildCard(new Card("Wild Card"));
```

### Why Prefer `make_unique` and `make_shared`?

While wrapping `new` still works, modern C++ guidelines strongly advise always using `std::make_unique` and `std::make_shared` instead. Here is why:

1. **Exception Safety (No Memory Leaks):** 
   If you write a function call like `processCard(unique_ptr<Card>(new Card("Ace")), dangerousFunction());`, the compiler is allowed to allocate the memory for `new Card` first, then evaluate `dangerousFunction()` *before* constructing the `unique_ptr`. If `dangerousFunction()` throws an exception, the raw `Card` memory is permanently leaked. `std::make_unique` prevents this by bundling the allocation and the smart pointer construction into one indivisible step.
2. **Performance (For `shared_ptr`):** 
   A `shared_ptr` needs to store both the object and a "control block" (the reference counter). If you use `shared_ptr<Card>(new Card("Ace"))`, the program performs **two** separate memory allocations (one for the card, one for the control block). If you use `std::make_shared<Card>("Ace")`, the program does a **single** memory allocation that fits both the card and the counter side-by-side, which is much faster and more cache-friendly.
3. **Readability:** 
   You do not have to repeat the type name twice (e.g., `unique_ptr<Card>(new Card(...))` vs `make_unique<Card>(...)`).

### What Doesn't Work and Why

You **cannot copy** a `unique_ptr`. The compiler explicitly forbids it to prevent two pointers from thinking they both exclusively own (and should both delete) the same memory block.

```cpp
unique_ptr<Card> card1 = make_unique<Card>("Queen of Hearts");

// ERROR: Call to implicitly-deleted copy constructor
// unique_ptr<Card> card2 = card1; 

// FIX: You must transfer ownership using std::move
unique_ptr<Card> card3 = std::move(card1); 
// card1 is now null, card3 owns the memory
```

## 2. std::shared_ptr

A `shared_ptr` uses **reference counting**. Every time you copy a `shared_ptr`, an internal counter increments. Every time one goes out of scope, the counter decrements. When the counter reaches `0`, the underlying memory is deleted.

### Example: Shared Ownership (Music Playlists)

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class Song {
public:
    string title;
    Song(string t) : title(t) { cout << "Song allocated: " << title << endl; }
    ~Song() { cout << "Song freed: " << title << endl; }
};

class Playlist {
public:
    string name;
    vector<shared_ptr<Song>> songs;
    Playlist(string n) : name(n) {}
    void addSong(shared_ptr<Song> song) { songs.push_back(song); }
};

void manageMusic() {
    // Reference count: 1
    shared_ptr<Song> mySong = make_shared<Song>("Bohemian Rhapsody");
    
    {
        Playlist favorites("Favorites");
        favorites.addSong(mySong); // Reference count: 2
        
        Playlist workout("Workout");
        workout.addSong(mySong); // Reference count: 3
    } // Playlists destroyed. Reference count drops to 1.

} // mySong destroyed. Reference count: 0. Memory freed.
```

### What Doesn't Work and Why

You should **never initialize two separate `shared_ptr`s from the same raw pointer**. They will not share the same reference counter. They will both start a counter at `1`, and both will attempt to delete the same memory when they expire, causing a "double free" crash.

```cpp
Song* rawSong = new Song("Danger Zone");

// sharedA thinks it is the sole owner (count = 1)
shared_ptr<Song> sharedA(rawSong); 

// ERROR IN LOGIC: sharedB ALSO thinks it is the sole owner (count = 1)
// shared_ptr<Song> sharedB(rawSong); 

// When they go out of scope, both try to delete rawSong. CRASH.
// FIX: Always use make_shared<Song>("Danger Zone"), and copy the shared_ptr itself.
```

## 3. std::weak_ptr

When objects need to reference each other, a common issue is **cyclic dependencies**. For example, if a `Team` owns its `Player`s (using `shared_ptr`), but a `Player` also owns its `Team` (using another `shared_ptr`), their reference counts will never reach `0`. They keep each other alive indefinitely, creating a memory leak.

A `weak_ptr` solves this. It observes an object without claiming ownership. In this example, the `Team` owns the `Player`, but the `Player` only *watches* the `Team`.

### Example: Breaking Cyclic Dependencies (Teams and Players)

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Team; // Forward declaration so Player knows Team exists

class Player {
public:
    string name;
    
    // The Player watches the Team, but does NOT own it. 
    // This prevents the Player and Team from keeping each other alive forever.
    weak_ptr<Team> myTeam; 

    Player(string n) : name(n) { cout << "  [+] Player created: " << name << endl; }
    ~Player() { cout << "  [-] Player destroyed: " << name << endl; }

    void checkStatus(); // Defined after Team
};

class Team {
public:
    string name;
    
    // The Team exclusively shares ownership of its Players
    vector<shared_ptr<Player>> roster; 

    Team(string n) : name(n) { cout << "  [+] Team created: " << name << endl; }
    ~Team() { cout << "  [-] Team destroyed: " << name << endl; }

    void draftPlayer(shared_ptr<Player> p) {
        roster.push_back(p);
    }
};

void Player::checkStatus() {
    // Because a weak_ptr doesn't own the memory, the Team might have been deleted.
    // We must call .lock() to safely check if it still exists before using it.
    if (shared_ptr<Team> team = myTeam.lock()) {
        cout << name << " is currently on: " << team->name << endl;
    } else {
        cout << name << " is a free agent! Their team disbanded." << endl;
    }
}

void playSeason() {
    // 1. Create a player (Reference count = 1)
    shared_ptr<Player> p1 = make_shared<Player>("Alex");

    {
        // 2. Create a team in a temporary local scope
        shared_ptr<Team> redTeam = make_shared<Team>("Red Dragons");
        
        redTeam->draftPlayer(p1); // Team claims ownership of Alex (Alex's count = 2)
        p1->myTeam = redTeam;     // Alex watches the Team (Team's count stays 1!)
        
        p1->checkStatus();
        
        cout << "The season ends. The team is disbanding...\n";
    } // redTeam goes out of scope here. Its count drops to 0, so it is destroyed!

    // 3. The player still exists, but when they check their team, they see it's gone
    p1->checkStatus();
    
} // p1 goes out of scope here and is safely destroyed.
```

### What Doesn't Work and Why

You **cannot dereference a `weak_ptr` directly** (no `->` or `*` operators). Because a `weak_ptr` does not own the memory, the object might have been deleted out from under it.

```cpp
weak_ptr<Team> watchingTeam = myTeam;

// ERROR: No overloaded '->' operator for weak_ptr
// cout << watchingTeam->name;

// FIX: You must call .lock() to check if it still exists and temporarily own it.
if (shared_ptr<Team> tempTeam = watchingTeam.lock()) {
    cout << tempTeam->name;
}
```

## 4. Legacy C++: Manual Memory Management

Before C++11, developers had to manually allocate memory using `new` and explicitly deallocate it using `delete`. For arrays, `new[]` and `delete[]` were required.

This approach is highly discouraged today because any early return, exception, or simple oversight results in permanent memory leaks.

### Example: Direct `new`, `delete`, and `delete[]`

```cpp
#include <iostream>
#include <string>

using namespace std;

class LegacyBuffer {
public:
    int* data;
    size_t size;

    LegacyBuffer(size_t s) : size(s) {
        // 1. Array Allocation: Requires tracking the exact size manually
        data = new int[size]; 
        cout << "Legacy array of size " << size << " allocated.\n";
    }

    ~LegacyBuffer() {
        // 2. Array Deallocation: MUST use delete[] for arrays
        delete[] data;
        cout << "Legacy array deleted.\n";
    }
};

void runLegacySystem() {
    // Single Object Allocation
    LegacyBuffer* myBuffer = new LegacyBuffer(100);

    // ... Do work with myBuffer ...

    // Pitfall 1: What if an exception is thrown here? 
    // myBuffer is never deleted. Memory leak!

    // Single Object Deallocation: MUST use standard delete
    delete myBuffer; 
}
```

### Legacy Pitfalls:

1. **The Array Deallocation Mismatch:** If you allocate with `new[]` (e.g., `int* arr = new int[10];`) but deallocate with standard `delete` (e.g., `delete arr;`), it results in **undefined behavior**. Usually, it only destroys the first element of the array and leaks the rest.

2. **The Exception Trap:** If an error is thrown between `new` and `delete`, the `delete` is skipped, permanently leaking the memory for the remainder of the program's lifecycle. Smart pointers fix this via RAII (Resource Acquisition Is Initialization), automatically cleaning up during stack unwinding.