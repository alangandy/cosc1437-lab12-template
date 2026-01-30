/**
 * Exam.h
 * Derived class for exam assignments
 * 
 * TODO: Lab 17 - Implement the Exam class inheriting from GradedItem
 */

#ifndef EXAM_H
#define EXAM_H

#include "GradedItem.h"

// ============================================================================
// TODO: Lab 17 - Inherit from GradedItem using public inheritance
// ============================================================================
class Exam : public GradedItem {
public:
    // Default constructor
    Exam() : GradedItem() {}
    
    // Parameterized constructor - calls base class constructor
    Exam(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}
    
    // ========================================================================
    // TODO: Lab 17 - Override virtual methods
    // ========================================================================
    
    // Override to return "Exam"
    std::string getCategory() const override { 
        return "Exam"; 
    }
    
    // Override to return exam weight (50%)
    float getWeight() const override { 
        return 0.50f; 
    }
};

#endif // EXAM_H
