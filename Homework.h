/**
 * Homework.h
 * Derived class for homework assignments
 * 
 * TODO: Lab 17 - Implement the Homework class inheriting from GradedItem
 */

#ifndef HOMEWORK_H
#define HOMEWORK_H

#include "GradedItem.h"

// ============================================================================
// TODO: Lab 17 - Inherit from GradedItem using public inheritance
// ============================================================================
class Homework : public GradedItem {
public:
    // Default constructor
    Homework() : GradedItem() {}
    
    // Parameterized constructor - calls base class constructor
    Homework(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}
    
    // ========================================================================
    // TODO: Lab 17 - Override virtual methods
    // ========================================================================
    
    // Override to return "Homework"
    std::string getCategory() const override { 
        return "Homework"; 
    }
    
    // Override to return homework weight (20%)
    float getWeight() const override { 
        return 0.20f; 
    }
};

#endif // HOMEWORK_H
