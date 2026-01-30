# Lab 21: Associative Containers with std::map

## Getting Started

> **Important:** This lab builds on your work from Lab 20.
> 
> Continue working in your **existing repository** from Lab 20. Do NOT create a new repository.
> 
> Your Lab 20 submission becomes the starting point for this lab.

---

## Objective

- Learn to use `std::map` for key-value storage
- Implement user-defined grade categories
- Create a flexible weighted grading system
- Manage categories dynamically

---

## Introduction

Until now, your grade calculator has had fixed categories: Homework (20%), Quiz (30%), and Exam (50%). But different courses have different grading schemes! In this lab, you'll use `std::map` to let users define their own categories with custom weights.

The `std::map` container stores key-value pairs, perfect for mapping category names to their weights and items.

---

## New Concepts

### std::map Basics

```cpp
#include <map>

std::map<std::string, float> weights;

// Insert values
weights["Homework"] = 20.0;
weights["Exams"] = 50.0;

// Access values
float hw = weights["Homework"];

// Check if key exists
if (weights.find("Labs") != weights.end()) {
    // Key exists
}

// Iterate over map
for (const auto& pair : weights) {
    std::cout << pair.first << ": " << pair.second << "%\n";
}
```

### Map Operations

| Operation | Description |
|-----------|-------------|
| `map[key] = value` | Insert or update |
| `map.at(key)` | Access with bounds check |
| `map.find(key)` | Get iterator to element |
| `map.count(key)` | Check existence (0 or 1) |
| `map.erase(key)` | Remove element |
| `map.size()` | Number of elements |

### Structured Bindings (C++17)

```cpp
for (const auto& [name, weight] : categoryWeights) {
    std::cout << name << ": " << weight << "%\n";
}
```

---

## Your Task

### Step 1: Include Map Header

```cpp
#include <map>
```

### Step 2: Create Category.h

```cpp
#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include "GradedItem.h"

struct Category {
    std::string name;
    float weight;
    std::vector<GradedItem*> items;
    
    Category() : name(""), weight(0) {}
    Category(const std::string& n, float w) : name(n), weight(w) {}
    
    float getAverage() const {
        if (items.empty()) return 0;
        float total = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            total += items[i]->getPercentage();
        }
        return total / items.size();
    }
    
    float getWeightedContribution() const {
        return getAverage() * (weight / 100.0);
    }
};

#endif
```

### Step 3: Update Data Structure

Replace your vector with a map:

```cpp
#include "Category.h"

// In main():
std::map<std::string, Category> categories;
```

### Step 4: Create Category Setup Function

```cpp
void setupCategories(std::map<std::string, Category>& categories) {
    displayHeader("CATEGORY SETUP");
    
    // Clear existing
    for (auto& [name, cat] : categories) {
        for (GradedItem* item : cat.items) {
            delete item;
        }
    }
    categories.clear();
    
    int numCats = InputHelper::getInt("How many categories? (1-10): ", 1, 10);
    
    float totalWeight = 0;
    
    for (int i = 0; i < numCats; ++i) {
        std::cout << "\nCategory " << (i + 1) << ":\n";
        
        std::string name = InputHelper::getString("  Name: ");
        
        while (categories.count(name) > 0) {
            std::cout << "  Category already exists!\n";
            name = InputHelper::getString("  Different name: ");
        }
        
        float remaining = 100.0f - totalWeight;
        std::cout << "  (Remaining weight: " << remaining << "%)\n";
        
        float weight;
        if (i == numCats - 1) {
            weight = remaining;
            std::cout << "  Weight (auto): " << weight << "%\n";
        } else {
            weight = InputHelper::getFloat("  Weight (%): ", 0.1f, remaining);
        }
        
        categories[name] = Category(name, weight);
        totalWeight += weight;
    }
    
    std::cout << "\nCategories created:\n";
    for (const auto& [name, cat] : categories) {
        std::cout << "  " << name << ": " << cat.weight << "%\n";
    }
}
```

### Step 5: Update Add Item Function

