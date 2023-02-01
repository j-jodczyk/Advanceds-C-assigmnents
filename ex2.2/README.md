# Ex2.2: Implementation of a template class (with a templated constructor)
## Deadline: December 5th, 4pm

This exercise is part two of three parts of Ex2. See also [https://gitlab.tuwien.ac.at/e360251/organization](https://gitlab.tuwien.ac.at/e360251/organization) for an overview and deadlines.

## Structure of files and folders

```
├── CMakeLists.txt
├── include
│   ├── Distribution.hpp
│   └── SpaceVector.hpp
├── src
│   └── benchmark.cpp
└── test
    ├── CMakeLists.txt
    ├── testasserts.hpp
    ├── TestA_ClassMembers.cpp
    ├── TestB_Vector.cpp
    ├── TestC_SpaceVector.cpp
    ├── TestD_List.cpp
    └── TestE_Deque.cpp

```

## Task 1: `Distribution` class template (construction from a `std::vector`)

Your first task is to implement a *user-defined type* `Distribution` which holds the *arithmetic mean* and the *standard deviation* of a distribution and fullfills the requirements described below.
(The formulas for *arithmetic mean* and the *standard deviation* are given at the end of this document.)

The type you implement must be called `Distribution` and be a `class` or `struct` template with:

- a single template type, e.g. `template<class T> class {};` or `template<class T> struct {};`
- two public member variables `mean` and `stddev`, both of type `T`
- a public member typedef `value_type` which aliases the template parameter `T`
- two constructors:
  - `Distribution(T mean, T stddev)` which directly initializes the two member variables from the parameters (without any calculations).
  - `Distribution(const std::vector<T> &vec)` which calculates the *arithmetic mean* and the *standard deviation* for the distribution of values present in the `std::vector<T>` and initializes the members with these calculated values.

Further requirements on the two constructors describe above are:
1. an implicit deduction mechanism of the class template parameter `T` must be present.
2. the following types for `T` must be supported:
  - `double`
  - `float`
  - `long`
  - `SpaceVector<double, 3>` (from `SpaceVector.hpp`)

**Hints**: `SpaceVector` already supports the required arithmetic operators to calculate the mean and standard deviation including a `sqrt` function defined in `SpaceVector.hpp` (for the built-in types `std::sqrt` is available in `<cmath>`).


**Hint**: When accessing the elements of the passed `std::vector` object, ideally you would use generic access methods from the beginning (i.e. range-base for loops or iterators), so you do not have to change your code for Task 2.

## Task 2: Extension of the `Distribution` class (to support a set of containers for construction)

The second task is to extend the available construction mechansim to support the calculation of *arithmetic mean* and *standard deviation* from other containers as well.
At least the following container types must be supported:
- `std::vector`
- `std::list`
- `std::deque`

In order to support these construction mechanisms, your constructor has become a template function itself, and `T` needs to be deduced from the passed container template using the template directly or using a deduction guide.

The template parameter `T` must still be deduced implicitly, i.e. without providing it explicitly when calling the constructors.

**Hint**: For standard library containers, the member typedef `value_type` allows to access the type of the stored elements.


## Tests

As usual, you are provided with several tests, which should guide you through the exercise.
Completing them in order will be the simplest approach:
- TestA_ClassMembers.cpp: checks if the prescribed class members and type aliases are accessible and have the right type.
- TestB_Vector.cpp: checks the construction mechanism and calculation for `mean` and `stddev` from a `std::vector` holding `float`s, `double`s, or `long`s.
- TestC_SpaceVector.cpp: checks the construction and calculation from a `std::vector` holding `SpaceVector<double, 3>`s.
- TestD_List.cpp: checks the construction and calculation using a `std::list` as underlying container.
- TestE_Deque.cpp: checks the construction and calculation using a `std::deque` as underlying container.

## Benchmark

A simple benchmark is provided in `src/benchmark.cpp` which will generate random distributions with varying types and use your `Distribution` type to find the *arithmetic mean* and the *standard deviation*.

## Building/Running

You can clone, build, and run all tests using:
```
git clone https://gitlab.tuwien.ac.at/e360251/ex2.2.git
cd ex2.1
mkdir build
cd build
cmake .. -D CMAKE_BUILD_TYPE=ASAN
make
ctest --verbose
```

You can build and run each test individually, e.g. using (from the build folder):
```bash
make TestA_ClassMembers
./test/TestA_ClassMembers
```

To enable building the benchmark executable in release mode run the following commands in your build folder:
```
cmake .. -D BUILD_BENCHMARK=ON        # enable build of benchmark target
cmake .. -D CMAKE_BUILD_TYPE=RELEASE  # sets optimization flags for the compiler
make benchmark
./benchmark
```

## Required formulas

Let's assume we have a set of numbers:

```math
s = \{1, 2, 3, 5, 8, 13 \}
```

### Arithmetic mean

The arithmetic mean is the average of all values in a distribution:

```math
\mu = \sum_{i=1}^n \frac{s_i}{n}= \frac{1 + 2 + 3 + 5 + 8 + 13}{6} = ...
```

### Standard deviation

First, we find the *variance* which is the square of the *standard deviation*.
It is given by the average of the squared difference of each element to the mean:

```math
\sigma^2 =  \sum_{i=1}^n \frac{(s_i - \mu)^2}{n} = ...
```

The square root of the variance is the standard deviation:

```math
\sigma =  \sqrt{\sum_{i=1}^n \frac{(s_i - \mu)^2}{n}} = ...
```
