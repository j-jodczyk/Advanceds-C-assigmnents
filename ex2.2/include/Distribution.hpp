#pragma once

#include <cmath>
#include <type_traits>
#include <vector>

template <typename T>
struct Distribution {
  typedef T value_type;
  value_type mean;
  value_type stddev;

  Distribution(T mean, T stddev) : mean(mean), stddev(stddev){}
  // Distribution(const std::vector<T>& data) : mean(0), stddev(0){
  //   for (value_type el : data) {
  //     mean = mean + el;
  //   }
  //   mean = mean / data.size();
  //   for (value_type el : data) {
  //     stddev = stddev + (el - mean) * (el - mean);
  //   }
  //   stddev = sqrt(stddev/data.size());
  // }
  template <template <typename> class C>
  Distribution(const C<T> &data) : mean(0), stddev(0) {
    for (auto el : data) {
      mean = mean + el;
    }
    mean = mean / data.size();
    for (auto el : data) {
      stddev = stddev + (el - mean) * (el - mean);
    }
    stddev = sqrt(stddev/data.size());
  }
};

/*
  Task 1: (Tests A,B)
  Implement a type "Distribution" here with the following properties:
  - "Distribution" should be a class template with a single template type
  - two public member variables "mean" and "stddev"
  - public member typedef "value_type" which aliases the template parameter
  - two constructors:
    - Distribution(T mean, T stddev) which sets the two member variables
    - Distribution(const std::vector<T> &data) which calculates
      the two member variables from a Distribution of data
  Task 2: (Tests C,D,E)
  Change the constructor "Distribution(const std::vector<T>&)" so it
  accepts any STL data structure (not just std::vector) and
  the class template parameter T is still deduced automatically,
  so an object can be constructed using "Distribution(<anySTLcontainer>)"
*/
