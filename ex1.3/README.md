# Ex1.3: Copy and move semantics for a resource owning class
## Deadline: November 7th, 4pm W

This exercise is part three of three parts of Ex1. The other two parts (Ex1.1 and Ex1.2) were rolled out separately. See also [https://gitlab.tuwien.ac.at/e360251/organization](https://gitlab.tuwien.ac.at/e360251/organization) for an overview and deadlines.

## Structure of files and folders

```
├── CMakeLists.txt                configuration of the project
├── include                       folder with includes of the List-library
│   └── List.hpp                  
├── lib                           folder with sources of the List-library:
│   ├── ListSMF.cpp               ... implementations of SMF (special member functions)  
│   └── List.cpp                  ... implementations other member functions 
├── src
│   └── benchmark.cpp             benchmark executable
└── test
    ├── CMakeLists.txt            configuration for executables of tests
    ├── testasserts.hpp
    ├── Test_copyAssign.cpp       tests copy assignment operator
    ├── Test_copyConstruct.cpp    tests copy constructor
    ├── Test_moveAssign.cpp       tests move assignment operator
    └── Test_moveConstruct.cpp    tests move constructor

```


## Task description

In this exercise, it is your task to extend a basic implementation of a single-linked-list `List` declared in `include/List.hpp`:

```cpp
class List {
public:
  using value_type = double;
  using size_type = std::size_t;

  // nested class
  struct Node {
    value_type value;
    Node *next = nullptr;
    Node(const value_type &);
  };

private:
  Node *_head = nullptr; // root element
  size_type _size = 0;   // current number of nodes in list

public:
  List();                              // default ctor
  List(size_type, const value_type &); // custom ctor
  ~List();                             // dtor

  List(const List &);            // copy ctor
  List(List &&);                 // move ctor
  List &operator=(const List &); // copy assign
  List &operator=(List &&);      // move assign

  size_type size() const;              // access current number of nodes in list
  const Node *data() const;            // obtain root element pointer
  value_type &front();                 // access front element
  void push_front(const value_type &); // push new list element at the front
  void pop_front();                    // pop element at the front
};
```

More specifically, the provided implementation in `lib/List.cpp` contains a user-defined constructor and correct user-defined destructor (along with all other member function implementations).

Additionally, only **defaulted** versions for the following four special member functions are provided in `lib/ListSMF.cpp`:

```cpp
// copy constructor
List::List(const List &other) = default;

// move constructor
List::List(List &&other) = default;

// copy assignment operator
List &List::operator=(const List &other) = default;

// move assignment operator
List &List::operator=(List &&other) = default;
```

You should be able to argue why the defaultet versions are not sufficient for the resource owning class `List`.

It is your task is to implement the *definitions* of these functions in `lib/ListSMF.cpp` according to the needs of the underlying dynamic resources (each node in the list is dynamically allocated).


**Note: Your implementation must strictly be confined to `lib/ListSMF.cpp` and you must not change any other files.**

Prepare yourself for a discussion of your implementation. 

## Implementation and Testing
You are provided with four tests to check the correct funcitonality of your implementation. There is no specific order in which the tests should be executed, as they are independent of each other. There is one test for each SMF:

- Test_copyAssign
- Test_copyConstruct
- Test_moveAssign
- Test_moveConstruct


## Benchmarking

For testing your implementation and its performance, a benchmark is provided in `src/benchmark.cpp`.
Similar to the last exercise it will inform you about the memory location of the *head* of the list before and after each operation.
**Note: Without reasonable implementations of the SMF the benchmark will fail at run time, i.e., the sanitizer will detect incorrect memory access with errors like "double free" or "use after free".**

The executable also measures the runtime of all 4 special member functions. Prepare yourself for a discussion on the runtimes of the different SMFs and why this is the case.

## Building

You can clone, build, and run all tests using:
```
git clone https://gitlab.tuwien.ac.at/e360251/ex1.3.git
cd ex1.3
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
