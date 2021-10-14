#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  vector<vector<int>> g(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<vector<int>> fa(N, vector<int>(20));
  vector<int> depth(N);
  vector<int> down(N), up(N);

  constexpr int kP = 1'000'000'000 + 7;

  auto DfsUp = [&](auto dfs, int x, int p = -1) -> void {
    fa[x][0] = p;
    for (int d = 1; (1 << d) <= depth[x]; ++d) {
      fa[x][d] = fa[fa[x][d - 1]][d - 1];
    }
    up[x] = 1;
    for (int u : g[x]) {
      if (u == p) continue;
      depth[u] = depth[x] + 1;
      dfs(dfs, u, x);
      up[x] += up[u] + 1;
      up[x] %= kP;
    }
  };

  auto DfsDown = [&](auto dfs, int x, int p = -1) -> void {
    int s = down[x];
    for (int u : g[x]) {
      if (u == p) continue;
      (s += up[u]) %= kP;
    }
    for (int u : g[x]) {
      if (u == p) continue;
      down[u] = (g[x].size() + s + kP - up[u]) % kP;
      dfs(dfs, u, x);
    }
  };

  DfsUp(DfsUp, 0);
  DfsDown(DfsDown, 0);

  vector<int> ups(N), downs(N);

  auto DfsSum = [&](auto dfs, int x, int p = -1) -> void {
    (ups[x] += up[x]) %= kP;
    (downs[x] += down[x]) %= kP;
    for (int u : g[x]) {
      if (u == p) continue;
      ups[u] = ups[x];
      downs[u] = downs[x];
      dfs(dfs, u, x);
    }
  };

  DfsSum(DfsSum, 0);

  auto GetLCA = [&](int x, int y) {
    if (depth[x] > depth[y]) swap(x, y);
    for (int d = 0; d < 20; ++d) {
      if ((depth[y] - depth[x]) >> d & 1) y = fa[y][d];
    }
    if (x == y) return x;
    for (int d = 19; d >= 0; --d) {
      if (fa[x][d] != fa[y][d]) {
        x = fa[x][d];
        y = fa[y][d];
      }
    }
    return fa[x][0];
  };

  for (int i = 0; i < Q; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    int z = GetLCA(x, y);
    int ans = (ups[x] + kP - ups[z]) % kP + (downs[y] + kP - downs[z]) % kP;
    cout << ans % kP << "\n";
  }
}

