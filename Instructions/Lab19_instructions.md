# Lab 19: Generic Programming with Templates

## Getting Started

> **Important:** This lab builds on your work from Lab 18.
> 
> Continue working in your **existing repository** from Lab 18. Do NOT create a new repository.
> 
> Your Lab 18 submission becomes the starting point for this lab.

---

## Objective

- Learn function templates in C++
- Write type-independent code
- Create reusable mathematical utilities
- Implement a "what-if" grade calculator

---

## Introduction

What if you need a function that works with `int`, `float`, and `double`? You could write three separate functions, or you could use **templates**! Templates let you write code once that works with any data type.

In this lab, you'll create template functions for grade calculations and add a "what-if" calculator feature.

---

## New Concepts

### Function Template Syntax

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Usage
int x = add(3, 4);        // T = int
double y = add(3.5, 2.1); // T = double
```

### Templates with Vectors

```cpp
template <typename T>
T findMax(const std::vector<T>& vec) {
    T max = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] > max) max = vec[i];
    }
    return max;
}
```

### Key Points

| Concept | Description |
|---------|-------------|
| `template <typename T>` | Declares a template with type parameter T |
| `T` | Placeholder that gets replaced with actual type |
| Type deduction | Compiler figures out T from arguments |
| Header-only | Templates must be in header files |

---

## Your Task

### Step 1: Create MathHelper.h

```cpp
#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <vector>
#include <stdexcept>

namespace MathHelper {

    // Calculate sum of vector elements
    template <typename T>
    T sum(const std::vector<T>& values) {
        T total = T();
        for (size_t i = 0; i < values.size(); ++i) {
            total += values[i];
        }
        return total;
    }

    // Calculate average of vector elements
    template <typename T>
    double average(const std::vector<T>& values) {
        if (values.empty()) return 0.0;
        return static_cast<double>(sum(values)) / values.size();
    }

    // Find minimum value
    template <typename T>
    T minimum(const std::vector<T>& values) {
        if (values.empty()) throw std::runtime_error("Empty vector");
        T min = values[0];
        for (size_t i = 1; i < values.size(); ++i) {
            if (values[i] < min) min = values[i];
        }
        return min;
    }

    // Find maximum value
    template <typename T>
    T maximum(const std::vector<T>& values) {
        if (values.empty()) throw std::runtime_error("Empty vector");
        T max = values[0];
        for (size_t i = 1; i < values.size(); ++i) {
            if (values[i] > max) max = values[i];
        }
        return max;
    }

    // Count values above threshold
    template <typename T>
    int countAbove(const std::vector<T>& values, T threshold) {
        int count = 0;
        for (size_t i = 0; i < values.size(); ++i) {
            if (values[i] > threshold) count++;
        }
        return count;
    }

    // Calculate percentage
    template <typename T>
    double percentage(T part, T whole) {
        if (whole == T()) return 0.0;
        return (static_cast<double>(part) / whole) * 100.0;
    }

