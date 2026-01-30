# Lab 16: Building a Menu-Driven Interface

## Getting Started

> **Important:** This lab builds on your work from Lab 15.
> 
> Continue working in your **existing repository** from Lab 15. Do NOT create a new repository.
> 
> Your Lab 15 submission becomes the starting point for this lab.

---

## Objective

- Create a professional menu system using loops
- Use `<iomanip>` for formatted output
- Organize code into helper functions
- Improve user experience with clear prompts

---

## Introduction

Your grade calculator has grown into a capable application! But the user interface is still basic - all the steps happen in sequence. In this lab, you'll transform it into a **menu-driven** application where users can choose what to do next.

You'll also learn to use `<iomanip>` to create nicely formatted output that looks professional.

---

## New Concepts

### The iomanip Library

```cpp
#include <iomanip>

// Set width for next output
std::cout << std::setw(10) << "Name";

// Set decimal precision
std::cout << std::fixed << std::setprecision(1) << 85.6667;  // Prints 85.7

// Alignment
std::cout << std::left << std::setw(20) << "Left aligned";
std::cout << std::right << std::setw(10) << "Right";
```

### Common iomanip Manipulators

| Manipulator | Purpose | Example |
|-------------|---------|---------|
| `setw(n)` | Set field width | `setw(10)` |
| `setprecision(n)` | Decimal places | `setprecision(2)` |
| `fixed` | Fixed decimal notation | `fixed` |
| `left` / `right` | Alignment | `left` |
| `setfill(c)` | Fill character | `setfill('.')` |

### Menu Pattern

```cpp
int choice = 0;
do {
    displayMenu();
    std::cin >> choice;
    
    switch (choice) {
        case 1:
            doOption1();
            break;
        case 2:
            doOption2();
            break;
        case 0:
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
    }
} while (choice != 0);
```

---

## Your Task

### Step 1: Add iomanip Include

```cpp
#include <iomanip>
```

### Step 2: Create Display Helper Functions

```cpp
void displayHeader(const std::string& title) {
    std::cout << "\n";
    std::cout << std::string(50, '=') << '\n';
    std::cout << "  " << title << '\n';
    std::cout << std::string(50, '=') << '\n';
}

void displaySeparator() {
    std::cout << std::string(50, '-') << '\n';
}
```

### Step 3: Create the Menu Display Function

```cpp
void displayMenu() {
    displayHeader("GRADE CALCULATOR - MAIN MENU");
    std::cout << "1. Set Grading Scheme\n";
    std::cout << "2. Add Assignment\n";
    std::cout << "3. View All Assignments\n";
    std::cout << "4. View Statistics\n";
    std::cout << "5. Calculate Final Grade\n";
    std::cout << "0. Exit\n";
    displaySeparator();
}
```

### Step 4: Create Formatted View Function

```cpp
void viewAssignments(const std::vector<Assignment>& assignments) {
    displayHeader("ALL ASSIGNMENTS");
    
    if (assignments.empty()) {
        std::cout << "No assignments entered yet.\n";
        return;
    }
    
    // Header row
    std::cout << std::left << std::setw(25) << "Name"
              << std::right << std::setw(10) << "Earned"
              << std::setw(10) << "Possible"
              << std::setw(10) << "Percent" << '\n';
    displaySeparator();
    
    // Data rows
    std::cout << std::fixed << std::setprecision(1);
    for (size_t i = 0; i < assignments.size(); ++i) {
        std::cout << std::left << std::setw(25) << assignments[i].getName()
                  << std::right << std::setw(10) << assignments[i].getPointsEarned()
                  << std::setw(10) << assignments[i].getPointsPossible()
                  << std::setw(9) << assignments[i].getPercentage() << "%\n";
    }
}
```

### Step 5: Implement the Main Menu Loop

```cpp
int main() {
    // Variable declarations
    std::vector<Assignment> assignments;
    int total_points = 1000;
    float A_pct = 90, B_pct = 80, C_pct = 70, D_pct = 60;
    bool scheme_set = false;
    
    displayGreeting();
    
    int choice = 0;
    do {
        displayMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                setGradingScheme(total_points, A_pct, B_pct, C_pct, D_pct);
                scheme_set = true;
                break;
            case 2:
                if (!scheme_set) {
                    std::cout << "Please set grading scheme first!\n";
                } else {
                    addAssignment(assignments);
                }
                break;
            case 3:
                viewAssignments(assignments);
                break;
            case 4:
                viewStatistics(assignments);
                break;
            case 5:
                calculateFinalGrade(assignments, A_pct, B_pct, C_pct, D_pct);
                break;
            case 0:
                displayHeader("GOODBYE");
                std::cout << "Thank you for using Grade Calculator!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    
    return 0;
}
```

---

## Expected Output

```
==================================================
  GRADE CALCULATOR - MAIN MENU
==================================================
1. Set Grading Scheme
2. Add Assignment
3. View All Assignments
4. View Statistics
5. Calculate Final Grade
0. Exit
--------------------------------------------------
Enter choice: 3

==================================================
  ALL ASSIGNMENTS
==================================================
Name                      Earned  Possible   Percent
--------------------------------------------------
Homework 1                  95.0     100.0     95.0%
Quiz 1                      42.0      50.0     84.0%
Midterm Exam                85.0     100.0     85.0%
```

---

## Submission

When your program has a working menu system with formatted output, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Created a menu-driven interface
- ✅ Used `<iomanip>` for professional formatting
- ✅ Organized code into reusable helper functions
- ✅ Implemented a main loop with switch statement

---

## Next Steps

In **Lab 17**, you'll add inheritance to create different types of graded items with weighted categories!
