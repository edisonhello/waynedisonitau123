#include <bits/stdc++.h>
using namespace std;

int gid(int x, int y) {
  return x * 360 + y;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t; cin >> t; while (t--) {
    int n; cin >> n;

    vector<vector<int>> cw(25, vector<int>(360, 0));
    vector<vector<int>> sw(25, vector<int>(360, 0));

    while (n--) {
      string type;
      cin >> type;
      if (type == "C") {
        int r, o1, o2;
        cin >> r >> o1 >> o2;
        for (int o = o1; o != o2; o = (o + 1) % 360) cw[r][o] = 1;
      } else {
        int r1, r2, o;
        cin >> r1 >> r2 >> o;
        for (int r = r1; r < r2; ++r) sw[r][o] = 1;
      }
    }

    queue<int> q;
    vector<int> vis(25 * 360, 0);
    for (int i = 0; i < 360; ++i) {
      vis[i] = 1;
      q.push(i);
    }

    vector<vector<int>> g(25 * 360);
    auto add_edge = [&](int u, int v) {
      g[u].push_back(v);
      g[v].push_back(u);
    };

    for (int r = 1; r <= 21; ++r) {
      for (int i = 0; i < 360; ++i) {
        if (!cw[r][i]) add_edge(gid(r - 1, i), gid(r, i));
        if (!sw[r][i]) add_edge(gid(r, (i - 1 + 360) % 360), gid(r, i));
      }
    }

    int yes = 0;

    while (q.size()) {
      int now = q.front();
      q.pop();
      if (now >= gid(21, 0)) yes = 1;
      for (int i : g[now]) {
        if (!vis[i]) {
          vis[i] = 1;
          q.push(i);
        }
      }
    }

    cout << (yes ? "YES" : "NO") << '\n';
  }
}

