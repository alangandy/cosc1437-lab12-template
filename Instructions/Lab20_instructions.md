# Lab 20: STL Algorithms and Lambda Functions

## Getting Started

> **Important:** This lab builds on your work from Lab 19.
> 
> Continue working in your **existing repository** from Lab 19. Do NOT create a new repository.
> 
> Your Lab 19 submission becomes the starting point for this lab.

---

## Objective

- Learn lambda function syntax in C++
- Use STL algorithms for data processing
- Implement sorting with custom comparators
- Add filtering and searching features

---

## Introduction

The Standard Template Library (STL) provides powerful algorithms that work with any container. Combined with **lambda functions**, you can write expressive, concise code for sorting, filtering, and transforming data.

In this lab, you'll add sorting options and search functionality to your grade calculator.

---

## New Concepts

### Lambda Syntax

```cpp
// Basic lambda
auto greet = []() {
    std::cout << "Hello!\n";
};
greet();

// Lambda with parameters
auto add = [](int a, int b) {
    return a + b;
};

// Lambda capturing variables
int threshold = 70;
auto isPassing = [threshold](int score) {
    return score >= threshold;
};
```

### Capture Modes

| Syntax | Meaning |
|--------|---------|
| `[]` | Capture nothing |
| `[x]` | Capture x by value |
| `[&x]` | Capture x by reference |
| `[=]` | Capture all by value |
| `[&]` | Capture all by reference |

### Common STL Algorithms

```cpp
#include <algorithm>

// Sort with custom comparator
std::sort(vec.begin(), vec.end(), [](int a, int b) {
    return a > b;  // Descending order
});

// Find element matching condition
auto it = std::find_if(vec.begin(), vec.end(), [](int n) {
    return n > 50;
});

// Count matching elements
int count = std::count_if(vec.begin(), vec.end(), [](int n) {
    return n >= 90;
});

// Apply function to each element
std::for_each(vec.begin(), vec.end(), [](int n) {
    std::cout << n << " ";
});
```

---

## Your Task

### Step 1: Include Algorithm Header

```cpp
#include <algorithm>
```

### Step 2: Add Sorting to View Function

```cpp
void viewItems(std::vector<GradedItem*>& items) {
    displayHeader("ALL GRADED ITEMS");
    
    if (items.empty()) {
        std::cout << "No items entered yet.\n";
        return;
    }
    
    std::cout << "Sort by:\n";
    std::cout << "1. Entry order (default)\n";
    std::cout << "2. Name (A-Z)\n";
    std::cout << "3. Name (Z-A)\n";
    std::cout << "4. Percentage (highest first)\n";
    std::cout << "5. Percentage (lowest first)\n";
    std::cout << "6. Category\n\n";
    
    int choice = InputHelper::getMenuChoice(1, 6);
    
    // Create a copy to sort
    std::vector<GradedItem*> sorted = items;
    
    switch (choice) {
        case 2:
            std::sort(sorted.begin(), sorted.end(),
                [](GradedItem* a, GradedItem* b) {
                    return a->getName() < b->getName();
                });
            break;
        case 3:
            std::sort(sorted.begin(), sorted.end(),
                [](GradedItem* a, GradedItem* b) {
                    return a->getName() > b->getName();
                });
            break;
        case 4:
            std::sort(sorted.begin(), sorted.end(),
                [](GradedItem* a, GradedItem* b) {
                    return a->getPercentage() > b->getPercentage();
                });
            break;
        case 5:
            std::sort(sorted.begin(), sorted.end(),
                [](GradedItem* a, GradedItem* b) {
                    return a->getPercentage() < b->getPercentage();
                });
            break;
        case 6:
            std::sort(sorted.begin(), sorted.end(),
                [](GradedItem* a, GradedItem* b) {
                    return a->getCategory() < b->getCategory();
                });
            break;
    }
    
    // Display sorted items
    std::cout << '\n';
    std::for_each(sorted.begin(), sorted.end(), [](GradedItem* item) {
        item->display();
    });
}
```

### Step 3: Add Filter Function

