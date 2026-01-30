# Lab 14: Creating Custom Objects

## Getting Started

> **Important:** This lab builds on your work from Lab 13.
> 
> Continue working in your **existing repository** from Lab 13. Do NOT create a new repository.
> 
> Your Lab 13 submission becomes the starting point for this lab.

---

## Objective

- Learn to define custom classes in C++
- Create an `Assignment` class with member variables and methods
- Use objects to store assignment data
- Understand constructors and member functions

---

## Introduction

Currently, your grade calculator only stores numeric scores. But what if you want to track assignment names, points possible, and points earned separately? In this lab, you'll create a custom `Assignment` class to organize this data.

Object-Oriented Programming (OOP) is a fundamental paradigm in C++ that lets you model real-world concepts as code.

---

## New Concepts

### Class Definition

```cpp
class Assignment {
public:
    std::string name;
    float points_earned;
    float points_possible;
    
    // Constructor
    Assignment(std::string n, float earned, float possible) {
        name = n;
        points_earned = earned;
        points_possible = possible;
    }
    
    // Member function
    float getPercentage() {
        return (points_earned / points_possible) * 100;
    }
};
```

### Using Objects

```cpp
Assignment hw1("Homework 1", 95, 100);
std::cout << hw1.name << ": " << hw1.getPercentage() << "%\n";
```

### Key Terminology

| Term | Meaning |
|------|---------|
| **Class** | A blueprint for creating objects |
| **Object** | An instance of a class |
| **Member variable** | Data stored in the object |
| **Member function** | A function that belongs to the class |
| **Constructor** | Special function that initializes the object |

---

## Your Task

### Step 1: Create Assignment.h

Create a new file called `Assignment.h`:

```cpp
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include <iostream>

class Assignment {
public:
    std::string name;
    float points_earned;
    float points_possible;
    
    // Constructor
    Assignment(std::string n, float earned, float possible) {
        name = n;
        points_earned = earned;
        points_possible = possible;
    }
    
    // Default constructor (needed for vectors)
    Assignment() {
        name = "";
        points_earned = 0;
        points_possible = 0;
    }
    
    // Calculate percentage
    float getPercentage() {
        if (points_possible == 0) return 0;
        return (points_earned / points_possible) * 100;
    }
    
    // Display assignment info
    void display() {
        std::cout << name << ": " 
                  << points_earned << "/" << points_possible 
                  << " (" << getPercentage() << "%)\n";
    }
};

#endif
```

### Step 2: Include the Header

In `main.cpp`, add:

```cpp
#include "Assignment.h"
```

### Step 3: Change Vector Type

Replace your `vector<float>` with:

```cpp
std::vector<Assignment> assignments;
```

### Step 4: Update Score Input

Change the input loop to collect assignment details:

```cpp
std::string assignmentName;
float pointsPossible, pointsEarned;

std::cout << "Assignment name (or 'done' to finish): ";
std::getline(std::cin, assignmentName);

if (assignmentName == "done") {
    break;
}

std::cout << "Points possible: ";
std::cin >> pointsPossible;

std::cout << "Points earned: ";
std::cin >> pointsEarned;
std::cin.ignore();  // Clear the newline

Assignment newAssignment(assignmentName, pointsEarned, pointsPossible);
assignments.push_back(newAssignment);
```

### Step 5: Update Display

```cpp
std::cout << "\nAll Assignments:\n";
std::cout << "================\n";
for (size_t i = 0; i < assignments.size(); ++i) {
    assignments[i].display();
}
```

### Step 6: Update Total Calculation

```cpp
float total_earned = 0;
float total_possible = 0;

for (size_t i = 0; i < assignments.size(); ++i) {
    total_earned += assignments[i].points_earned;
    total_possible += assignments[i].points_possible;
}

float overall_percentage = (total_earned / total_possible) * 100;
```

---

## Expected Output

```
Assignment name (or 'done' to finish): Homework 1
Points possible: 100
Points earned: 95

Assignment name (or 'done' to finish): Quiz 1
Points possible: 50
Points earned: 42

Assignment name (or 'done' to finish): done

All Assignments:
================
Homework 1: 95/100 (95%)
Quiz 1: 42/50 (84%)

Total: 137/150 (91.33%)
Final Grade: A
```

---

## Submission

When your program uses the `Assignment` class correctly, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Created a custom class with member variables
- ✅ Implemented constructors and member functions
- ✅ Used a vector of objects
- ✅ Organized related data together

---

## Next Steps

In **Lab 15**, you'll refactor the `Assignment` class to separate the header (.h) from the implementation (.cpp)!
