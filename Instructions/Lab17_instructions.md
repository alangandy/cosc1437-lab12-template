# Lab 17: Inheritance and Weighted Grades

## Getting Started

> **Important:** This lab builds on your work from Lab 16.
> 
> Continue working in your **existing repository** from Lab 16. Do NOT create a new repository.
> 
> Your Lab 16 submission becomes the starting point for this lab.

---

## Objective

- Learn class inheritance in C++
- Create a base class and derived classes
- Implement polymorphism with virtual methods
- Build a weighted grading system

---

## Introduction

Not all assignments are equal! Homework might be worth 20% of your grade, quizzes 30%, and exams 50%. In this lab, you'll use **inheritance** to create different types of graded items, each with its own weight category.

Inheritance is a core OOP concept that lets you create specialized classes from a general base class.

---

## New Concepts

### Inheritance Syntax

```cpp
class Base {
public:
    virtual void speak() { std::cout << "Base speaking\n"; }
};

class Derived : public Base {
public:
    void speak() override { std::cout << "Derived speaking\n"; }
};
```

### Virtual Methods and Polymorphism

```cpp
Base* ptr = new Derived();
ptr->speak();  // Calls Derived::speak() due to virtual
```

### Key Terminology

| Term | Meaning |
|------|---------|
| **Base class** | The parent class being inherited from |
| **Derived class** | The child class that inherits |
| **virtual** | Allows method to be overridden |
| **override** | Explicitly marks an overriding method |
| **Polymorphism** | Using base pointer to call derived methods |

---

## Your Task

### Step 1: Create GradedItem.h (Base Class)

```cpp
#ifndef GRADEDITEM_H
#define GRADEDITEM_H

#include <string>
#include <iostream>

class GradedItem {
protected:
    std::string name;
    float points_earned;
    float points_possible;

public:
    GradedItem() : name(""), points_earned(0), points_possible(0) {}
    
    GradedItem(const std::string& n, float earned, float possible)
        : name(n), points_earned(earned), points_possible(possible) {}
    
    virtual ~GradedItem() {}  // Virtual destructor
    
    // Getters
    std::string getName() const { return name; }
    float getPointsEarned() const { return points_earned; }
    float getPointsPossible() const { return points_possible; }
    
    float getPercentage() const {
        if (points_possible == 0) return 0;
        return (points_earned / points_possible) * 100;
    }
    
    // Virtual methods for derived classes to override
    virtual std::string getCategory() const { return "General"; }
    virtual float getWeight() const { return 1.0; }
    
    virtual void display() const {
        std::cout << getCategory() << " - " << name << ": "
                  << points_earned << "/" << points_possible
                  << " (" << getPercentage() << "%)\n";
    }
};

#endif
```

### Step 2: Create Homework.h

```cpp
#ifndef HOMEWORK_H
#define HOMEWORK_H

#include "GradedItem.h"

class Homework : public GradedItem {
public:
    Homework() : GradedItem() {}
    
    Homework(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}
    
    std::string getCategory() const override { return "Homework"; }
    float getWeight() const override { return 0.20; }  // 20%
};

#endif
```

### Step 3: Create Quiz.h

```cpp
#ifndef QUIZ_H
#define QUIZ_H

#include "GradedItem.h"

class Quiz : public GradedItem {
public:
    Quiz() : GradedItem() {}
    
    Quiz(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}
    
    std::string getCategory() const override { return "Quiz"; }
    float getWeight() const override { return 0.30; }  // 30%
};

#endif
```

### Step 4: Create Exam.h

```cpp
#ifndef EXAM_H
#define EXAM_H

#include "GradedItem.h"

class Exam : public GradedItem {
public:
    Exam() : GradedItem() {}
    
    Exam(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}
    
    std::string getCategory() const override { return "Exam"; }
    float getWeight() const override { return 0.50; }  // 50%
};

#endif
```

### Step 5: Update main.cpp

Include the new headers:

```cpp
#include "GradedItem.h"
#include "Homework.h"
#include "Quiz.h"
#include "Exam.h"
```

Change your vector to store pointers:

```cpp
std::vector<GradedItem*> items;
```

