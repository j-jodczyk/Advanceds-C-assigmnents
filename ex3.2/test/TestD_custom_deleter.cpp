#include "testasserts.hpp"

#include <cstdio>
#include <type_traits>
#include <unique_ptr.hpp>

int delete_double_lambda_calls = 0;

// custom deleter for double
int delete_double_calls = 0;
void deleter_double(double *p) {
  delete p;
  ++delete_double_calls;
}

// custom deleter for FILE
int delete_FILE_calls = 0;
void deleter_FILE(FILE *handle) {
  std::fclose(handle);
  ++delete_FILE_calls;
}

// custom deleter for arrays
int delete_array_calls = 0;
void deleter_array_double(double *p) {
  delete[] p;
  ++delete_array_calls;
}

auto open(const char *name, const char *mode) {}

int main() {

  { // custom deleter double
    auto up1 = unique_ptr(new double{}, deleter_double);
    auto up2 = unique_ptr<double>(new double{}, [](double *p) -> void {
      delete p;
      ++delete_double_lambda_calls;
    });
  }
  TEST_ASSERT(delete_double_calls == 1,
              "delete not called after unique_ptr went out of scope");
  TEST_ASSERT(delete_double_lambda_calls == 1,
              "delete not called after unique_ptr went out of scope");

  { // custom deleter for a raw array
    auto up = unique_ptr(new double[10], deleter_array_double);
  }
  TEST_ASSERT(delete_array_calls == 1,
              "delete[] not called after unique_ptr went out of scope");

  { // custom "closer" as deleter
    auto filename = "data.json";
    auto mode = "w+";
    FILE *ptr = std::fopen(filename, mode);
    auto file = unique_ptr(ptr, deleter_FILE);
    TEST_ASSERT(file != nullptr, "filePtr is nullptr after opening")
    fprintf(file.get(), "%s", "{\n  \"TestF\": \"success\"\n}\n");
  }
  TEST_ASSERT(delete_FILE_calls == 1,
              "fclose not called after unique_ptr went out of scope");

  return 0;
}