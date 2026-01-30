/**
 * InputHelper.h
 * Utility functions for validated user input
 * 
 * TODO: Lab 18 - Implement input validation functions
 */

#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <iostream>
#include <string>
#include <limits>

namespace InputHelper {

    // ========================================================================
    // TODO: Lab 18 - Implement clearInput() to reset cin after errors
    // ========================================================================
    inline void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // ========================================================================
    // TODO: Lab 18 - Implement getInt() with range validation
    // ========================================================================
    inline int getInt(const std::string& prompt, int min, int max) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            
            if (std::cin.fail()) {
                clearInput();
                std::cout << "  Error: Please enter a valid number.\n";
            } else if (value < min || value > max) {
                clearInput();
                std::cout << "  Error: Must be between " << min << " and " << max << ".\n";
            } else {
                clearInput();
                return value;
            }
        }
    }

    // ========================================================================
    // TODO: Lab 18 - Implement getFloat() with range validation
    // ========================================================================
    inline float getFloat(const std::string& prompt, float min, float max) {
        float value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            
            if (std::cin.fail()) {
                clearInput();
                std::cout << "  Error: Please enter a valid number.\n";
            } else if (value < min || value > max) {
                clearInput();
                std::cout << "  Error: Must be between " << min << " and " << max << ".\n";
            } else {
                clearInput();
                return value;
            }
        }
    }

    // ========================================================================
    // TODO: Lab 18 - Implement getPercentage() (0-100 range)
    // ========================================================================
    inline float getPercentage(const std::string& prompt) {
        return getFloat(prompt, 0.0f, 100.0f);
    }

    // ========================================================================
    // TODO: Lab 18 - Implement getString() with empty check
    // ========================================================================
    inline std::string getString(const std::string& prompt) {
        std::string value;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, value);
            
            if (value.empty()) {
                std::cout << "  Error: Please enter a value.\n";
            } else {
                return value;
            }
        }
    }

    // ========================================================================
    // TODO: Lab 18 - Implement getYesNo() for y/n prompts
    // ========================================================================
    inline bool getYesNo(const std::string& prompt) {
        char response;
        while (true) {
            std::cout << prompt << " (y/n): ";
            std::cin >> response;
            clearInput();
            
            if (response == 'y' || response == 'Y') return true;
            if (response == 'n' || response == 'N') return false;
            
            std::cout << "  Error: Please enter 'y' or 'n'.\n";
        }
    }

    // ========================================================================
    // TODO: Lab 18 - Implement getMenuChoice() for menu selection
    // ========================================================================
    inline int getMenuChoice(int min, int max) {
        return getInt("Enter choice: ", min, max);
    }

    // ========================================================================
    // TODO: Lab 18 - Implement pressEnterToContinue()
    // ========================================================================
    inline void pressEnterToContinue() {
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

}  // namespace InputHelper

#endif // INPUTHELPER_H
