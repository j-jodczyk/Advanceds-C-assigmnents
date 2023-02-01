#include <Curl.hpp>       // namespace curl
#include <TimedCache.hpp> // namespace tcache

#include <chrono>   // timing
#include <iostream> // printing
#include <string>   // string

void print_head_tail(const std::string &str, std::size_t n) {
  std::cout << str.substr(0, n) << " ... " << str.substr(str.size() - n)
            << std::endl;
}

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double, std::milli>;

int main(void) {
  // instead of the direct queries

  //curl::Curl geturl;
  tcache::TimedCache timedCache(0.5);

  {
    auto start = Clock::now();
    auto content = timedCache.get("https://tiss.tuwien.ac.at//api/course/360251-2022W");
    print_head_tail(content, 40);
    auto stop = Clock::now();
    std::cout << "lookup took:" << Duration(stop - start).count() << "ms"
              << std::endl;
  }
  {
    auto start = Clock::now();
    auto content = timedCache.get("https://tiss.tuwien.ac.at//api/course/360251-2022W");
    print_head_tail(content, 40);
    auto stop = Clock::now();
    std::cout << "lookup took:" << Duration(stop - start).count() << "ms"
              << std::endl;
  }
  {
    auto start = Clock::now();
    auto content = timedCache.get("https://tiss.tuwien.ac.at//api/course/360251-2022W");
    auto stop = Clock::now();
    print_head_tail(content, 40);
    std::cout << "lookup took:" << Duration(stop - start).count() << "ms"
              << std::endl;
  }
  {
    auto start = Clock::now();
    auto content = timedCache.get("https://tiss.tuwien.ac.at//api/course/360251-2021W");
    print_head_tail(content, 40);
    auto stop = Clock::now();
    std::cout << "lookup took:" << Duration(stop - start).count() << "ms"
              << std::endl;
  }

  return 0;
}