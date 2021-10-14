#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  if (N % 2 == 1 || N == 2) {
    cout << "impossible\n";
    return 0;
  }
  int K = N / 2;
  cout << 1 << " " << (K - 1) << " " << K << "\n";
  cout << "B " << 1 << " " << 0 << " " << "U\n";
  for (int i = 0; i < K - 1; ++i) {
    cout << "A " << 0 << " " << i << " " << "U\n";
    cout << "A " << 0 << " " << i + 1 << " " << "D\n";
  }
  cout << "A " << 0 << " " << K - 1 << " " << "U\n";
}
