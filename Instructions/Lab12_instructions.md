# Lab 12: STL Algorithms

## Getting Started

> **Important:** This lab builds on your work from Lab 11.
> 
> Continue working in your **existing repository** from Lab 11. Do NOT create a new repository.
> 
> Your Lab 11 submission becomes the starting point for this lab.

---

## Objective

- Learn to use the `<algorithm>` library
- Find minimum and maximum values with `std::min_element` and `std::max_element`
- Understand iterators and dereferencing

---

## Introduction

In Lab 11, you stored assignment scores in a `std::vector`. Now you'll use the Standard Template Library (STL) algorithms to efficiently find the highest and lowest scores without writing manual loops.

The `<algorithm>` header provides powerful, pre-built functions that work with any container.

---

## New Concepts

### The Algorithm Library

```cpp
#include <algorithm>

std::vector<float> scores = {85.5, 92.0, 78.3, 95.5, 88.0};

// Find minimum
auto minIt = std::min_element(scores.begin(), scores.end());
float lowest = *minIt;  // Dereference iterator

// Find maximum  
auto maxIt = std::max_element(scores.begin(), scores.end());
float highest = *maxIt;
```

### Iterators

| Concept | Description |
|---------|-------------|
| `begin()` | Iterator to first element |
| `end()` | Iterator past last element |
| `*iterator` | Dereference to get value |
| `auto` | Let compiler deduce type |

---

## Your Task

### Step 1: Add the Algorithm Include

At the top of `main.cpp`, add:

```cpp
#include <algorithm>
```

### Step 2: Find Highest and Lowest Scores

After displaying all scores, add code to find and display the extremes:

```cpp
// Display all scores from vector
std::cout << "\nScores Entered\n";
std::cout << "==============\n";
for (size_t i = 0; i < assignment_scores.size(); ++i) {
    std::cout << "Assignment " << (i + 1) << ": " << assignment_scores[i] << '\n';
}

// TODO: Lab 12 - Find highest and lowest using algorithm
if (!assignment_scores.empty()) {
    auto minIt = std::min_element(assignment_scores.begin(), assignment_scores.end());
    auto maxIt = std::max_element(assignment_scores.begin(), assignment_scores.end());
    
    std::cout << "\nHighest Score: " << *maxIt << '\n';
    std::cout << "Lowest Score: " << *minIt << '\n';
}
```

### Step 3: Calculate Range

You can also show the range (difference between highest and lowest):

```cpp
float range = *maxIt - *minIt;
std::cout << "Score Range: " << range << '\n';
```

---

## Expected Output

```
Scores Entered
==============
Assignment 1: 95
Assignment 2: 72
Assignment 3: 88
Assignment 4: 91
Assignment 5: 85

Highest Score: 95
Lowest Score: 72
Score Range: 23

Final Results
=============
Total Points Earned: 431
...
```

---

## Why Use STL Algorithms?

| Manual Loop | STL Algorithm |
|-------------|---------------|
| More code to write | One line |
| Potential for bugs | Tested and optimized |
| Harder to read | Self-documenting |
| May be slower | Highly optimized |

---

## Submission

When your program displays the highest and lowest scores using STL algorithms, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Included the `<algorithm>` header
- ✅ Used `std::min_element` to find the lowest value
- ✅ Used `std::max_element` to find the highest value
- ✅ Worked with iterators and dereferencing

---

## Next Steps

In **Lab 13**, you'll add file I/O to save and load your grades between sessions!
