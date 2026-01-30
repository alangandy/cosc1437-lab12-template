/**
 * Category.h
 * Struct for managing grade categories with custom weights
 * 
 * TODO: Lab 21 - Implement the Category struct for use with std::map
 */

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include "GradedItem.h"

// ============================================================================
// TODO: Lab 21 - Implement the Category struct
// ============================================================================
struct Category {
    std::string name;
    float weight;  // Weight as percentage (e.g., 20.0 for 20%)
    std::vector<GradedItem*> items;
    
    // Default constructor
    Category() : name(""), weight(0) {}
    
    // Parameterized constructor
    Category(const std::string& n, float w) : name(n), weight(w) {}
    
    // ========================================================================
    // TODO: Lab 21 - Implement getTotalEarned()
    // ========================================================================
    float getTotalEarned() const {
        float total = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            total += items[i]->getPointsEarned();
        }
        return total;
    }
    
    // ========================================================================
    // TODO: Lab 21 - Implement getTotalPossible()
    // ========================================================================
    float getTotalPossible() const {
        float total = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            total += items[i]->getPointsPossible();
        }
        return total;
    }
    
    // ========================================================================
    // TODO: Lab 21 - Implement getPercentage() - average of all items
    // ========================================================================
    float getPercentage() const {
        if (items.empty()) return 0;
        float total = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            total += items[i]->getPercentage();
        }
        return total / items.size();
    }
    
    // ========================================================================
    // TODO: Lab 21 - Implement getWeightedContribution()
    // ========================================================================
    float getWeightedContribution() const {
        return getPercentage() * (weight / 100.0f);
    }
    
    // ========================================================================
    // TODO: Lab 21 - Implement getItemCount()
    // ========================================================================
    size_t getItemCount() const {
        return items.size();
    }
};

#endif // CATEGORY_H
