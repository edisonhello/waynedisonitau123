#include <bits/stdc++.h>
using namespace std;

vector<int> do1(vector<int> v) {
  for (int i = 1; i < v.size(); i += 2) {
    swap(v[i - 1], v[i]);
  }
  return v;
}

vector<int> do2(vector<int> v) {
  for (int i = 0; i < v.size() / 2; ++i) {
    swap(v[i], v[i + v.size() / 2]);
  }
  return v;
}

bool is_sorted(vector<int> v) {
  for (int i = 0; i < v.size(); ++i) if (i + 1 != v[i]) return 0;
  return 1;
}

int main() {
  int n; cin >> n;
  n *= 2;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];

  if (is_sorted(v)) {
    cout << 0 << endl;
    exit(0);
  }

  int mn = INT_MAX;

  auto o = v;

  {
    int cnt = 0;
    while (true) {
      v = do1(v);
      ++cnt;
      if (is_sorted(v)) break;
      if (v == o) break;
      v = do2(v);
      ++cnt;
      if (is_sorted(v)) break;
      if (v == o) break;
    }

    if (is_sorted(v)) mn = min(mn, cnt);
  } 
  v = o;
  {
    int cnt = 0;
    while (true) {
      v = do2(v);
      ++cnt;
      if (is_sorted(v)) break;
      if (v == o) break;
      v = do1(v);
      ++cnt;
      if (is_sorted(v)) break;
      if (v == o) break;
    }

    if (is_sorted(v)) mn = min(mn, cnt);
  }

  if (mn == INT_MAX) cout << -1 << '\n';
  else cout << mn << endl;
}
