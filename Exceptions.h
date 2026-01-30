/**
 * Exceptions.h
 * Custom exception classes for the Grade Calculator
 * 
 * TODO: Lab 22 - Implement custom exception hierarchy
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// ============================================================================
// TODO: Lab 22 - Implement base exception class
// ============================================================================

/**
 * Base exception for all Grade Calculator errors
 */
class GradeCalculatorException : public std::runtime_error {
public:
    explicit GradeCalculatorException(const std::string& msg)
        : std::runtime_error(msg) {}
};

// ============================================================================
// TODO: Lab 22 - Implement FileException for file I/O errors
// ============================================================================

/**
 * Exception for file operation errors
 */
class FileException : public GradeCalculatorException {
public:
    explicit FileException(const std::string& msg)
        : GradeCalculatorException("File error: " + msg) {}
};

// ============================================================================
// TODO: Lab 22 - Implement InvalidDataException for data validation errors
// ============================================================================

/**
 * Exception for invalid data/input errors
 */
class InvalidDataException : public GradeCalculatorException {
public:
    explicit InvalidDataException(const std::string& msg)
        : GradeCalculatorException("Invalid data: " + msg) {}
};

// ============================================================================
// TODO: Lab 22 - Implement CategoryException for category-related errors
// ============================================================================

/**
 * Exception for category management errors
 */
class CategoryException : public GradeCalculatorException {
public:
    explicit CategoryException(const std::string& msg)
        : GradeCalculatorException("Category error: " + msg) {}
};

// ============================================================================
// TODO: Lab 22 - Implement WeightException for weight validation errors
// ============================================================================

/**
 * Exception for weight-related errors (weights must sum to 100%)
 */
class WeightException : public GradeCalculatorException {
public:
    explicit WeightException(const std::string& msg)
        : GradeCalculatorException("Weight error: " + msg) {}
};

#endif // EXCEPTIONS_H
