#include <bits/stdc++.h>
using namespace std;

void Solve() {
  int N;
  cin >> N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    A[i]--;
  }
  vector<int> pos(N);
  for (int i = 0; i < N; ++i) {
    cin >> B[i];
    B[i]--;
    pos[B[i]] = i;
  }
  vector<int> pref(N);
  vector<pair<int, int>> ans;
  for (int i = 0; i < N; ++i) {
    int p = find(A.begin(), A.end(), i) - A.begin();
    int q = pos[i];
    if (q > p) {
      cout << "-1\n";
      return;
    }
    pref[q] = A[q] > A[p] ? A[q] : 1'000'000'000;
    for (int j = q + 1; j <= p; ++j) {
      int v = A[j] > A[p] ? A[j] : 1'000'000'000;
      pref[j] = min(pref[j - 1], v);
    }
    while (p > q) {
      if (pref[p - 1] == 1'000'000'000) {
        cout << "-1\n";
        return;
      }
      int v = pref[p - 1];
      int o = p;
      while (p > q && A[p] != v) p--;
      ans.emplace_back(p, o);
      swap(A[o], A[p]);
    }
  }
  assert(A == B);
  cout << ans.size() << "\n";
  for (auto [i, j] : ans) {
    cout << i + 1 << " " << j + 1 << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    Solve();
  }
  return 0;
}

