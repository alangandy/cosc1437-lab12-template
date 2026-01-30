/**
 * COSC 1437 - Grade Calculator
 * Portfolio Project: Labs 11-22
 * 
 * This file contains the main program logic for the Grade Calculator.
 * Look for TODO comments to find your tasks for each lab.
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "greeting.h"

// TODO: Lab 13 - Add #include <fstream> for file operations

// TODO: Lab 14 - Add #include "Assignment.h"

// TODO: Lab 16 - Add #include <iomanip> for formatted output

// TODO: Lab 17 - Add includes for inheritance:
// #include "GradedItem.h"
// #include "Homework.h"
// #include "Quiz.h"
// #include "Exam.h"

// TODO: Lab 18 - Add #include "InputHelper.h"

// TODO: Lab 19 - Add #include "MathHelper.h"

// TODO: Lab 20 - Add #include <algorithm> for STL algorithms

// TODO: Lab 21 - Add #include <map> and #include "Category.h"

// TODO: Lab 22 - Add #include "Exceptions.h" and #include "FileManager.h"


// ============================================================================
// TODO: Lab 13 - Implement saveGrades() function
// ============================================================================
// void saveGrades(const std::string& filename, 
//                 int total_points,
//                 float A_pct, float B_pct, float C_pct, float D_pct,
//                 const std::vector<float>& scores) {
//     // Open file with ofstream
//     // Write grading scheme
//     // Write number of scores
//     // Write each score
//     // Close file
// }


// ============================================================================
// TODO: Lab 13 - Implement loadGrades() function
// ============================================================================
// bool loadGrades(const std::string& filename,
//                 int& total_points,
//                 float& A_pct, float& B_pct, float& C_pct, float& D_pct,
//                 std::vector<float>& scores) {
//     // Open file with ifstream
//     // Read grading scheme
//     // Read number of scores
//     // Read each score into vector
//     // Close file
//     // Return true if successful
// }


// ============================================================================
// TODO: Lab 16 - Implement display helper functions
// ============================================================================
// void displayHeader(const std::string& title) {
//     // Print formatted header with title
// }

// void displaySeparator() {
//     // Print separator line
// }

// void displayMenu() {
//     // Print main menu options
// }


// ============================================================================
// TODO: Lab 16 - Implement menu handler functions
// ============================================================================
// void setGradingScheme(int& total, float& A, float& B, float& C, float& D) {
//     // Get grading scheme from user
// }

// void addAssignment(std::vector<Assignment>& assignments) {
//     // Get assignment details and add to vector
// }

// void viewAssignments(const std::vector<Assignment>& assignments) {
//     // Display all assignments with formatting
// }


// ============================================================================
// TODO: Lab 17 - Update to use GradedItem* pointers for polymorphism
// ============================================================================
// void addGradedItem(std::vector<GradedItem*>& items) {
//     // Show category menu (Homework, Quiz, Exam)
//     // Create appropriate derived class object
//     // Add pointer to vector
// }

// void calculateWeightedGrade(const std::vector<GradedItem*>& items, ...) {
//     // Calculate weighted average by category
// }


// ============================================================================
// TODO: Lab 19 - Implement statistics using templates
// ============================================================================
// void viewStatistics(const std::vector<GradedItem*>& items) {
//     // Use MathHelper template functions
//     // Display average, min, max, distribution
// }

// void whatIfCalculator(...) {
//     // Project final grade based on hypothetical scores
// }


// ============================================================================
// TODO: Lab 20 - Implement sorting and filtering with lambdas
// ============================================================================
// void viewItemsSorted(std::vector<GradedItem*>& items) {
//     // Sort options with lambda comparators
// }

// void filterItems(const std::vector<GradedItem*>& items) {
//     // Filter by category, percentage, grade using copy_if
// }

// void searchItems(const std::vector<GradedItem*>& items) {
//     // Search by name using find_if and lambdas
// }


// ============================================================================
// TODO: Lab 21 - Implement category management with std::map
// ============================================================================
// void setupCategories(std::map<std::string, Category>& categories) {
//     // Let user define custom categories with weights
// }

// void manageCategories(std::map<std::string, Category>& categories) {
//     // View, add, delete, modify categories
// }


// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    // ========================================================================
    // Variable Declarations
    // ========================================================================
    
    // Grading scheme
    int total_course_points = 0;
    float A_points = 0.0f, B_points = 0.0f, C_points = 0.0f, D_points = 0.0f;
    float A_percentage = 0.0f, B_percentage = 0.0f, C_percentage = 0.0f, D_percentage = 0.0f;
    
    // Score tracking
    float total_points_earned = 0.0f;
    float total_percentage_earned = 0.0f;
    float assignment_score = 0.0f;
    
    // Program control
    char earned_grade = ' ';
    bool score_input = true;
    int assignment = 1;
    
    // TODO: Lab 11 - Declare vector for scores
    std::vector<float> assignment_scores;
    
    // TODO: Lab 14 - Change to: std::vector<Assignment> assignments;
    
    // TODO: Lab 17 - Change to: std::vector<GradedItem*> items;
    
    // TODO: Lab 21 - Add: std::map<std::string, Category> categories;

    // ========================================================================
    // TODO: Lab 22 - Wrap main logic in try-catch
    // ========================================================================
    // try {
    
    // ========================================================================
    // Program Start
    // ========================================================================
    
    // Display greeting
    displayGreeting();
    
    // Welcome message
    std::cout << "Welcome to the COSC 1437 Grade Calculator\n\n";

    // ========================================================================
    // TODO: Lab 13 - Add load prompt at start
    // ========================================================================
    // char loadChoice;
    // std::cout << "Load saved grades? (y/n): ";
    // std::cin >> loadChoice;
    // if (loadChoice == 'y' || loadChoice == 'Y') {
    //     if (loadGrades("grades.txt", ...)) {
    //         std::cout << "Grades loaded!\n";
    //     }
    // }

    // ========================================================================
    // Grading Scheme Setup
    // ========================================================================
    std::cout << "Grading Scheme Setup\n";
    std::cout << "====================\n";
    std::cout << "Please input the Total Points Possible: ";
    std::cin >> total_course_points;
    std::cout << '\n';

    // Get grade thresholds
    for (char grade = 'A'; grade <= 'D'; grade++) {
        std::cout << "Please input the Minimum Points for a '" << grade << "': ";
        if (grade == 'A') {
            std::cin >> A_points;
        } else if (grade == 'B') {
            std::cin >> B_points;
        } else if (grade == 'C') {
            std::cin >> C_points;
        } else if (grade == 'D') {
            std::cin >> D_points;
        }
        std::cout << '\n';
    }

    // Calculate percentages
    A_percentage = (A_points / total_course_points) * 100;
    B_percentage = (B_points / total_course_points) * 100;
    C_percentage = (C_points / total_course_points) * 100;
    D_percentage = (D_points / total_course_points) * 100;

    // Display the grading scheme
    std::cout << "The Grading Scheme You Input\n";
    std::cout << "============================\n";
    std::cout << "Total Points Possible in the Course: " << total_course_points << '\n';
    std::cout << "Points needed for an 'A': " << A_points << " or " << A_percentage << "%\n";
    std::cout << "Points needed for a 'B': " << B_points << " or " << B_percentage << "%\n";
    std::cout << "Points needed for a 'C': " << C_points << " or " << C_percentage << "%\n";
    std::cout << "Points needed for a 'D': " << D_points << " or " << D_percentage << "%\n";

    // ========================================================================
    // TODO: Lab 16 - Replace linear flow with menu loop
    // ========================================================================
    // int choice = 0;
    // do {
    //     displayMenu();
    //     std::cin >> choice;
    //     switch (choice) {
    //         case 1: setGradingScheme(...); break;
    //         case 2: addAssignment(...); break;
    //         // ... more cases
    //         case 0: std::cout << "Goodbye!\n"; break;
    //     }
    // } while (choice != 0);

    // ========================================================================
    // Score Input Loop
    // ========================================================================
    std::cout << "\nGrade Calculation\n";
    std::cout << "=================\n";
    std::cout << "Enter assignment scores (negative number to stop):\n\n";

    do {
        std::cout << "Please input the points earned for Assignment " << assignment << ": ";
        std::cin >> assignment_score;
        
        if (assignment_score >= 0) {
            // TODO: Lab 11 - Store score in vector
            assignment_scores.push_back(assignment_score);
            
            total_points_earned += assignment_score;
            assignment++;
        } else {
            score_input = false;
        }
    } while (score_input);

    // ========================================================================
    // Display Scores from Vector
    // ========================================================================
    std::cout << "\nScores Entered\n";
    std::cout << "==============\n";
    
    // TODO: Lab 11 - Display scores from vector
    for (size_t i = 0; i < assignment_scores.size(); ++i) {
        std::cout << "Assignment " << (i + 1) << ": " << assignment_scores[i] << '\n';
    }

    // ========================================================================
    // TODO: Lab 12 - Find highest and lowest using <algorithm>
    // ========================================================================
    // if (!assignment_scores.empty()) {
    //     auto minIt = std::min_element(assignment_scores.begin(), assignment_scores.end());
    //     auto maxIt = std::max_element(assignment_scores.begin(), assignment_scores.end());
    //     std::cout << "\nHighest Score: " << *maxIt << '\n';
    //     std::cout << "Lowest Score: " << *minIt << '\n';
    // }

    // ========================================================================
    // Grade Calculation
    // ========================================================================
    
    // Determine the final grade
    if (total_points_earned >= A_points) {
        earned_grade = 'A';
    } else if (total_points_earned >= B_points) {
        earned_grade = 'B';
    } else if (total_points_earned >= C_points) {
        earned_grade = 'C';
    } else if (total_points_earned >= D_points) {
        earned_grade = 'D';
    } else {
        earned_grade = 'F';
    }

    // Calculate percentage
    total_percentage_earned = (total_points_earned / total_course_points) * 100;

    // Display results
    std::cout << "\nFinal Results\n";
    std::cout << "=============\n";
    std::cout << "Total Points Earned: " << total_points_earned << '\n';
    std::cout << "Total Points Possible: " << total_course_points << '\n';
    std::cout << "Total Percentage: " << total_percentage_earned << "%\n";
    std::cout << "Total Percentage (rounded): " << round(total_percentage_earned) << "%\n";
    std::cout << "Final Letter Grade: " << earned_grade << '\n';

    // ========================================================================
    // TODO: Lab 13 - Add save prompt at end
    // ========================================================================
    // char saveChoice;
    // std::cout << "\nSave grades for next time? (y/n): ";
    // std::cin >> saveChoice;
    // if (saveChoice == 'y' || saveChoice == 'Y') {
    //     saveGrades("grades.txt", ...);
    // }

    // ========================================================================
    // TODO: Lab 17 - Clean up dynamically allocated memory
    // ========================================================================
    // for (size_t i = 0; i < items.size(); ++i) {
    //     delete items[i];
    // }
    // items.clear();

    // ========================================================================
    // TODO: Lab 22 - Exception handling catch blocks
    // ========================================================================
    // } catch (const GradeCalculatorException& e) {
    //     std::cerr << "Error: " << e.what() << '\n';
    //     return 1;
    // } catch (const std::exception& e) {
    //     std::cerr << "Fatal error: " << e.what() << '\n';
    //     return 1;
    // }

    return 0;
}