    // Clamp value to range
    template <typename T>
    T clamp(T value, T min, T max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

}  // namespace MathHelper

#endif
```

### Step 2: Include the Header

```cpp
#include "MathHelper.h"
```

### Step 3: Update Statistics Function

```cpp
void viewStatistics(const std::vector<GradedItem*>& items) {
    displayHeader("STATISTICS");
    
    if (items.empty()) {
        std::cout << "No items to analyze.\n";
        return;
    }
    
    // Extract percentages into a vector
    std::vector<float> percentages;
    for (size_t i = 0; i < items.size(); ++i) {
        percentages.push_back(items[i]->getPercentage());
    }
    
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Total Items:    " << items.size() << '\n';
    std::cout << "Average Score:  " << MathHelper::average(percentages) << "%\n";
    std::cout << "Highest Score:  " << MathHelper::maximum(percentages) << "%\n";
    std::cout << "Lowest Score:   " << MathHelper::minimum(percentages) << "%\n";
    
    std::cout << "\nGrade Distribution:\n";
    std::cout << "  A (90%+):     " << MathHelper::countAbove(percentages, 89.9f) << '\n';
    std::cout << "  B (80-89%):   " << MathHelper::countAbove(percentages, 79.9f) - 
                                       MathHelper::countAbove(percentages, 89.9f) << '\n';
    std::cout << "  C (70-79%):   " << MathHelper::countAbove(percentages, 69.9f) - 
                                       MathHelper::countAbove(percentages, 79.9f) << '\n';
}
```

### Step 4: Add What-If Calculator

Add a new menu option and function:

```cpp
void whatIfCalculator(const std::vector<GradedItem*>& items,
                      float A_pct, float B_pct, float C_pct, float D_pct) {
    displayHeader("WHAT-IF CALCULATOR");
    
    // Calculate current category averages
    std::vector<float> hwPcts, quizPcts, examPcts;
    
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i]->getCategory() == "Homework") {
            hwPcts.push_back(items[i]->getPercentage());
        } else if (items[i]->getCategory() == "Quiz") {
            quizPcts.push_back(items[i]->getPercentage());
        } else if (items[i]->getCategory() == "Exam") {
            examPcts.push_back(items[i]->getPercentage());
        }
    }
    
    float hwAvg = hwPcts.empty() ? 0 : MathHelper::average(hwPcts);
    float quizAvg = quizPcts.empty() ? 0 : MathHelper::average(quizPcts);
    float examAvg = examPcts.empty() ? 0 : MathHelper::average(examPcts);
    
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Current Averages:\n";
    std::cout << "  Homework: " << hwAvg << "%\n";
    std::cout << "  Quizzes:  " << quizAvg << "%\n";
    std::cout << "  Exams:    " << examAvg << "%\n\n";
    
    std::cout << "Enter projected averages to see your potential grade:\n\n";
    
    float projHw = InputHelper::getPercentage("Projected Homework avg: ");
    float projQuiz = InputHelper::getPercentage("Projected Quiz avg: ");
    float projExam = InputHelper::getPercentage("Projected Exam avg: ");
    
    float projected = (projHw * 0.20) + (projQuiz * 0.30) + (projExam * 0.50);
    projected = MathHelper::clamp(projected, 0.0f, 100.0f);
    
    char grade;
    if (projected >= A_pct) grade = 'A';
    else if (projected >= B_pct) grade = 'B';
    else if (projected >= C_pct) grade = 'C';
    else if (projected >= D_pct) grade = 'D';
    else grade = 'F';
    
    std::cout << "\n=============================\n";
    std::cout << "Projected Final: " << projected << "% = " << grade << '\n';
    std::cout << "=============================\n";
}
```

### Step 5: Update Menu

Add option 6 for What-If Calculator:

```cpp
std::cout << "6. What-If Calculator\n";
```

---

## Expected Output

```
==================================================
  WHAT-IF CALCULATOR
==================================================
Current Averages:
  Homework: 92.5%
  Quizzes:  85.0%
  Exams:    78.0%

Enter projected averages to see your potential grade:

Projected Homework avg: 90
Projected Quiz avg: 85
Projected Exam avg: 90

=============================
Projected Final: 88.5% = B
=============================
```

---

## Why Templates?

| Without Templates | With Templates |
|-------------------|----------------|
| `sumInt()`, `sumFloat()`, `sumDouble()` | `sum<T>()` works for all |
| Code duplication | Write once, use everywhere |
| Hard to maintain | Single source of truth |

---

## Submission

When your program uses templates and includes a what-if calculator, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Created function templates
- ✅ Wrote type-independent utility functions
- ✅ Implemented a what-if grade projector
- ✅ Used templates with vectors

---

## Next Steps

In **Lab 20**, you'll learn lambdas and STL algorithms for powerful data processing!
