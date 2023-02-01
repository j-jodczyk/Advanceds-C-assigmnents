#pragma once

#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sstream>

// define test assertion, which will throw if condition is false
#define TEST_ASSERT(condition, message)                                        \
  {                                                                            \
    if (!(condition)) {                                                        \
      throw std::runtime_error(                                                \
          std::string(__FILE__) + std::string(":") +                           \
          std::to_string(__LINE__) + std::string(" in ") +                     \
          std::string(__PRETTY_FUNCTION__) + "\nERROR: " + message);           \
    }                                                                          \
  }

// define assertion to check whether value is within bounds
#define TEST_ASSERT_IN_RANGE(value, lower, upper, message)                     \
  {                                                                            \
    if (!(value >= lower && value <= upper)) {                                 \
      std::ostringstream oss;                                                  \
      oss << std::setprecision(2) << std::fixed;                               \
      oss << "\nEROR: " << message << lower << " <= " << value                 \
          << " <= " << upper << " is not true";                                \
      throw std::runtime_error(std::string(__FILE__) + std::string(":") +      \
                               std::to_string(__LINE__) +                      \
                               std::string(" in ") +                           \
                               std::string(__PRETTY_FUNCTION__) + oss.str());  \
    }                                                                          \
  }

