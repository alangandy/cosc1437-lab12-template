# Lab 13: File Storage with Streams

## Getting Started

> **Important:** This lab builds on your work from Lab 12.
> 
> Continue working in your **existing repository** from Lab 12. Do NOT create a new repository.
> 
> Your Lab 12 submission becomes the starting point for this lab.

---

## Objective

- Learn to use file streams (`std::ifstream` and `std::ofstream`)
- Save grade data to a file
- Load grade data from a file
- Understand file I/O error handling

---

## Introduction

Your grade calculator now stores scores in a vector, but all data is lost when the program ends. In this lab, you'll add the ability to **save** your grading scheme and scores to a file, and **load** them back when the program starts.

This is a crucial feature for any real application - users expect their data to persist between sessions!

---

## New Concepts

### File Output with ofstream

```cpp
#include <fstream>

std::ofstream outFile("grades.txt");
if (outFile.is_open()) {
    outFile << total_points << '\n';
    outFile << score1 << '\n';
    outFile.close();
}
```

### File Input with ifstream

```cpp
std::ifstream inFile("grades.txt");
if (inFile.is_open()) {
    inFile >> total_points;
    inFile >> score1;
    inFile.close();
}
```

### Key Functions

| Function | Purpose |
|----------|---------|
| `is_open()` | Check if file opened successfully |
| `close()` | Close the file when done |
| `>>` | Read from file (like cin) |
| `<<` | Write to file (like cout) |

---

## Your Task

### Step 1: Add the fstream Include

At the top of `main.cpp`, add:

```cpp
#include <fstream>
```

### Step 2: Create the Save Function

Find the `TODO: Lab 13` comment and implement the `saveGrades()` function:

```cpp
void saveGrades(const std::string& filename, 
                int total_points,
                float A_pct, float B_pct, float C_pct, float D_pct,
                const std::vector<float>& scores) {
    std::ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        std::cout << "Error: Could not save to file.\n";
        return;
    }
    
    // Save grading scheme
    outFile << total_points << '\n';
    outFile << A_pct << '\n';
    outFile << B_pct << '\n';
    outFile << C_pct << '\n';
    outFile << D_pct << '\n';
    
    // Save number of scores, then each score
    outFile << scores.size() << '\n';
    for (size_t i = 0; i < scores.size(); ++i) {
        outFile << scores[i] << '\n';
    }
    
    outFile.close();
    std::cout << "Grades saved successfully!\n";
}
```

### Step 3: Create the Load Function

```cpp
bool loadGrades(const std::string& filename,
                int& total_points,
                float& A_pct, float& B_pct, float& C_pct, float& D_pct,
                std::vector<float>& scores) {
    std::ifstream inFile(filename);
    
    if (!inFile.is_open()) {
        return false;  // File doesn't exist
    }
    
    // Load grading scheme
    inFile >> total_points;
    inFile >> A_pct >> B_pct >> C_pct >> D_pct;
    
    // Load scores
    size_t count;
    inFile >> count;
    
    scores.clear();
    for (size_t i = 0; i < count; ++i) {
        float score;
        inFile >> score;
        scores.push_back(score);
    }
    
    inFile.close();
    std::cout << "Grades loaded successfully!\n";
    return true;
}
```

### Step 4: Add Save/Load Prompts

At program start, ask if user wants to load:

```cpp
char loadChoice;
std::cout << "Load saved grades? (y/n): ";
std::cin >> loadChoice;

if (loadChoice == 'y' || loadChoice == 'Y') {
    if (loadGrades("grades.txt", total_course_points, 
                   A_percentage, B_percentage, C_percentage, D_percentage,
                   assignment_scores)) {
        // Data loaded, skip grading scheme input
    }
}
```

At program end, ask if user wants to save:

```cpp
char saveChoice;
std::cout << "Save grades for next time? (y/n): ";
std::cin >> saveChoice;

if (saveChoice == 'y' || saveChoice == 'Y') {
    saveGrades("grades.txt", total_course_points,
               A_percentage, B_percentage, C_percentage, D_percentage,
               assignment_scores);
}
```

---

## Expected Output

```
Load saved grades? (y/n): n

[... normal program flow ...]

Save grades for next time? (y/n): y
Grades saved successfully!
```

Next run:
```
Load saved grades? (y/n): y
Grades loaded successfully!
Total Points: 1000
Scores loaded: 3
```

---

## Submission

When your program can save and load grades correctly, click **"Submit"**.

---

## What You Learned

In this lab, you:
- ✅ Used `std::ofstream` to write data to files
- ✅ Used `std::ifstream` to read data from files
- ✅ Implemented data persistence for your application
- ✅ Handled file I/O errors gracefully

---

## Next Steps

In **Lab 14**, you'll create an `Assignment` class to store assignment names along with scores!
