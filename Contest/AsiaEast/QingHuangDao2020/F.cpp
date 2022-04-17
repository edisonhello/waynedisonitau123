#include <bits/stdc++.h>
using namespace std;

int solve() {
  int n, m;
  cin >> n >> m;

  vector<int> djs(n + 3);
  iota(djs.begin(), djs.end(), 0);

  function<int(int)> F = [&](int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); };
  auto U = [&](int x, int y) { djs[F(x)] = F(y); };

  vector<pair<int, int>> g;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    g.emplace_back(u, v);
    U(u, v);
  }

  vector<int> V(n + 4), E(n + 4);
  for (int i = 1; i <= n; ++i) {
    V[F(i)]++;
  }
  for (auto [u, v] : g) {
    E[F(u)]++;
  }

  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += max(E[i] - V[i], 0);
  }

  return sum;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t; cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": " << solve() << '\n';
    
  }
}

