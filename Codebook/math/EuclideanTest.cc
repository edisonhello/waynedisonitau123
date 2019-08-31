#include <cassert>
#include <iostream>
#include <random>

int64_t f(int64_t a, int64_t b, int64_t c, int64_t n) {
  if (a >= c || b >= c)
    return (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1) +
           f(a % c, b % c, c, n);
  if (n < 0 || a == 0) return 0;
  int64_t m = (a * n + b) / c;
  return n * m - f(c, c - b - 1, a, m - 1);
}

int64_t h(int64_t, int64_t, int64_t, int64_t);

int64_t g(int64_t a, int64_t b, int64_t c, int64_t n) {
  if (a >= c || b >= c)
    return (a / c) * (n * (n + 1) * (2 * n + 1) / 6) +
           (b / c) * (n * (n + 1) / 2) + g(a % c, b % c, c, n);
  if (n < 0 || a == 0) return 0;
  int64_t m = (a * n + b) / c;
  return (n * (n + 1) * m - f(c, c - b - 1, a, m - 1) -
          h(c, c - b - 1, a, m - 1)) /
         2;
}

int64_t h(int64_t a, int64_t b, int64_t c, int64_t n) {
  if (a >= c || b >= c)
    return (a / c) * (a / c) * (n * (n + 1) * (2 * n + 1) / 6) +
           (b / c) * (b / c) * (n + 1) + (a / c) * (b / c) * n * (n + 1) +
           h(a % c, b % c, c, n) + 2 * (a / c) * g(a % c, b % c, c, n) +
           2 * (b / c) * f(a % c, b % c, c, n);
  if (n < 0 || a == 0) return 0;
  int64_t m = (a * n + b) / c;
  return n * m * (m + 1) - 2 * g(c, c - b - 1, a, m - 1) -
         2 * f(c, c - b - 1, a, m - 1) - f(a, b, c, n);
}

namespace bf {

int64_t f(int64_t a, int64_t b, int64_t c, int64_t n) {
  int64_t res = 0;
  for (int i = 0; i <= n; ++i) res += (a * i + b) / c;
  return res;
}

int64_t g(int64_t a, int64_t b, int64_t c, int64_t n) {
  int64_t res = 0;
  for (int i = 0; i <= n; ++i) res += i * ((a * i + b) / c);
  return res;
}

int64_t h(int64_t a, int64_t b, int64_t c, int64_t n) {
  int64_t res = 0;
  for (int i = 0; i <= n; ++i) res += ((a * i + b) / c) * ((a * i + b) / c);
  return res;
}

}  // namespace bf

int main() {
  std::mt19937 rng(123214);
  std::uniform_int_distribution<int> dis(0, 1023);

  for (int i = 0; i < 100000000; ++i) {
    if (i % 100 == 0) std::cout << "i = " << i << std::endl;
    int a = dis(rng), b = dis(rng), c = dis(rng), n = dis(rng);
    while (c == 0) c = dis(rng);
    if (bf::f(a, b, c, n) != f(a, b, c, n)) {
      std::cout << "f: "
                << "a = " << a << " b = " << b << " c = " << c << " n = " << n
                << std::endl;
      exit(0);
    }
    if (bf::g(a, b, c, n) != g(a, b, c, n)) {
      std::cout << "g: "
                << "a = " << a << " b = " << b << " c = " << c << " n = " << n
                << std::endl;
      exit(0);
    }
    if (bf::h(a, b, c, n) != h(a, b, c, n)) {
      std::cout << "h: "
                << "a = " << a << " b = " << b << " c = " << c << " n = " << n
                << std::endl;
      exit(0);
    }
  }
}
