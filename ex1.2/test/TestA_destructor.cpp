
#include <iostream>
#include <Vector.hpp>
#include "testasserts.hpp"

int main() {
  { // start a new scope
    Vector vec(7, 1.6180339887);
    std::cout << "Initialized Vector with " << vec.size() << " Elements with value " << vec[0] << std::endl;
  }
  // vec goes out of scope here
  // therefore the destructor is called.
  // if you have not implemented it correctly,
  // the address sanitizer of your compiler will
  // output an error message when your program
  // finishes since there is still some memory
  // allocated in the end.

  // NOTE: there is no way to check this at compile time
  // in C++, which is why we need to be very
  // careful with pointers
  
  return 0;
}