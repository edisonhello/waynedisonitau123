#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, T;
  cin >> N >> T;
  vector<int> d(N), s(N);
  for (int i = 0; i < N; ++i) {
    cin >> d[i] >> s[i];
  }

  auto Check = [&](double c) {
    double sum = 0;
    for (int i = 0; i < N; ++i) {
      if (s[i] + c <= 0) return false;
      sum += d[i] / (s[i] + c);
    }
    return sum <= T;
  };

  double l = -1E9, r = 1E9;
  for (int it = 0; it < 100; ++it) {
    double m = (l + r) / 2;
    if (Check(m)) r = m;
    else l = m;
  }

  cout << fixed << setprecision(20) << l << "\n";
}