```cpp
void filterItems(const std::vector<GradedItem*>& items) {
    displayHeader("FILTER ITEMS");
    
    if (items.empty()) {
        std::cout << "No items to filter.\n";
        return;
    }
    
    std::cout << "Filter by:\n";
    std::cout << "1. Category\n";
    std::cout << "2. Minimum percentage\n";
    std::cout << "3. Grade letter\n\n";
    
    int choice = InputHelper::getMenuChoice(1, 3);
    
    std::vector<GradedItem*> filtered;
    
    switch (choice) {
        case 1: {
            std::cout << "1. Homework  2. Quiz  3. Exam\n";
            int cat = InputHelper::getMenuChoice(1, 3);
            std::string category = (cat == 1) ? "Homework" : (cat == 2) ? "Quiz" : "Exam";
            
            std::copy_if(items.begin(), items.end(), std::back_inserter(filtered),
                [&category](GradedItem* item) {
                    return item->getCategory() == category;
                });
            break;
        }
        case 2: {
            float minPct = InputHelper::getPercentage("Minimum percentage: ");
            
            std::copy_if(items.begin(), items.end(), std::back_inserter(filtered),
                [minPct](GradedItem* item) {
                    return item->getPercentage() >= minPct;
                });
            break;
        }
        case 3: {
            std::cout << "1. A  2. B  3. C  4. D  5. F\n";
            int g = InputHelper::getMenuChoice(1, 5);
            float minP, maxP;
            if (g == 1) { minP = 90; maxP = 100; }
            else if (g == 2) { minP = 80; maxP = 89.99f; }
            else if (g == 3) { minP = 70; maxP = 79.99f; }
            else if (g == 4) { minP = 60; maxP = 69.99f; }
            else { minP = 0; maxP = 59.99f; }
            
            std::copy_if(items.begin(), items.end(), std::back_inserter(filtered),
                [minP, maxP](GradedItem* item) {
                    float p = item->getPercentage();
                    return p >= minP && p <= maxP;
                });
            break;
        }
    }
    
    std::cout << "\nFound " << filtered.size() << " items:\n";
    std::for_each(filtered.begin(), filtered.end(), [](GradedItem* item) {
        item->display();
    });
}
```

### Step 4: Add Search Function

```cpp
void searchItems(const std::vector<GradedItem*>& items) {
    displayHeader("SEARCH ITEMS");
    
    std::string searchTerm = InputHelper::getString("Search for: ");
    
    // Convert to lowercase for case-insensitive search
    std::transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
    
    std::vector<GradedItem*> results;
    
    std::copy_if(items.begin(), items.end(), std::back_inserter(results),
        [&searchTerm](GradedItem* item) {
            std::string name = item->getName();
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            return name.find(searchTerm) != std::string::npos;
        });
    
    std::cout << "\nFound " << results.size() << " items matching '" << searchTerm << "':\n";
    
    if (results.empty()) {
        std::cout << "No items found.\n";
    } else {
        std::for_each(results.begin(), results.end(), [](GradedItem* item) {
            item->display();
        });
    }
}
```

### Step 5: Update Menu

Add options for filter and search:

```cpp
std::cout << "4. Filter Items\n";
std::cout << "5. Search Items\n";
```

---

## Expected Output

```
==================================================
  ALL GRADED ITEMS
==================================================
Sort by:
1. Entry order (default)
2. Name (A-Z)
3. Name (Z-A)
4. Percentage (highest first)
5. Percentage (lowest first)
6. Category

Enter choice: 4

Exam - Final Exam: 92/100 (92%)
Homework - Ch12: 47/50 (94%)
Quiz - Quiz 3: 28/30 (93.3%)
Homework - Ch11: 85/100 (85%)
Quiz - Quiz 2: 18/25 (72%)
```

---

## Common STL Algorithms

| Algorithm | Purpose |
|-----------|---------|
| `sort` | Sort elements |
| `find_if` | Find first match |
| `count_if` | Count matches |
| `copy_if` | Copy matching elements |
| `for_each` | Apply function to all |
| `transform` | Transform elements |
| `remove_if` | Remove matching elements |

---

## Submission

When your program supports sorting, filtering, and searching with lambdas, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Created lambda functions with various captures
- ✅ Used `std::sort` with custom comparators
- ✅ Implemented filtering with `std::copy_if`
- ✅ Built a search feature

---

## Next Steps

In **Lab 21**, you'll use `std::map` for user-defined weighted categories!
