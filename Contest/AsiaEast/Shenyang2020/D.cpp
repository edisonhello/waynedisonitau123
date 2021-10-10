#include <bits/stdc++.h>
using namespace std;

void solve(int n) {
  vector<int> best;
  int bc = -1;

  for (int z = 0; z < (1 << n); ++z) {
    int c = 0;
    for (int i = 0; i < n; ++i) {
      int cc = 0;
      for (int j = i; j < n; ++j) {
        cc += !!(z & (1 << j));
        if (cc & 1) ++c;
      }
    }
    if (c == bc) {
      best.push_back(z);
    } else if (c > bc) {
      best.clear();
      best.push_back(z);
      bc = c;
    }
  }

  sort(best.begin(), best.end());
  if (best.size() > 100u) best.resize(100);

  cout << bc << endl;
  for (int i : best) {
    for (int y = n - 1; y >= 0; --y) cout << (!!(i & (1 << y)) ? "r" : "b");
    cout << endl;
  }
}

int main() {
  int n; cin >> n;
  solve(n);
}
