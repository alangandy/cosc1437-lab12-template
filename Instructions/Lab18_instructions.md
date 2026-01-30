# Lab 18: Input Validation and Error Handling

## Getting Started

> **Important:** This lab builds on your work from Lab 17.
> 
> Continue working in your **existing repository** from Lab 17. Do NOT create a new repository.
> 
> Your Lab 17 submission becomes the starting point for this lab.

---

## Objective

- Learn to validate user input in C++
- Handle input stream errors gracefully
- Create reusable input validation functions
- Prevent program crashes from bad input

---

## Introduction

What happens when a user types "abc" when your program expects a number? The program might crash, enter an infinite loop, or produce garbage results. In this lab, you'll make your grade calculator **robust** by validating all user input.

Professional applications never trust user input - they always validate!

---

## New Concepts

### Input Stream States

```cpp
std::cin >> number;

if (std::cin.fail()) {
    // Input failed (wrong type entered)
    std::cin.clear();              // Clear error flag
    std::cin.ignore(1000, '\n');   // Discard bad input
}
```

### Input Validation Loop Pattern

```cpp
int getValidInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Error: Please enter a number.\n";
        } else if (value < min || value > max) {
            std::cout << "Error: Must be between " << min << " and " << max << ".\n";
        } else {
            std::cin.ignore(1000, '\n');
            return value;
        }
    }
}
```

### Key Functions

| Function | Purpose |
|----------|---------|
| `cin.fail()` | Returns true if last input failed |
| `cin.clear()` | Clears error flags |
| `cin.ignore(n, delim)` | Discards n chars or until delimiter |

---

## Your Task

### Step 1: Create InputHelper.h

```cpp
#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <iostream>
#include <string>
#include <limits>

namespace InputHelper {

    inline void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    inline int getInt(const std::string& prompt, int min, int max) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            
            if (std::cin.fail()) {
                clearInput();
                std::cout << "  Error: Please enter a valid number.\n";
            } else if (value < min || value > max) {
                clearInput();
                std::cout << "  Error: Must be between " << min << " and " << max << ".\n";
            } else {
                clearInput();
                return value;
            }
        }
    }

    inline float getFloat(const std::string& prompt, float min, float max) {
        float value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            
            if (std::cin.fail()) {
                clearInput();
                std::cout << "  Error: Please enter a valid number.\n";
            } else if (value < min || value > max) {
                clearInput();
                std::cout << "  Error: Must be between " << min << " and " << max << ".\n";
            } else {
                clearInput();
                return value;
            }
        }
    }

    inline float getPercentage(const std::string& prompt) {
        return getFloat(prompt, 0.0f, 100.0f);
    }

    inline std::string getString(const std::string& prompt) {
        std::string value;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, value);
            
            if (value.empty()) {
                std::cout << "  Error: Please enter a value.\n";
            } else {
                return value;
            }
        }
    }

    inline bool getYesNo(const std::string& prompt) {
        char response;
        while (true) {
            std::cout << prompt << " (y/n): ";
            std::cin >> response;
            clearInput();
            
            if (response == 'y' || response == 'Y') return true;
            if (response == 'n' || response == 'N') return false;
            
            std::cout << "  Error: Please enter 'y' or 'n'.\n";
        }
    }

    inline int getMenuChoice(int min, int max) {
        return getInt("Enter choice: ", min, max);
    }

    inline void pressEnterToContinue() {
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

}  // namespace InputHelper

#endif
```

### Step 2: Include the Header

```cpp
#include "InputHelper.h"
```

### Step 3: Update Grading Scheme Input

```cpp
void setGradingScheme(int& total, float& A, float& B, float& C, float& D) {
    displayHeader("GRADING SCHEME SETUP");
    
    total = InputHelper::getInt("Total points possible (1-10000): ", 1, 10000);
    
    std::cout << "\nEnter minimum percentages (must be in descending order):\n";
    
    A = InputHelper::getPercentage("Minimum % for A: ");
    B = InputHelper::getFloat("Minimum % for B: ", 0, A - 0.1f);
    C = InputHelper::getFloat("Minimum % for C: ", 0, B - 0.1f);
    D = InputHelper::getFloat("Minimum % for D: ", 0, C - 0.1f);
    
    std::cout << "\nGrading scheme saved!\n";
    InputHelper::pressEnterToContinue();
}
```

### Step 4: Update Add Item Function

```cpp
void addGradedItem(std::vector<GradedItem*>& items) {
    displayHeader("ADD GRADED ITEM");
    
    std::cout << "Select category:\n";
    std::cout << "1. Homework (20%)\n";
    std::cout << "2. Quiz (30%)\n";
    std::cout << "3. Exam (50%)\n\n";
    
    int category = InputHelper::getMenuChoice(1, 3);
    
    std::string name = InputHelper::getString("Name: ");
    float possible = InputHelper::getFloat("Points possible: ", 0.1f, 1000.0f);
    float earned = InputHelper::getFloat("Points earned: ", 0.0f, possible);
    
    GradedItem* item = nullptr;
    switch (category) {
        case 1: item = new Homework(name, earned, possible); break;
        case 2: item = new Quiz(name, earned, possible); break;
        case 3: item = new Exam(name, earned, possible); break;
    }
    
    items.push_back(item);
    std::cout << "\nItem added successfully!\n";
    InputHelper::pressEnterToContinue();
}
```

### Step 5: Update Main Menu

```cpp
int choice = 0;
do {
    displayMenu();
    choice = InputHelper::getMenuChoice(0, 6);
    
    switch (choice) {
        // ... cases
        case 0:
            if (InputHelper::getYesNo("Are you sure you want to exit?")) {
                displayHeader("GOODBYE");
                std::cout << "Thank you for using Grade Calculator!\n";
            } else {
                choice = -1;  // Don't exit
            }
            break;
    }
} while (choice != 0);
```

---

## Expected Output

```
Enter total points possible (1-10000): abc
  Error: Please enter a valid number.
Enter total points possible (1-10000): -50
  Error: Must be between 1 and 10000.
Enter total points possible (1-10000): 1000

Minimum % for A: 90
Minimum % for B: 95
  Error: Must be between 0 and 89.9.
Minimum % for B: 80
```

---

## Why Input Validation Matters

| Without Validation | With Validation |
|--------------------|-----------------|
| Program crashes | Graceful error messages |
| Infinite loops | Recovers and re-prompts |
| Invalid data stored | Only valid data accepted |
| Poor user experience | Professional feel |

---

## Submission

When your program handles all invalid input gracefully, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Created reusable input validation functions
- ✅ Handled cin stream errors properly
- ✅ Implemented range validation
- ✅ Made the program robust against bad input

---

## Next Steps

In **Lab 19**, you'll learn function templates to write generic, reusable code!
