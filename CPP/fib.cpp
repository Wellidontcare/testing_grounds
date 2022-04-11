#include <iostream>

auto fib(int64_t n) -> int64_t {
  if (n < 2) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

auto main() -> int { std::cout << fib(25) << "\n"; }
