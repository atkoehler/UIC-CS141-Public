# Frequency Counter Live Lecture Program

Implementation of a counting program that counts the frequency of various characteristics within a data set of strings. Data is acquired through file input and stored only when it meets specific conditions.

## Key Concepts

- strings & vectors (and associated member functions)
- switch statements
- file input
- user defined functions

## Group Tasks from Lecture

* Step 1: Generate Data Algorithm & Questions
* Step 2: isvowel helper function implementation
* Step 3: implement one of the counting functions based on group number


# Program Description

This program was implemented in steps across groups and the a working solution implemented during the live lecture session. Functionality and comments were finalized after lecture. For example, only one data validity condition existed during the live lecture.


## Pre Validity Check Manipulations

All non alphabetic ending characters should be trimmed, and then the word evaluated to meet other conditions before storage


## Valid Data Conditions

We will only save data that meets the following conditions, but we will output any data that does not meet the conditions.
- Words must be 5 characters
- Words must be all lowercase alphabetic letters
- All stored words must be unique


## Input / Data Entry

We will read all input via file input. The user should specify the filename.


## Full Program Menu Options

Implement a program with the following menu options and use appropriate output and inputs.

1. Load Data
2. Clear Data
3. Count Vowels
4. Count Non-Vowels
5. Count words that start with vowels