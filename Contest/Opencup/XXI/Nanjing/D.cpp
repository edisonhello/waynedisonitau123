#include <bits/stdc++.h>
using namespace std;

void Solve() {
  int N, M;
  cin >> N >> M;
  vector<pair<int, int>> edges(M);
  vector<vector<int>> g(N);
  for (int i = 0; i < M; ++i) {
    cin >> edges[i].first >> edges[i].second;
    edges[i].first--;
    edges[i].second--;
    g[edges[i].first].push_back(edges[i].second);
    g[edges[i].second].push_back(edges[i].first);
  }
  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  vector<vector<pair<int, int>>> tree(N);
  vector<bool> on_tree(M);

  auto Print = [&]() {
    vector<int> ndeg(N);
    iota(uf.begin(), uf.end(), 0);
    cout << "Yes\n";
    for (int i = 0; i < M; ++i) {
      if (!on_tree[i]) continue;
      auto [u, v] = edges[i];
      assert(u != v);
      assert(Find(u) != Find(v));
      ndeg[u]++;
      ndeg[v]++;
      uf[Find(u)] = Find(v);
      // cout << u + 1 << " " << v + 1 << "\n";
    }
    for (int i = 0; i < N; ++i) {
      assert(ndeg[i] * 2 <= N);
    }
  };

  for (int i = 0; i < M; ++i) {
    auto [u, v] = edges[i];
    if (u == v) continue;
    if (Find(u) != Find(v)) {
      on_tree[i] = true;
      int fu = Find(u);
      int fv = Find(v);
      uf[fu] = fv;
      tree[u].emplace_back(v, i);
      tree[v].emplace_back(u, i);
    }
  }
  int root = -1;
  for (int i = 0; i < N; ++i) {
    if (tree[i].size() * 2 > N) root = i;
  }
  cerr << "root = " << root << endl;
  cerr << "tree: ";
  for (int i = 0; i < M; ++i) cerr << on_tree[i];
  cerr << endl;
  if (root == -1) {
    Print();
    return;
  }

  iota(uf.begin(), uf.end(), 0);
  for (int i = 0; i < M; ++i) {
    auto [u, v] = edges[i];
    if (u == v) continue;
    if (u == root || v == root) continue;
    int fu = Find(u), fv = Find(v);
    uf[fu] = fv;
  }

  vector<int> belong(N);
  for (int i = 0; i < N; ++i) belong[i] = Find(i);
  iota(uf.begin(), uf.end(), 0);

  for (int i = 0; i < M; ++i) {
    if (!on_tree[i]) continue;
    auto [u, v] = edges[i];
    if (u == v) continue;
    if (u == root || v == root) continue;
    uf[Find(u)] = Find(v);
  }

  vector<vector<int>> sw(N);
  for (int i = 0; i < M; ++i) {
    if (on_tree[i]) continue;
    auto [u, v] = edges[i];
    if (u == v) continue;
    if (u == root || v == root) continue;
    int fu = Find(u), fv = Find(v);
    if (fu != fv) {
      uf[fu] = fv;
      assert(belong[u] == belong[v]);
      cerr << "haha i = " << i << endl;
      sw[belong[u]].push_back(i);
    }
  }

  sort(tree[root].begin(), tree[root].end(), [&](auto u, auto v) { return belong[u.first] < belong[v.first]; });
  int quota = 0;
  int s = tree[root].size();
  vector<int> deg(N);
  for (int i = 0; i < N; ++i) deg[i] = tree[i].size();
  for (int i = 0, j = 0; i < tree[root].size(); i = j) {
    while (j < tree[root].size() && belong[tree[root][j].first] == belong[tree[root][i].first]) j++;
    if (j - i > 1) {
      int cnt = j - i;
      int w = belong[tree[root][i].first];
      for (int k = i; k < j; ++k) {
        if (cnt == 1) continue;
        while (!sw[w].empty()) {
          auto [u, v] = edges[sw[w].back()];
          ++deg[u];
          ++deg[v];
          --deg[root];
          --deg[tree[root][k].first];
          bool ok = (deg[u] * 2 <= N && deg[v] * 2 <= N);
          if (ok) {
            on_tree[tree[root][k].second] = false;
            on_tree[sw[w].back()] = true;
            sw[w].pop_back();
            cnt--;
            break;
          } else {
            --deg[u];
            --deg[v];
            ++deg[root];
            ++deg[tree[root][k].first];
          }
          sw[w].pop_back();
        }
      }
    }
  }
  if (all_of(deg.begin(), deg.end(), [&](int x) { return x * 2 <= N; })) {
    Print();
    return;
  }
  if (N % 2 == 0) {
    cout << "No\n";
    return;
  }
  cerr << "root = " << root << endl;
  cerr << "tree: ";
  for (int i = 0; i < M; ++i) cerr << on_tree[i];
  cerr << endl;
  for (int i = 0; i < N; ++i) tree[i].clear();
  for (int i = 0; i < M; ++i) {
    if (!on_tree[i]) continue;
    auto [u, v] = edges[i];
    if (u == v) continue;
    tree[u].emplace_back(v, i);
    tree[v].emplace_back(u, i);
  }
  int T = (N + 1) / 2;
  assert(tree[root].size() >= T);
  if (tree[root].size() != T) {
    cout << "No\n";
    return;
  }
  int D = -1, f = -1;
  for (auto [u, e] : tree[root]) {
    if (D == -1 || deg[u] > deg[D]) {
      D = u;
      f = e;
    }
  }
  if (deg[D] != T - 1) {
    cout << "No\n";
    return;
  }
  vector<int> pile(N, -1);
  for (auto [u, e] : tree[root]) {
    if (u != D) pile[u] = 0;
  }
  for (auto [u, e] : tree[D]) {
    if (u != root) pile[u] = 1;
  }
  for (int i = 0; i < M; ++i) {
    if (on_tree[i]) continue;
    auto [u, v] = edges[i];
    if (u == v) continue;
    if (u == root || v == root) continue;
    if (u == D || v == D) {
      int w = (u == D ? v : u);
      if (pile[w] == 0 && (deg[w] + 1) * 2 <= N) {
        on_tree[i] = true;
        on_tree[f] = false;
        Print();
        return;
      }
      continue;
    }
    if (pile[u] == 1 && pile[v] == 1) continue;
    assert(!(pile[u] == 0 && pile[v] == 0));
    if (pile[u] != pile[v]) {
      on_tree[i] = true;
      on_tree[f] = false;
      Print();
      return;
    }
  }
  cout << "No\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) Solve();
}
