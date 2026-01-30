/**
 * GradedItem.h
 * Base class for all graded items (Homework, Quiz, Exam)
 * 
 * TODO: Lab 17 - Implement the GradedItem base class with virtual methods
 */

#ifndef GRADEDITEM_H
#define GRADEDITEM_H

#include <string>
#include <iostream>

class GradedItem {
// ============================================================================
// TODO: Lab 17 - Use 'protected' so derived classes can access
// ============================================================================
protected:
    std::string name;
    float points_earned;
    float points_possible;

public:
    // ========================================================================
    // TODO: Lab 17 - Implement constructors
    // ========================================================================
    
    // Default constructor
    GradedItem() : name(""), points_earned(0), points_possible(0) {}
    
    // Parameterized constructor
    GradedItem(const std::string& n, float earned, float possible)
        : name(n), points_earned(earned), points_possible(possible) {}
    
    // Virtual destructor (important for polymorphism!)
    virtual ~GradedItem() {}
    
    // ========================================================================
    // TODO: Lab 17 - Implement getter methods
    // ========================================================================
    
    std::string getName() const { return name; }
    float getPointsEarned() const { return points_earned; }
    float getPointsPossible() const { return points_possible; }
    
    float getPercentage() const {
        if (points_possible == 0) return 0;
        return (points_earned / points_possible) * 100;
    }
    
    // ========================================================================
    // TODO: Lab 17 - Implement virtual methods for derived classes to override
    // ========================================================================
    
    // Returns the category name (overridden by derived classes)
    virtual std::string getCategory() const { return "General"; }
    
    // Returns the weight for this category (overridden by derived classes)
    virtual float getWeight() const { return 1.0f; }
    
    // Display the item (can be overridden)
    virtual void display() const {
        std::cout << getCategory() << " - " << name << ": "
                  << points_earned << "/" << points_possible
                  << " (" << getPercentage() << "%)\n";
    }
};

#endif // GRADEDITEM_H
