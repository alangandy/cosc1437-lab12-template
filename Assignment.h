/**
 * Assignment.h
 * Custom class for storing assignment information
 * 
 * TODO: Lab 14 - Implement the Assignment class
 * TODO: Lab 15 - Move implementations to Assignment.cpp, make members private
 */

#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include <iostream>

class Assignment {
// ============================================================================
// TODO: Lab 15 - Change 'public' to 'private' for member variables
// ============================================================================
public:
    std::string name;
    float points_earned;
    float points_possible;

public:
    // ========================================================================
    // TODO: Lab 14 - Implement constructors
    // ========================================================================
    
    // Default constructor
    Assignment() {
        name = "";
        points_earned = 0;
        points_possible = 0;
    }
    
    // Parameterized constructor
    Assignment(const std::string& n, float earned, float possible) {
        name = n;
        points_earned = earned;
        points_possible = possible;
    }
    
    // ========================================================================
    // TODO: Lab 14 - Implement member functions
    // ========================================================================
    
    // Calculate and return the percentage score
    float getPercentage() const {
        if (points_possible == 0) return 0;
        return (points_earned / points_possible) * 100;
    }
    
    // Display assignment information
    void display() const {
        std::cout << name << ": " 
                  << points_earned << "/" << points_possible 
                  << " (" << getPercentage() << "%)\n";
    }
    
    // ========================================================================
    // TODO: Lab 15 - Add getter methods (after making members private)
    // ========================================================================
    // std::string getName() const;
    // float getPointsEarned() const;
    // float getPointsPossible() const;
    
    // ========================================================================
    // TODO: Lab 15 - Add setter methods with validation
    // ========================================================================
    // void setName(const std::string& n);
    // void setPointsEarned(float earned);
    // void setPointsPossible(float possible);
};

#endif // ASSIGNMENT_H
