#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<vector<int>> g(N);
  vector<int> color(N);
  for (int i = 0; i < N; ++i) cin >> color[i]; 
  for (int i = 0; i < N - 1; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<int> deg(N);
  vector<int> que;
  vector<bool> vis(N);
  vector<int> child(N), black(N), fa(N, -1);

  for (int i = 0; i < N; ++i) {
    deg[i] = g[i].size();
    if (deg[i] == 1) {
      fa[i] = g[i][0];
      child[fa[i]]++;
      if (color[i] == 0) black[fa[i]]++;
    }
  }

  vector<vector<int>> after(N);
  vector<int> ord;
  for (int it = 0; it < que.size(); ++it) {
    int x = que[it];
    cout << "x = " << x + 1 << "\n";
    vis[x] = true;
    ord.push_back(x);
    for (int u : g[x]) {
      if (vis[u]) continue;
      color[u] ^= 1;
      --child[u];
      if (child[u] == black[u]) {
        for (int v : g[u]) {
          if (fa[v] == u) {
            if (vis[v]) continue;
            assert(color[v] == 0);
            after[u].push_back(v);
            vis[v] = true;
          }
        }
        for (int v : g[u]) {
          if (vis[v]) continue;
          assert(fa[u] == -1);
          fa[u] = v;
        }
        if (fa[u] != -1) {
          child[fa[u]]++;
          if (color[u] == 0) black[fa[u]]++;
        }
        if (color[u] == 1) que.push_back(u);
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    if (vis[i]) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
  for (int u : ord) {
    cout << u + 1 << " ";
    for (int v : after[u]) cout << v + 1 << " ";
  }
  cout << "\n";
}
