# Ex1.2: Constructors and destructor for a resource owning class 
## Deadline: November 7th, 4pm 

This exercise is part two of three parts of Ex1. The other two parts (Ex1.1 and Ex1.3) are rolled out separately. See also [https://gitlab.tuwien.ac.at/e360251/organization](https://gitlab.tuwien.ac.at/e360251/organization) for an overview and deadlines.


## Structure of files and folders

```
├── CMakeLists.txt                  configuration of the project
├── include                         folder with includes of the Vector-library
│   └── Vector.hpp  
├── lib                             folder with sources of the Vector-library:
│   ├── VectorSMF.cpp               ... implementations of SMF (special member functions)
│   └── Vector.cpp                  ... implementations other member functions         
├── src     
│   └── benchmark.cpp               benchmark executable
└── test
    ├── CMakeLists.txt              configuration for executables of tests
    ├── testasserts.hpp    
    ├── TestA_destructor.cpp        tests destructor of Vector
    ├── TestB_copyConstructor.cpp   tests copy constructor of Vector
    └── TestC_moveConstructor.cpp   tests move constructor of Vector

```

## Task description

This exercise deals with a `Vector` type. `Vector` implements a minimal subset of the interface of a std::vector. Its private data member `_data` stores a pointer to dynamically allocated memory which is used to store the elements contiguously in memory (std::vector works the same way):

```c++
class Vector {
public:
  using value_type = double;
  using size_type = std::size_t;

private:
  size_type _size = 0;
  value_type *_data = nullptr;

public:
  Vector();                                    // default ctor
  Vector(size_type n, const value_type &init); // ctor with size and init

  Vector(const Vector &); // copy constructor
  Vector(Vector &&);      // move constructor
  ~Vector();              // destructor

  value_type *data();                // getter for _data
  size_type size();                  // getter for _size
  value_type &operator[](size_type); // acccess via []
};
```

The `Vector` class is declared in `include/Vector.hpp` (see above) and defined in `lib/Vector.cpp`.

```C++
#include "Vector.hpp"

// default constructor
Vector::Vector() {}

// Constructor
Vector::Vector(size_type size, const value_type &value)
    : _size(size), _data(new Vector::value_type[size]) {
  for (std::size_t i = 0; i < _size; ++i) {
    _data[i] = value;
  }
}

// access to raw pointer to the data
Vector::value_type *Vector::data() { return _data; }

// get the number of elements stored in the vector
Vector::size_type Vector::size() { return _size; }

// access an element of the vector (obtaining a reference)
Vector::value_type &Vector::operator[](size_type pos) { return _data[pos]; }
```

**Defective implementations** of the three special member functions (SMFs) of `Vector` are provided in `lib/VectorSMF.cpp`:

```C++
#include "Vector.hpp"

// copy constructor
Vector::Vector(const Vector &other) = default;

// move constructor
Vector::Vector(Vector &&other) = default;

// destructor
Vector::~Vector() = default;
```

You should be able to argue why the *defaulted* versions are defective!

It is your task to change these three *defaulted* special member functions of `Vector` to match the demands originating from the ownership of the dynamic resource pointed to by `_data`.

**Note: You should only change the file `lib/VectorSMF.cpp` since all other files will not be considered during submission**. 



Prepare yourself for a discussion of your implementation.

## Implementation and Testing
You are provided with three tests to check the correct functionality of your implementation. These will warn you about memory issues giving you some hints where the problems may be:

- TestA_destructor
- TestB_copyConstructor
- TestC_moveConstructor

The best starting point is implementing the destructor `~Vector`, because it is needed everytime `Vector` is used. Once your destructor passes `TestA_destructor` you can move on to the copy and move constructors.

## Benchmarking
For testing your implementation and its performance, a benchmark is provided in `src/benchmark.cpp`. 

It provides you with hints about the memory location of the allocated data. The initial output reflects how the copy and move constructors do not behave as expected for the data structure:
```
Copy:
Old data before  | New data after   | Old data after
  0x7f0b8f88a010 |   0x7f0b8f88a010 | 0x7f0b8f88a010     
# When old data is copied into new data, they should have different memory locations

Move:
Old data before  | New data after   | Old Data after
  0x7f0b8f88a010 |   0x7f0b8f88a010 | 0x7f0b8f88a010
  # When old data is copied into new data, old data should not know about the memory location any more
```

The executable also measures the runtime of the different constructors. 
For the *defaulted* special member functions, the runtime comparison is not yet meaningful; the output looks similar to this:
```
Copy constructor Vector(const Vector&)  called as Vector(vec)             4.90e-08 s
Move constructor Vector(Vector&&)       called as Vector(std::move(vec))  9.92e-08 s
```
After corretly impelementing all constructors you can expect the move construction to be much faster (in this setup about an order of magnitude) than the copy constructor.

## Building

You can clone, build, and run all tests using:
```
git clone https://gitlab.tuwien.ac.at/e360251/ex1.2.git
cd ex1.2
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
