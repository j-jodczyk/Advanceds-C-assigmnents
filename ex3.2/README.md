# Ex3.2: Implementation of a smart pointer to handle unique ownership (simplified `std::unique_ptr`)
## Deadline: January 16th 2023, 4pm

This exercise is part two of three parts of Ex3. See also [https://gitlab.tuwien.ac.at/e360251/organization](https://gitlab.tuwien.ac.at/e360251/organization) for an overview and deadlines.

## Structure of files and folders

```
├── CMakeLists.txt
├── include
│   ├── default_deleter.hpp
│   └── unique_ptr.hpp
├── README.md
└── test
    ├── CMakeLists.txt
    ├── TestA_SMF_and_get.cpp
    ├── testasserts.hpp
    ├── TestB_assign_reset_release.cpp
    ├── TestC_compare.cpp
    └── TestD_custom_deleter.cpp
```

## Task1: Implement a simplified `std::unique_ptr`

In this exercise it is your task to implement a *smart pointer* class in the header `include/unique_ptr.hpp`. 
Your implementation `unique_ptr` will be a simplified version of `std::unique_ptr` [(cppref)](https://en.cppreference.com/w/cpp/memory/unique_ptr) as it always uses `delete` to dealloacte the managed resource.

One noticeable simplification is that your class does not support a 'deleter deduction' for array types automatically (you will add a *custom deleter function* later in Task2). This allows implicit type deduction on construction for your type (which is not available for `std::unique_ptr` due to the fact that the returned type from a `new T` is indistinguishable from the returned type from `new T[]`).

### Specification and Tests
Your implementation should provide the following functionality (checked by the test below):

- **TestA_SMF_and_get** checks: 
  - nested types `::pointer` and `::element_type` reflecting the type of the managed resource
  - `get()` to return a raw pointer to the managed resource
  - construction from a raw pointer
  - move construction from other `unique_ptr`
  - move assignment from other `unique_ptr`
  - disabled copy-construction and copy-assign
  - Note: There is no need to implement conversion constructors or conversion assignments between `unique_ptr`s of different template type `T`.
- **TestB_assign_reset_release** checks:
  - `reset(arg)` to delete the currently managed resource and start managing the resource passed via a pointer (`arg`)
  - `reset()` to delete the currently managed resource (i.e., behave the same as `reset(nullptr)`)
  - assignment from `nullptr`, which should have the same behaviour as `reset()`  
  - `release()` to stop management of the currently wrapped resource and return a pointer to the resource
- **TestC_compare** checks:
  - comparison operators `==` and `!=` between two `unique_ptr`s of the same type (should behave like the equivalent raw pointer comparison)
  - comparison operators `==` and `!=` between a `unique_ptr` and a `nullptr` (should behave like a raw pointer comparison with `nullptr`) 
  - implicit conversion to `bool`, i.e. to be used in a condition like this: `if (ptr) {...}` 

## Task2: Custom deleter function

After implementing all of the functionality above, you are required to add support for a *custom deleter* via a function pointer with this signature: `void (*)(T*)`.

You should introduce an additional class member to hold this function pointer and provide an additional constructor with a second parameter to allow to provide a custom deleter function.

If no custom deleter function is supplied (i.e. tests A-C), the template function `default_deleter` in `include/default_deleter.hpp` should be used as default for the deleter function member. 

This custom deleter now allows to handle custom deletion tasks, for example, you can now manage a raw array with your class if you provide the fitting `delete[]` operation via a custom deleter. 

**Hint**: Try to make all previous tests (A-C) work again once you implemented the default deleter before moving TestD.

### Specification and Tests
Your implementation of a custom deleter should provide the following functionaltiy:

- **TestD_custom_deleter** checks: 
  - construction using a custom deleter function pointer as second parameter.
  - invocation of custom deleters on destruction of resource
  - a use case where a raw array (to be deleted via `delete[]`) is wrapped using `unique_ptr`
  - a use case where `FILE` handles are wrapped using `unique_ptr` and a custom deleter function is used to 'close' the handle on the ´FILE´

## Building/Running

You can clone, build, and run all tests using:
```
git clone https://gitlab.tuwien.ac.at/e360251/ex3.2.git
cd ex3.2
mkdir build
cd build
cmake .. -D CMAKE_BUILD_TYPE=ASAN
make
ctest --verbose
```

You can build and run each test individually, e.g. using (from the build folder):
```bash
make TestA_SMF_and_get
./test/TestA_SMF_and_get 
```
