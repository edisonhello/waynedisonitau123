#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> a(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
  }
  vector<vector<int>> g(N);
  for (int i = 0; i < N - 1; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  vector<int> A(N, N + 1);
  vector<int> B(N, -1);

  auto Dfs = [&](auto self, int x, int p = -1) -> void {
    A[x] = -1;
    B[x] = N + 1;
    for (int u : g[x]) {
      if (u == p) {
        continue;
      }
      self(self, u, x);
      int aa = N + 1;
      int bb = -1;
      if (a[u] > a[x]) {
        aa = min(aa, max(A[x], A[u]));
      }
      if (B[u] > a[x]) {
        aa = min(aa, max(A[x], a[u]));
      }
      if (a[u] < a[x]) {
        bb = max(bb, min(B[x], B[u]));
      }
      if (A[u] < a[x]) {
        bb = max(bb, min(B[x], a[u]));
      }
      A[x] = aa;
      B[x] = bb;
    }
  };

  Dfs(Dfs, 0);

  if (A[0] != N + 1 || B[0] != -1) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}
