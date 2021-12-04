#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Node {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> ys;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> zs;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<array<int, 3>> vec(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < 3; ++j) {
      cin >> vec[i][j];
      vec[i][j] = N - vec[i][j];
    }
  }
  vector<Node> xtree(N + 1);
  vector<Node> ytree(N + 1);


  auto Insert = [&](vector<Node>& tree, int x, int y, int z, int p) {
    for (int i = x + 1; i <= N; i += i & -i) {
      tree[i].ys.emplace(y, p);
      tree[i].zs.emplace(z, p);
    }
  };


  auto Query = [&](vector<Node>& tree, int x, int y, int z, function<void(int)>&& work) {
    for (int i = x; i > 0; i -= i & -i) {
      while (!tree[i].ys.empty()) {
        if (tree[i].ys.top().first >= y) {
          break;
        }
        auto p = tree[i].ys.top();
        tree[i].ys.pop();
        work(p.second);
      }
      while (!tree[i].zs.empty()) {
        if (tree[i].zs.top().first >= z) {
          break;
        }
        auto p = tree[i].zs.top();
        tree[i].zs.pop();
        work(p.second);
      }
    }
  };

  for (int i = 0; i < N; ++i) {
    Insert(xtree, vec[i][0], vec[i][1], vec[i][2], i);
    Insert(ytree, vec[i][1], vec[i][0], vec[i][2], i);
  }
  vector<bool> vis(N);
  vector<int> topo;

  auto Dfs = [&](auto dfs, int x) -> void {
    vis[x] = true;
    Query(xtree, vec[x][0], vec[x][1], vec[x][2], [&](int y) { 
      if (!vis[y]) {
        dfs(dfs, y);
      }
    });
    Query(ytree, vec[x][1], vec[x][0], vec[x][2], [&](int y) {
      if (!vis[y]) {
        dfs(dfs, y);
      }
    });
    topo.push_back(x);
  };

  for (int i = 0; i < N; ++i) {
    if (vis[i]) continue;
    Dfs(Dfs, i);
  }

  reverse(topo.begin(), topo.end());

  for (int i = 0; i <= N; ++i) {
    while (!xtree[i].ys.empty()) xtree[i].ys.pop();
    while (!xtree[i].zs.empty()) xtree[i].zs.pop();
    while (!ytree[i].ys.empty()) ytree[i].ys.pop();
    while (!ytree[i].zs.empty()) ytree[i].zs.pop();
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < 3; ++j) {
      vec[i][j] = N - vec[i][j] - 1;
    }
    Insert(xtree, vec[i][0], vec[i][1], vec[i][2], i);
    Insert(ytree, vec[i][1], vec[i][0], vec[i][2], i);
  }
  vector<int> scc(N, -1);

  auto RevDfs = [&](auto dfs, int x, int p) -> void {
    scc[x] = p;
    Query(xtree, vec[x][0], vec[x][1], vec[x][2], [&](int y) { 
      if (scc[y] == -1) {
        dfs(dfs, y, p);
      }; 
    });
    Query(ytree, vec[x][1], vec[x][0], vec[x][2], [&](int y) {
      if (scc[y] == -1) {
        dfs(dfs, y, p);
      }     
    });
  };

  int p = 0;
  for (int u : topo) {
    if (scc[u] == -1) {
      RevDfs(RevDfs, u, p++);
    }
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    if (scc[x] <= scc[y]) cout << "YES\n";
    else cout << "NO\n";
  }
  return 0;
}

