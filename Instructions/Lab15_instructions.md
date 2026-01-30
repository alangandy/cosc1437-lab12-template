# Lab 15: Fine-Tuning Objects

## Getting Started

> **Important:** This lab builds on your work from Lab 14.
> 
> Continue working in your **existing repository** from Lab 14. Do NOT create a new repository.
> 
> Your Lab 14 submission becomes the starting point for this lab.

---

## Objective

- Separate class declarations from implementations
- Learn about encapsulation with private members
- Implement getter and setter methods
- Use `const` correctness for member functions

---

## Introduction

In Lab 14, you created the `Assignment` class with everything in the header file. This works for small classes, but as classes grow larger, it's better practice to separate the **declaration** (in `.h`) from the **implementation** (in `.cpp`).

You'll also learn about **encapsulation** - hiding internal data and providing controlled access through methods.

---

## New Concepts

### Separating Declaration and Implementation

**Header file (.h)** - Contains declarations only:
```cpp
class Assignment {
public:
    void display() const;  // Declaration only
};
```

**Implementation file (.cpp)** - Contains the actual code:
```cpp
void Assignment::display() const {
    // Implementation here
}
```

### The Scope Resolution Operator `::`

When implementing methods outside the class, use `ClassName::methodName`:

```cpp
float Assignment::getPercentage() const {
    return (points_earned / points_possible) * 100;
}
```

### Encapsulation with Private Members

```cpp
class Assignment {
private:
    std::string name;        // Can't be accessed directly
    float points_earned;
    float points_possible;
    
public:
    std::string getName() const { return name; }  // Getter
    void setName(const std::string& n) { name = n; }  // Setter
};
```

### Const Member Functions

A `const` method promises not to modify the object:

```cpp
float getPercentage() const;  // Won't change any member variables
```

---

## Your Task

### Step 1: Update Assignment.h

Change your header to contain only declarations:

```cpp
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>

class Assignment {
private:
    std::string name;
    float points_earned;
    float points_possible;

public:
    // Constructors
    Assignment();
    Assignment(const std::string& n, float earned, float possible);
    
    // Getters
    std::string getName() const;
    float getPointsEarned() const;
    float getPointsPossible() const;
    float getPercentage() const;
    
    // Setters
    void setName(const std::string& n);
    void setPointsEarned(float earned);
    void setPointsPossible(float possible);
    
    // Display
    void display() const;
};

#endif
```

### Step 2: Create Assignment.cpp

Create a new file with the implementations:

```cpp
#include "Assignment.h"
#include <iostream>

// Default constructor
Assignment::Assignment() {
    name = "";
    points_earned = 0;
    points_possible = 0;
}

// Parameterized constructor
Assignment::Assignment(const std::string& n, float earned, float possible) {
    name = n;
    points_earned = earned;
    points_possible = possible;
}

// Getters
std::string Assignment::getName() const {
    return name;
}

float Assignment::getPointsEarned() const {
    return points_earned;
}

float Assignment::getPointsPossible() const {
    return points_possible;
}

float Assignment::getPercentage() const {
    if (points_possible == 0) return 0;
    return (points_earned / points_possible) * 100;
}

// Setters
void Assignment::setName(const std::string& n) {
    name = n;
}

void Assignment::setPointsEarned(float earned) {
    if (earned >= 0) {
        points_earned = earned;
    }
}

void Assignment::setPointsPossible(float possible) {
    if (possible > 0) {
        points_possible = possible;
    }
}

// Display
void Assignment::display() const {
    std::cout << name << ": " 
              << points_earned << "/" << points_possible 
              << " (" << getPercentage() << "%)\n";
}
```

### Step 3: Update main.cpp

Since members are now private, use getters in your calculations:

```cpp
for (size_t i = 0; i < assignments.size(); ++i) {
    total_earned += assignments[i].getPointsEarned();
    total_possible += assignments[i].getPointsPossible();
}
```

### Step 4: Update Compilation

You now need to compile both `.cpp` files:

```bash
g++ -std=c++17 -o grade_calc main.cpp greeting.cpp Assignment.cpp
```

---

## Why Encapsulation?

| Without Encapsulation | With Encapsulation |
|-----------------------|-------------------|
| `assignment.points_earned = -100;` (Allowed!) | `assignment.setPointsEarned(-100);` (Can validate!) |
| Anyone can break the data | Data is protected |
| Hard to change internal structure | Can change internals without breaking code |

---

## Submission

When your program compiles with separate files and uses getters/setters, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Separated header declarations from implementations
- ✅ Used the scope resolution operator `::`
- ✅ Made member variables private
- ✅ Created getter and setter methods
- ✅ Used `const` for methods that don't modify data

---

## Next Steps

In **Lab 16**, you'll create a menu-driven interface with professional formatting!
