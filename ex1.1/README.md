# Ex1.1: Comparing reference/move/value semantics 
## Deadline: November 7th, 4pm 

This exercise is one of three parts of Ex1. The other two parts (Ex1.2 and Ex1.3) will be rolled out separately. See also [https://gitlab.tuwien.ac.at/e360251/organization](https://gitlab.tuwien.ac.at/e360251/organization) for an overview and deadlines.

## Structure of files and folders

```
├── CMakeLists.txt          configuration of the project
├── include                 folder with includes of the Widget-library
│   └── Widget.hpp
├── lib                     folder with sources of the Widget-library
│   └── Widget.cpp
├── src
│   └── benchmark.cpp       benchmark executable 
└── test                    folder with tests
    ├── CMakeLists.txt      configuration for executables of tests
    ├── testasserts.hpp     contains helper macro 'TEST_ASSERT'    
    ├── TestA_rref.cpp      tests function 'rref::init'
    ├── TestB_lref.cpp      tests function 'lref::init'
    └── TestC_value.cpp     tests function 'value::init'
```

## Task description

This exercise deals with a `Widget` type which looks like this:
```C++
using Vector = std::vector<double>

struct Widget {
  Vector vec;
};
```
`Widget` has a single non-reference member `vec` which is of type `Vector = std::vector<dobule>`.

Your task is to complete the implementaton of three types of initialization functions `init(...)`, so they are as efficient as possible, i.e. using `std::move()`.
The tests in the folder `tests` will detect whether you have found the most efficient solution and will fail if you have not, giving you hints what the problem is.

All three `init` functions initialize a `Widget` using an existing `Vector` object which is passed as function parameter. 

Note: They are defined in different namespaces so their definitions do not collide. These namespaces are `rvref`, `lvref`, `value`, which are defined in `include/Widget.cpp`.

You are only allowed to change the code in the function body of the three `init` functions in `lib/Widget.cpp`.

Finally, you should benchmark your implementations using the `benchmark` executable generated from the `src/benchmark.cpp` file.
Prepare yourself for a discussion on the obtained runtime differences when benchmarking your implementations.

## A: Init using rvalue reference argument (move semantics)

The function takes a single argument of type 'rvalue reference to `Vector`' and returns a `Widget` by value:
```C++
Widget rvref::init(Vector &&rref) {
  return Widget{/* ??? */};
};
```
Your task is to change the way `Widget` is initialized and make 'best use' of the rvalue reference.
The function parameter is of type **rvalue reference and only binds to movable objects**, which means it can be 'moved into' the returned `Widget` object for performance reasons.

## B: Init using lvalue reference argument (reference semantics)

The function takes a single argument of type 'lvalue reference to `Vector`'  and returns a `Widget` by value:
```C++
Widget lvref::init(Vector &lref) {
  return Widget{/* ??? */};
};
```
Again, it is your task to implement the function. 
The function parameter is of type **lvalue reference and only binds to lvalue objects**.
Therefore, the `Vector` should not be 'moved into' the `Widget` but instead has to be copied.

## C: Init using by-value argument (value semantics)

The function takes a single non-reference argument of type `Vector` and returns a `Widget` by value:
```C++
Widget value::init(Vector vec) {
  return Widget{/* ??? */};
};
```

The function parameter is **Vector and is a local object**. This means that passed objects can be moved **or** copied into it.
Again, it is your task to implement the function and to make 'best use' of the local `Vector` object which is available (in form of the function argument).

## Benchmarking

The code in `src/benchmark.cpp` measures the runtime of all three initialization functions by using the different init functions to initialize `Widget` object with large `Vector` objects. For example:

```C++
rvref::init(std::move(vec));
```

The output of running the executable `benchmark` before you have changed anything will look similar to:

```
rvref::init(Vector&&) called as rvref::init(std::move(vec))  1.97e-02 s
lvref::init(Vector&)  called as lvref::init(vec)             2.00e-02 s
value::init(Vector)   called as value::init(std::move(vec))  2.22e-02 s
value::init(Vector)   called as value::init(vec)             3.83e-02 s
```
*Note that `value::init` is tested twice: once using an r-value reference using `std::move` and once using an l-value reference.*

Initiallly, the first three invocations take roughly the same time and only the 4th is roughly 2 times slower. Once you have optimized the code, some of the functions should be roughly ten times as fast as the others.

Prepare yourself for a discussion on the results of the benchmark and why some functions are faster than others.

## Building

You can clone, build, and run all tests using:
```
git clone https://gitlab.tuwien.ac.at/e360251/ex1.1.git
cd ex1.1
mkdir build
cd build
cmake .. -D CMAKE_BUILD_TYPE=ASAN
make
ctest --verbose
```

For a meaningful benchmark, it is necessary to use the CMake build type `Release` which enables optimizations. It can be set using the following command in the build folder:
```
cmake .. -D CMAKE_BUILD_TYPE=RELEASE
make benchmark
./benchmark
```
