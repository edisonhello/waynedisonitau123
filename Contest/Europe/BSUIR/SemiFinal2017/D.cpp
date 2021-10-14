#include <iostream>

int main() {
  int N;
  std::cin >> N;
  int ans = 1;
  constexpr int kP = 1'000'000'000 + 7;
  for (int i = 0; i < N * N + (N - 1) * (N + 1) - 1; ++i) {
    ans = (ans + ans) % kP;
  }
  std::cout << ans << "\n";
}
