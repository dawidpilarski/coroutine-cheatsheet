#include <cppcoro/generator.hpp>

cppcoro::generator<unsigned long long> fibonacci_gen() {
  std::array arr{0ull, 0ull};
  unsigned long long result=0;

  do {
    co_yield result;
    if(result == 0 and arr == std::array{0ull, 0ull})
      result = 1;
    else if (result == 1 and arr == std::array{0ull, 0ull})
      arr = {0, 1};
    else{
      arr[0] = arr[1];
      arr[1] = result;
      result = arr[0] + arr[1];
    }
  } while (result >= arr[1]);
}