```cpp
void addGradedItem(std::map<std::string, Category>& categories) {
    displayHeader("ADD GRADED ITEM");
    
    if (categories.empty()) {
        std::cout << "Please set up categories first!\n";
        return;
    }
    
    std::cout << "Select category:\n";
    std::vector<std::string> names;
    int i = 1;
    for (const auto& [name, cat] : categories) {
        std::cout << i << ". " << name << " (" << cat.weight << "%)\n";
        names.push_back(name);
        i++;
    }
    
    int choice = InputHelper::getMenuChoice(1, names.size());
    std::string selected = names[choice - 1];
    
    std::string itemName = InputHelper::getString("Item name: ");
    float possible = InputHelper::getFloat("Points possible: ", 0.1f, 1000.0f);
    float earned = InputHelper::getFloat("Points earned: ", 0.0f, possible);
    
    GradedItem* item = new GradedItem(itemName, earned, possible);
    categories[selected].items.push_back(item);
    
    std::cout << "\nItem added to " << selected << "!\n";
}
```

### Step 6: Update Final Grade Calculation

```cpp
void calculateFinalGrade(const std::map<std::string, Category>& categories,
                         float A_pct, float B_pct, float C_pct, float D_pct) {
    displayHeader("FINAL GRADE CALCULATION");
    
    if (categories.empty()) {
        std::cout << "No categories set up.\n";
        return;
    }
    
    std::cout << std::fixed << std::setprecision(1);
    
    float finalGrade = 0;
    
    for (const auto& [name, cat] : categories) {
        float avg = cat.getAverage();
        float contribution = cat.getWeightedContribution();
        
        std::cout << name << ":\n";
        std::cout << "  Average: " << avg << "%\n";
        std::cout << "  Weight: " << cat.weight << "%\n";
        std::cout << "  Contribution: " << contribution << "%\n\n";
        
        if (!cat.items.empty()) {
            finalGrade += contribution;
        }
    }
    
    char grade;
    if (finalGrade >= A_pct) grade = 'A';
    else if (finalGrade >= B_pct) grade = 'B';
    else if (finalGrade >= C_pct) grade = 'C';
    else if (finalGrade >= D_pct) grade = 'D';
    else grade = 'F';
    
    std::cout << "============================\n";
    std::cout << "Final Grade: " << finalGrade << "% = " << grade << '\n';
    std::cout << "============================\n";
}
```

### Step 7: Add Category Management Menu

```cpp
void manageCategories(std::map<std::string, Category>& categories) {
    displayHeader("MANAGE CATEGORIES");
    
    std::cout << "1. View categories\n";
    std::cout << "2. Add category\n";
    std::cout << "3. Delete category\n";
    std::cout << "4. Reset all\n\n";
    
    int choice = InputHelper::getMenuChoice(1, 4);
    
    switch (choice) {
        case 1:
            for (const auto& [name, cat] : categories) {
                std::cout << name << ": " << cat.weight << "% ("
                          << cat.items.size() << " items)\n";
            }
            break;
        case 2:
            // Add implementation
            break;
        case 3:
            // Delete implementation  
            break;
        case 4:
            setupCategories(categories);
            break;
    }
}
```

---

## Expected Output

```
==================================================
  CATEGORY SETUP
==================================================
How many categories? (1-10): 4

Category 1:
  Name: Homework
  (Remaining weight: 100%)
  Weight (%): 15

Category 2:
  Name: Labs
  (Remaining weight: 85%)
  Weight (%): 20

Category 3:
  Name: Quizzes
  (Remaining weight: 65%)
  Weight (%): 25

Category 4:
  Name: Exams
  Weight (auto): 40%

Categories created:
  Exams: 40%
  Homework: 15%
  Labs: 20%
  Quizzes: 25%
```

---

## Submission

When your program supports user-defined weighted categories, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Used `std::map` for key-value storage
- ✅ Implemented user-defined categories
- ✅ Created flexible weighted grading
- ✅ Managed dynamic data structures

---

## Next Steps

In **Lab 22**, you'll add exception handling for a robust final application!
