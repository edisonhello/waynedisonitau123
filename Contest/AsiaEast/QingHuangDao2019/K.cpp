#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<vector<int>> g(N);
    vector<int> fa(N, -1), deg(N);
    vector<bool> leaf(N, true);
    for (int i = 1; i < N; ++i) {
      cin >> fa[i];
      fa[i]--;
      deg[i]++;
      deg[fa[i]]++;
      leaf[fa[i]] = false;
    }
    vector<pair<int, int>> que;
    for (int i = 0; i < N; ++i) if (leaf[i]) que.emplace_back(i, 1);
    bool ok = false;
    for (int it = 0; it < que.size(); ++it) {
      auto [x, y] = que[it];
      if (fa[x] >= 0 && deg[fa[x]] + (fa[x] == 0) == 2) {
        que.emplace_back(fa[x], y + 1);
      } else {
        ok |= y % 2 == 1;
      }
    }

    if (!ok) cout << "Meiya\n";
    else cout << "Takeru\n";
  }
}
