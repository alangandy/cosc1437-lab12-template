# Lab 22: Exception Handling - Final Application

## Getting Started

> **Important:** This lab builds on your work from Lab 21.
> 
> Continue working in your **existing repository** from Lab 21. Do NOT create a new repository.
> 
> Your Lab 21 submission becomes the starting point for this lab.

---

## Objective

- Learn exception handling with try-catch blocks
- Create custom exception classes
- Implement robust file operations
- Complete a production-ready grade calculator

---

## Introduction

Congratulations on reaching the final lab! Your grade calculator is feature-complete, but it's not quite production-ready. What happens if a file can't be opened? If memory allocation fails? If data is corrupted?

In this lab, you'll add **exception handling** to make your application robust and professional. By the end, you'll have a complete, polished grade calculator!

---

## New Concepts

### Try-Catch Blocks

```cpp
try {
    // Code that might throw an exception
    riskyOperation();
} catch (const std::exception& e) {
    // Handle the exception
    std::cout << "Error: " << e.what() << '\n';
}
```

### Throwing Exceptions

```cpp
void validate(int value) {
    if (value < 0) {
        throw std::invalid_argument("Value cannot be negative");
    }
}
```

### Standard Exceptions

| Type | Use Case |
|------|----------|
| `std::exception` | Base class |
| `std::runtime_error` | Runtime problems |
| `std::invalid_argument` | Invalid parameter |
| `std::out_of_range` | Value out of range |
| `std::bad_alloc` | Memory allocation failure |

### Custom Exceptions

```cpp
class FileException : public std::runtime_error {
public:
    FileException(const std::string& msg)
        : std::runtime_error(msg) {}
};
```

---

## Your Task

### Step 1: Create Exceptions.h

```cpp
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class GradeCalculatorException : public std::runtime_error {
public:
    explicit GradeCalculatorException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class FileException : public GradeCalculatorException {
public:
    explicit FileException(const std::string& msg)
        : GradeCalculatorException("File error: " + msg) {}
};

class InvalidDataException : public GradeCalculatorException {
public:
    explicit InvalidDataException(const std::string& msg)
        : GradeCalculatorException("Invalid data: " + msg) {}
};

class CategoryException : public GradeCalculatorException {
public:
    explicit CategoryException(const std::string& msg)
        : GradeCalculatorException("Category error: " + msg) {}
};

#endif
```

### Step 2: Create FileManager.h

```cpp
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <string>
#include <map>
#include "Category.h"
#include "Exceptions.h"

namespace FileManager {

    inline void saveToFile(const std::string& filename,
                          const std::map<std::string, Category>& categories,
                          float A, float B, float C, float D) {
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            throw FileException("Could not open file for writing: " + filename);
        }
        
        try {
            file << A << '\n' << B << '\n' << C << '\n' << D << '\n';
            file << categories.size() << '\n';
            
            for (const auto& [name, cat] : categories) {
                file << name << '\n' << cat.weight << '\n';
                file << cat.items.size() << '\n';
                
                for (const GradedItem* item : cat.items) {
                    file << item->getName() << '\n';
                    file << item->getPointsEarned() << '\n';
                    file << item->getPointsPossible() << '\n';
                }
            }
            
            if (file.fail()) {
                throw FileException("Write failed");
            }
            
            file.close();
        } catch (...) {
            file.close();
            throw;
        }
    }

    inline bool loadFromFile(const std::string& filename,
                            std::map<std::string, Category>& categories,
                            float& A, float& B, float& C, float& D) {
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            return false;  // File doesn't exist
        }
        
        try {
            // Clear existing
            for (auto& [name, cat] : categories) {
                for (GradedItem* item : cat.items) delete item;
            }
            categories.clear();
            
            if (!(file >> A >> B >> C >> D)) {
                throw InvalidDataException("Could not read thresholds");
            }
            
            size_t numCats;
            if (!(file >> numCats)) {
                throw InvalidDataException("Could not read category count");
            }
            file.ignore();
            
            for (size_t i = 0; i < numCats; ++i) {
                std::string catName;
                float weight;
                size_t numItems;
                
                std::getline(file, catName);
                file >> weight >> numItems;
                file.ignore();
                
                Category cat(catName, weight);
                
                for (size_t j = 0; j < numItems; ++j) {
                    std::string itemName;
                    float earned, possible;
                    
                    std::getline(file, itemName);
                    file >> earned >> possible;
                    file.ignore();
                    
                    cat.items.push_back(new GradedItem(itemName, earned, possible));
                }
                
                categories[catName] = cat;
            }
            
            file.close();
            return true;
            
        } catch (...) {
            file.close();
            throw;
        }
    }

}  // namespace FileManager

#endif
```

