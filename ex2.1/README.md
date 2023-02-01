# Ex2.1: Wrapper function (perfect forwarding) to track execution time of function calls
## Deadline: December 5th, 4pm

This exercise is part one of three parts of Ex2. See also [https://gitlab.tuwien.ac.at/e360251/organization](https://gitlab.tuwien.ac.at/e360251/organization) for an overview and deadlines.

## Structure of files and folders

```
├── CMakeLists.txt
├── include
│   └── measureTime.hpp
├── README.md
├── src
│   └── measureTransform.cpp
└── test
    ├── CMakeLists.txt
    ├── testasserts.hpp
    ├── TestA_two_args_same_type.cpp
    ├── TestB_two_args_any_types.cpp
    └── TestC_any_args_any_types.cpp
```


## Task description

In this exercise, it is your task to generialize/adopt a provided wrapper-functionality to measure the run time of *callables*, which can be functions or function objects which can be *called* using the `()` operator.

An inflexible implementation of `measureTime` --- which only works for functions with two parameters of the **same type** --- is provided as a starting point (`include/measureTime.hpp`):

```C++
template<class CALLABLE, class Arg>
double measureTime(CALLABLE callable, Arg&& a, Arg&& b) {
  using Clock = std::chrono::high_resolution_clock;
  auto start = Clock::now();    // start time measurement

  // forward the two arguments to the callable `call`
  callable(std::forward<Arg>(a), std::forward<Arg>(b));

  auto stop = Clock::now();     // stop time measurement
  return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}
```

However, if two parameters with different type are passed to `measureTime`, this implementation obviously fails.
The provided implementation will also fail if the number of parameters is not exactly 2.

Be aware that your solution must support any number of parameters and therefore adding overloads with different numbers of arguments will not lead you to a reasonable solution.
In order to allow for any number of different parameters, you should use

- **perfect forwarding** to support any combination of "value-ness", "const-ness", and "reference-ness" for the list of arguments in combination with a
- **variadic template (template parameter pack)** to be able to forward any number of arguments.

You have to implement the wrapping-functionality solely in `include/measureTime.hpp` and are not allowed to change any other files.

**Note**: For this exercise, you can assume that the `measureTime` wrapper-functionality only needs to support functions with return type `void` (and the return type of `measureTime` is used to report the runtime of the wrapped function call).

Prepare yourself for a discussion of your submitted solution (including an interpretation of your benchmark results).

## Tests

The first test `tests/TestA_two_args_same_type.cpp` works out of the box and should show you how perfect forwarding will be used:
```C++
  double a = 1.;
  double b = 3.;
  // normal function call
  add(a, b);

  // function call to measure the runtime
  double duration = measureTime(add, a, b);
```

The other two tests `TestB_two_args_any_types` and `TestC_any_args_any_types` do what their names suggest and initially fail (before you adopt the implementation).

## Benchmark

Once your implementation passes all tests, you can run the benchmarks provided in `src/measureTransform.cpp` to see how different transformations of vectors (using `std::transform`) perform. (You are not required to understand the benchmarked functions in detail).\

Note: the benchmark is not built in the default CMake settings of this project, see below how to enable the built of the benchmark.

## Building/Running

You can clone, build, and run all tests using:
```
git clone https://gitlab.tuwien.ac.at/e360251/ex2.1.git
cd ex2.1
mkdir build
cd build
cmake .. -D CMAKE_BUILD_TYPE=ASAN
make
ctest --verbose
```

You can build and run each test individually, e.g. using (from the build folder):
```bash
make TestA_two_args_same_type 
./test/TestA_two_args_same_type 
```

To enable building the benchmark executable in release mode run the following commands in your build folder:
```
cmake .. -D BUILD_BENCHMARK=ON        # enable build of benchmark target
cmake .. -D CMAKE_BUILD_TYPE=RELEASE  # sets optimization flags for the compiler
make benchmark
./benchmark
```
