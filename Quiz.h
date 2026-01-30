/**
 * Quiz.h
 * Derived class for quiz assignments
 * 
 * TODO: Lab 17 - Implement the Quiz class inheriting from GradedItem
 */

#ifndef QUIZ_H
#define QUIZ_H

#include "GradedItem.h"

// ============================================================================
// TODO: Lab 17 - Inherit from GradedItem using public inheritance
// ============================================================================
class Quiz : public GradedItem {
public:
    // Default constructor
    Quiz() : GradedItem() {}
    
    // Parameterized constructor - calls base class constructor
    Quiz(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}
    
    // ========================================================================
    // TODO: Lab 17 - Override virtual methods
    // ========================================================================
    
    // Override to return "Quiz"
    std::string getCategory() const override { 
        return "Quiz"; 
    }
    
    // Override to return quiz weight (30%)
    float getWeight() const override { 
        return 0.30f; 
    }
};

#endif // QUIZ_H
