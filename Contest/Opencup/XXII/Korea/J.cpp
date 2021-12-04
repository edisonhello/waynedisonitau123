#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> x(N), a(N);
  for (int i = 0; i < N; ++i) {
    cin >> x[i] >> a[i];
  }
  vector<int> divs;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (a[i] != a[j]) {
        int v = abs(x[i] - x[j]);
        for (int p = 1; 1LL * p * p <= v; ++p) {
          if (v % p == 0) {
            divs.push_back(p);
            divs.push_back(v / p);
          }
        }
      }
    }
  }
  sort(divs.begin(), divs.end());
  divs.resize(unique(divs.begin(), divs.end()) - divs.begin());

  vector<int> good;
  int A = 0;
  int64_t B = 0;
  for (int u = 1; u <= 50; ++u) {
    if (binary_search(divs.begin(), divs.end(), u)) {
      continue;
    }
    vector<int> used(u);
    for (int i = 0; i < N; ++i) {
      int r = x[i] % u;
      if (r < 0) r += u;
      used[r] = 1;
    }
    if (count(used.begin(), used.end(), 0) == 0) {
      good.push_back(u);
    }
  }
  for (int u : divs) {
    A++;
    B += u;
  }
  for (int i = 0; i < good.size(); ++i) {
    bool fail = false;
    for (int j = 0; j < i; ++j) {
      if (good[i] % good[j] == 0) {
        fail = true;
      }
    }
    if (fail) {
      A++;
      B += good[i];
    }
  }
  cout << A << " " << B << "\n";
}

