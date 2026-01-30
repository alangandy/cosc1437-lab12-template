/**
 * FileManager.h
 * File operations for saving and loading grade data
 * 
 * TODO: Lab 22 - Implement file save/load with exception handling
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <string>
#include <map>
#include "Category.h"
#include "Exceptions.h"

namespace FileManager {

    // ========================================================================
    // TODO: Lab 22 - Implement saveToFile() with exception handling
    // ========================================================================
    
    /**
     * Saves all grade data to a file
     * 
     * File format:
     * Line 1-4: Grade thresholds (A, B, C, D percentages)
     * Line 5: Number of categories
     * For each category:
     *   - Category name
     *   - Category weight
     *   - Number of items
     *   - For each item: name, earned, possible (3 lines each)
     * 
     * @throws FileException if file cannot be opened or write fails
     */
    inline void saveToFile(const std::string& filename,
                          const std::map<std::string, Category>& categories,
                          float A_pct, float B_pct, float C_pct, float D_pct) {
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            throw FileException("Could not open file for writing: " + filename);
        }
        
        try {
            // Write grade thresholds
            file << A_pct << '\n';
            file << B_pct << '\n';
            file << C_pct << '\n';
            file << D_pct << '\n';
            
            // Write number of categories
            file << categories.size() << '\n';
            
            // Write each category
            for (const auto& pair : categories) {
                const Category& cat = pair.second;
                
                file << cat.name << '\n';
                file << cat.weight << '\n';
                file << cat.items.size() << '\n';
                
                // Write each item in the category
                for (const GradedItem* item : cat.items) {
                    file << item->getName() << '\n';
                    file << item->getPointsEarned() << '\n';
                    file << item->getPointsPossible() << '\n';
                }
            }
            
            if (file.fail()) {
                throw FileException("Write operation failed");
            }
            
            file.close();
            
        } catch (...) {
            file.close();
            throw;  // Re-throw the exception
        }
    }

    // ========================================================================
    // TODO: Lab 22 - Implement loadFromFile() with exception handling
    // ========================================================================
    
    /**
     * Loads grade data from a file
     * 
     * @return true if file was loaded successfully, false if file doesn't exist
     * @throws InvalidDataException if file format is incorrect
     */
    inline bool loadFromFile(const std::string& filename,
                            std::map<std::string, Category>& categories,
                            float& A_pct, float& B_pct, float& C_pct, float& D_pct) {
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            return false;  // File doesn't exist - not an error
        }
        
        try {
            // Clean up existing data
            for (auto& pair : categories) {
                for (GradedItem* item : pair.second.items) {
                    delete item;
                }
            }
            categories.clear();
            
            // Read grade thresholds
            if (!(file >> A_pct >> B_pct >> C_pct >> D_pct)) {
                throw InvalidDataException("Could not read grade thresholds");
            }
            
            // Validate thresholds
            if (A_pct < B_pct || B_pct < C_pct || C_pct < D_pct) {
                throw InvalidDataException("Grade thresholds must be in descending order");
            }
            
            // Read number of categories
            size_t numCategories;
            if (!(file >> numCategories)) {
                throw InvalidDataException("Could not read category count");
            }
            file.ignore();  // Skip newline
            
            // Read each category
            for (size_t i = 0; i < numCategories; ++i) {
                std::string catName;
                float weight;
                size_t numItems;
                
                std::getline(file, catName);
                if (!(file >> weight >> numItems)) {
                    throw InvalidDataException("Could not read category data");
                }
                file.ignore();
                
                // Validate weight
                if (weight < 0 || weight > 100) {
                    throw InvalidDataException("Category weight out of range: " + catName);
                }
                
                Category cat(catName, weight);
                
                // Read items for this category
                for (size_t j = 0; j < numItems; ++j) {
                    std::string itemName;
                    float earned, possible;
                    
                    std::getline(file, itemName);
                    if (!(file >> earned >> possible)) {
                        throw InvalidDataException("Could not read item data");
                    }
                    file.ignore();
                    
                    // Validate item data
                    if (possible <= 0) {
                        throw InvalidDataException("Points possible must be > 0");
                    }
                    if (earned < 0 || earned > possible) {
                        throw InvalidDataException("Points earned out of range");
                    }
                    
                    cat.items.push_back(new GradedItem(itemName, earned, possible));
                }
                
                categories[catName] = cat;
            }
            
            file.close();
            return true;
            
        } catch (...) {
            file.close();
            throw;  // Re-throw the exception
        }
    }

}  // namespace FileManager

#endif // FILEMANAGER_H
