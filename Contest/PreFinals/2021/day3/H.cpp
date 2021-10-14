#include <bits/stdc++.h>
using namespace std;


vector<pair<int, int>> solve(int n) {
  vector<pair<int, int>> ans;
  if (n == 4) {
    ans.emplace_back(1, 2);
    ans.emplace_back(5, 7);
    ans.emplace_back(3, 6);
    ans.emplace_back(4, 8);
  } else if (n % 4 == 0) {
    int nn = n * 2;
    for (int i = n, j = 2 * n; i != j; ++i, --j) ans.emplace_back(i, j);
    ans.emplace_back(n / 2 * 3, n / 2 + 1);

    ans.emplace_back(n - 1, n / 2);
    int l = 1, r = n - 2;
    for (int i = 0; i < n / 4 - 1; ++i) {
      ans.emplace_back(l, r);
      ++l, --r;
    }
    ans.emplace_back(l, l + 1);
    l += 2;
    while (l < r) {
      ans.emplace_back(l, r);
      ++l, --r;
    }
    ans.pop_back();
  } else if (n % 4 == 1) {
    // TODO
  } else {
    return vector<pair<int, int>>();
  }

  for (auto &p : ans) if (p.first > p.second) swap(p.first, p.second);

  sort(ans.begin(), ans.end(), [&] (const pair<int, int> &a, const pair<int, int> &b) {
    return a.second - a.first < b.second - b.first;
  });

  return ans;
}

bool check(int n, vector<pair<int, int>> ans) {
  vector<bool> used(n * 2 + 1, false);
  auto insert = [&] (int v) {
    if (v < 1 || v > 2 * n) return false;
    if (used[v]) return false;
    used[v] = 1;
    return true;
  };

  for (int i = 1; i <= n; ++i) {
    auto &p = ans[i - 1];
    if (!insert(p.first)) return false;
    if (!insert(p.second)) return false;
    if (p.second - p.first != i) return false;
  }

  return true;
}

int main() {
  for (int i = 4; i <= 1000000; i += 4) {
    check(i, solve(i));
    cerr << "fin " << i << endl;
  }
  // int n; cin >> n;

  // auto ans = solve(n);

  // check(n, ans);

  // for (auto &p : ans) {
  //   cout << p.first << ' ' << p.second << endl;
  // }
}
