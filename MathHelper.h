/**
 * MathHelper.h
 * Template functions for mathematical operations
 * 
 * TODO: Lab 19 - Implement template functions for generic math operations
 */

#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <vector>
#include <stdexcept>

namespace MathHelper {

    // ========================================================================
    // TODO: Lab 19 - Implement sum() template function
    // ========================================================================
    template <typename T>
    T sum(const std::vector<T>& values) {
        T total = T();  // Zero-initialize
        for (size_t i = 0; i < values.size(); ++i) {
            total += values[i];
        }
        return total;
    }

    // ========================================================================
    // TODO: Lab 19 - Implement average() template function
    // ========================================================================
    template <typename T>
    double average(const std::vector<T>& values) {
        if (values.empty()) return 0.0;
        return static_cast<double>(sum(values)) / values.size();
    }

    // ========================================================================
    // TODO: Lab 19 - Implement minimum() template function
    // ========================================================================
    template <typename T>
    T minimum(const std::vector<T>& values) {
        if (values.empty()) {
            throw std::runtime_error("Cannot find minimum of empty vector");
        }
        T min = values[0];
        for (size_t i = 1; i < values.size(); ++i) {
            if (values[i] < min) {
                min = values[i];
            }
        }
        return min;
    }

    // ========================================================================
    // TODO: Lab 19 - Implement maximum() template function
    // ========================================================================
    template <typename T>
    T maximum(const std::vector<T>& values) {
        if (values.empty()) {
            throw std::runtime_error("Cannot find maximum of empty vector");
        }
        T max = values[0];
        for (size_t i = 1; i < values.size(); ++i) {
            if (values[i] > max) {
                max = values[i];
            }
        }
        return max;
    }

    // ========================================================================
    // TODO: Lab 19 - Implement countAbove() template function
    // ========================================================================
    template <typename T>
    int countAbove(const std::vector<T>& values, T threshold) {
        int count = 0;
        for (size_t i = 0; i < values.size(); ++i) {
            if (values[i] > threshold) {
                count++;
            }
        }
        return count;
    }

    // ========================================================================
    // TODO: Lab 19 - Implement countBelow() template function
    // ========================================================================
    template <typename T>
    int countBelow(const std::vector<T>& values, T threshold) {
        int count = 0;
        for (size_t i = 0; i < values.size(); ++i) {
            if (values[i] < threshold) {
                count++;
            }
        }
        return count;
    }

    // ========================================================================
    // TODO: Lab 19 - Implement percentage() template function
    // ========================================================================
    template <typename T>
    double percentage(T part, T whole) {
        if (whole == T()) return 0.0;
        return (static_cast<double>(part) / whole) * 100.0;
    }

    // ========================================================================
    // TODO: Lab 19 - Implement clamp() template function
    // ========================================================================
    template <typename T>
    T clamp(T value, T min, T max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    // ========================================================================
    // TODO: Lab 19 - Implement inRange() template function
    // ========================================================================
    template <typename T>
    bool inRange(T value, T min, T max) {
        return value >= min && value <= max;
    }

}  // namespace MathHelper

#endif // MATHHELPER_H