### Step 6: Update Add Item Function

```cpp
void addGradedItem(std::vector<GradedItem*>& items) {
    displayHeader("ADD GRADED ITEM");
    
    std::cout << "Select category:\n";
    std::cout << "1. Homework (20% weight)\n";
    std::cout << "2. Quiz (30% weight)\n";
    std::cout << "3. Exam (50% weight)\n";
    std::cout << "Choice: ";
    
    int category;
    std::cin >> category;
    std::cin.ignore();
    
    std::cout << "Name: ";
    std::string name;
    std::getline(std::cin, name);
    
    std::cout << "Points possible: ";
    float possible;
    std::cin >> possible;
    
    std::cout << "Points earned: ";
    float earned;
    std::cin >> earned;
    
    GradedItem* item = nullptr;
    switch (category) {
        case 1: item = new Homework(name, earned, possible); break;
        case 2: item = new Quiz(name, earned, possible); break;
        case 3: item = new Exam(name, earned, possible); break;
    }
    
    if (item) {
        items.push_back(item);
        std::cout << "Item added!\n";
    }
}
```

### Step 7: Implement Weighted Grade Calculation

```cpp
void calculateWeightedGrade(const std::vector<GradedItem*>& items,
                            float A_pct, float B_pct, float C_pct, float D_pct) {
    displayHeader("WEIGHTED GRADE CALCULATION");
    
    // Calculate average for each category
    float hwTotal = 0, hwCount = 0;
    float quizTotal = 0, quizCount = 0;
    float examTotal = 0, examCount = 0;
    
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i]->getCategory() == "Homework") {
            hwTotal += items[i]->getPercentage();
            hwCount++;
        } else if (items[i]->getCategory() == "Quiz") {
            quizTotal += items[i]->getPercentage();
            quizCount++;
        } else if (items[i]->getCategory() == "Exam") {
            examTotal += items[i]->getPercentage();
            examCount++;
        }
    }
    
    float hwAvg = hwCount > 0 ? hwTotal / hwCount : 0;
    float quizAvg = quizCount > 0 ? quizTotal / quizCount : 0;
    float examAvg = examCount > 0 ? examTotal / examCount : 0;
    
    // Calculate weighted final
    float finalGrade = (hwAvg * 0.20) + (quizAvg * 0.30) + (examAvg * 0.50);
    
    std::cout << "Homework Average:  " << hwAvg << "% (20% weight)\n";
    std::cout << "Quiz Average:      " << quizAvg << "% (30% weight)\n";
    std::cout << "Exam Average:      " << examAvg << "% (50% weight)\n";
    std::cout << "\nFinal Weighted Grade: " << finalGrade << "%\n";
    
    // Determine letter grade
    char grade;
    if (finalGrade >= A_pct) grade = 'A';
    else if (finalGrade >= B_pct) grade = 'B';
    else if (finalGrade >= C_pct) grade = 'C';
    else if (finalGrade >= D_pct) grade = 'D';
    else grade = 'F';
    
    std::cout << "Letter Grade: " << grade << '\n';
}
```

### Step 8: Clean Up Memory

At the end of main():

```cpp
// Clean up dynamically allocated memory
for (size_t i = 0; i < items.size(); ++i) {
    delete items[i];
}
items.clear();
```

---

## Expected Output

```
==================================================
  ADD GRADED ITEM
==================================================
Select category:
1. Homework (20% weight)
2. Quiz (30% weight)
3. Exam (50% weight)
Choice: 3
Name: Midterm
Points possible: 100
Points earned: 85
Item added!

==================================================
  WEIGHTED GRADE CALCULATION
==================================================
Homework Average:  92.5% (20% weight)
Quiz Average:      85.0% (30% weight)
Exam Average:      85.0% (50% weight)

Final Weighted Grade: 86.5%
Letter Grade: B
```

---

## Submission

When your program supports weighted grade categories with inheritance, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Created a base class with virtual methods
- ✅ Implemented derived classes that override methods
- ✅ Used polymorphism with base class pointers
- ✅ Built a weighted grading system

---

## Next Steps

In **Lab 18**, you'll add robust input validation to handle user errors gracefully!
