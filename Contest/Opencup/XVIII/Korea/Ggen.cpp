#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());

  int n = 100000, m = 300000;
  cout << n << ' ' << m << endl;

  set<pair<int, int>> st;
  for (int i = 1; i < n; ++i) {
    int u = rand() % i + 1;
    int v = i + 1;
    cout << u << ' ' << v << ' ' << rand() % 1000000000 + 1 << '\n';
    m--;

    st.insert(minmax(u, v));
  }
  while (m--) {
    int u, v; do {
      u = rand() % n + 1, v = rand() % n + 1;
      if (u == v) continue;
      if (st.count(minmax(u, v))) continue;
      break;
    } while (1);
    if (u > v) swap(u, v);
    st.insert(minmax(u, v));
    cout << u << ' ' << v << ' ' << rand() % 1000000000 + 1 << '\n';
  }
}
