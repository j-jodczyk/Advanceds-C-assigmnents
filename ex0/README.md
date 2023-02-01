# Ex0: Introductory Exercise 
## Deadline: October 17, 4pm

- This is an introductory exercise.
- It aims to help you to get started with your own environment/configuration.
- The exercise is not graded, nevertheless we require a submission to make you comfortable with the modalities for the later exercises.
- It is **not** a problem if you do not complete all required function implementations (but you should at least manage to complete 2 of 7). 

## Prerequisits

- git
- CMake 
- Toolchain for C++17

## Overview

- You are provided a set of function specifications. 
- It is your task to implement these functions according to the described specification. 
- A single test is already provided for each function.  
- All functions are bundled into a library with the name `helper_functions`  
- Each test links to this library and performs some checks on one of the functions.
- You should **solely** edit code in the file `src/helper_functions.cpp`
- The helper functions all deal with a vector-like type, namely: `using Vector = std::vector<double>` 

## Project Layout

The project structure is provided and **must not be altered**:
```
├── CMakeLists.txt
├── include
│   └── helper_functions.hpp
├── README.md
├── src
│   └── helper_functions.cpp
└── test
    ├── CMakeLists.txt
    ├── test_concat.cpp
    ├── test_copy.cpp 
    ├── test_fill_uniform_random.cpp
    ├── test_print.cpp
    ├── test_reset.cpp
    ├── test_sort.cpp
    └── test_swap.cpp
```

## Function Specification

- Note: You can also use the affiliated tests to infer required functionality
- Note: `include/helper_functions.hpp` contains all declarations and types
- Note: You should only implement in `src/helper_functions.cpp`

### Function `print`

The vector (passed as argument) is printed to the console.

```cpp
void print(const Vector &vec);
```

### Function `reset`

The vector (passed as argument) is reset (i.e., all elements are removed).

```cpp
void reset(Vector &vec);
```

### Function `copy` 

A copy of the vector (passed as argument) is returned.

```cpp
Vector copy(const Vector &vec);
```

### Function `concat` 
The two vectors (which are passed as arguments) are concatenated and returned.

```cpp
Vector concat(const Vector &a, const Vector &b); 
```

### Function `swap`

The elements of the two vectors (passed as arguments) are swapped.

```cpp
void swap(Vector &a, Vector &b);
```

### Function `test_fill_uniform_random` 

The vector (passed as argument) is resized to `n` elements and filled with random numbers uniformly distributed in the interval `lower` to `upper`.

```cpp
void fill_uniform_random(Vector &vec, std::size_t n, 
                         double lower,
                         double upper);
```

### Function `sort`

The vector (passed as argument) is sorted (in-place) according to a comparison function (which is also passed) returning true if the first argument `a` occurs before the second `b` in a sorted sequence.

```cpp
using Compare = std::function<bool(const double &a, const double &b)>;
void sort(Vector &vec, Compare comp);
```