### Step 3: Add Exception Handling to Main

```cpp
#include "Exceptions.h"
#include "FileManager.h"

int main() {
    try {
        // All your existing code...
        
        std::map<std::string, Category> categories;
        float A = 90, B = 80, C = 70, D = 60;
        
        displayGreeting();
        
        int choice = 0;
        do {
            try {
                displayMenu();
                choice = InputHelper::getMenuChoice(0, 11);
                
                switch (choice) {
                    // ... all cases
                    
                    case 10:  // Save
                        try {
                            std::string filename = InputHelper::getString("Filename: ");
                            FileManager::saveToFile(filename, categories, A, B, C, D);
                            std::cout << "Saved successfully!\n";
                        } catch (const FileException& e) {
                            std::cout << "Error: " << e.what() << '\n';
                        }
                        break;
                        
                    case 11:  // Load
                        try {
                            std::string filename = InputHelper::getString("Filename: ");
                            if (FileManager::loadFromFile(filename, categories, A, B, C, D)) {
                                std::cout << "Loaded successfully!\n";
                            } else {
                                std::cout << "File not found.\n";
                            }
                        } catch (const InvalidDataException& e) {
                            std::cout << "Error: " << e.what() << '\n';
                        }
                        break;
                }
                
            } catch (const GradeCalculatorException& e) {
                std::cout << "\nError: " << e.what() << '\n';
                InputHelper::pressEnterToContinue();
            }
            
        } while (choice != 0);
        
        // Cleanup
        for (auto& [name, cat] : categories) {
            for (GradedItem* item : cat.items) delete item;
        }
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "\n*** Fatal Error: " << e.what() << " ***\n";
        return 1;
    } catch (...) {
        std::cerr << "\n*** Unknown Fatal Error ***\n";
        return 1;
    }
}
```

### Step 4: Add Validation with Exceptions

Update GradedItem constructor:

```cpp
GradedItem(const std::string& n, float earned, float possible) {
    if (n.empty()) {
        throw InvalidDataException("Name cannot be empty");
    }
    if (possible <= 0) {
        throw InvalidDataException("Points possible must be > 0");
    }
    if (earned < 0 || earned > possible) {
        throw InvalidDataException("Points earned out of range");
    }
    
    name = n;
    points_earned = earned;
    points_possible = possible;
}
```

---

## Final Menu Structure

```
==================================================
  GRADE CALCULATOR - MAIN MENU
==================================================
 1. Set Up Categories
 2. Set Grade Thresholds
 3. Add Graded Item
 4. View All Items
 5. View Statistics
 6. Calculate Final Grade
 7. What-If Calculator
 8. Filter Items
 9. Search Items
10. Save Data
11. Load Data
 0. Exit
--------------------------------------------------
```

---

## Expected Behavior

```
Enter filename: /invalid/path/file.dat
Error: File error: Could not open file for writing: /invalid/path/file.dat

Enter filename: corrupted.dat
Error: Invalid data: Could not read thresholds
```

---

## 🎉 Congratulations!

You've completed all 22 labs and built a **professional-grade** Grade Calculator!

### Features Implemented

| Lab | Feature |
|-----|---------|
| 1-2 | Basic I/O |
| 3-4 | Variables and math |
| 5-7 | Control flow |
| 8-9 | Functions |
| 10 | Header files |
| 11-12 | Vectors and algorithms |
| 13 | File I/O |
| 14-16 | OOP basics |
| 17 | Inheritance |
| 18 | Input validation |
| 19 | Templates |
| 20 | Lambdas/STL |
| 21 | Maps |
| 22 | Exceptions |

---

## Submission

When your program handles all errors gracefully, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Implemented try-catch exception handling
- ✅ Created custom exception classes
- ✅ Built robust file operations
- ✅ Completed a production-ready application

---

## What's Next?

You now have the foundation for:
- Data Structures (COSC 2436)
- More complex C++ applications
- Contributing to open-source projects
- Learning advanced topics

**Great work completing this course!** 🎓
