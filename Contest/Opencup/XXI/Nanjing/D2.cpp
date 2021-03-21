#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  set<pair<int, int>> st;
  vector<pair<int, int>> edg;

  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    if (u == v) continue;
    if (st.count(minmax(u, v))) continue;
    st.insert(minmax(u, v));
    edg.emplace_back(u, v);
  }

  if (n == 3) { cout << "No" << '\n'; return; }

  m = edg.size();

  vector<int> djs(n);
  function<int(int)> Find = [&] (int x) { return x == djs[x] ? x : djs[x] = Find(djs[x]); };
  auto Union = [&] (int x, int y) { djs[Find(x)] = Find(y); };

  iota(djs.begin(), djs.end(), 0);

  vector<bool> on_tree(m, false);
  vector<int> deg(n, 0);
  for (int i = 0; i < m; ++i) {
    auto [u, v] = edg[i];
    if (Find(u) == Find(v)) continue;
    Union(u, v);
    on_tree[i] = true;
    ++deg[u], ++deg[v];
  }


  int root = -1;
  for (int i = 0; i < n; ++i) {
    if (deg[i] > n / 2) root = i;
  }


  auto checkTree = [&] (vector<pair<int, int>> tree) {
    fill(deg.begin(), deg.end(), 0);
    iota(djs.begin(), djs.end(), 0);
    for (auto [u, v] : tree) {
      ++deg[u];
      ++deg[v];
      assert(Find(u) != Find(v));
      Union(u, v);
    }
    for (int i = 0; i < n; ++i) assert(deg[i] <= n / 2);
    assert(tree.size() == n - 1);
  };

  if (root == -1) {
    cout << "Yes" << '\n';
    vector<pair<int, int>> tree;
    for (int i = 0; i < m; ++i) if (on_tree[i]) {
      tree.emplace_back(edg[i]);
      cout << edg[i].first + 1 << ' ' << edg[i].second + 1 << '\n';
    }
    checkTree(tree);

    return;
  }


  iota(djs.begin(), djs.end(), 0);

  for (int i = 0; i < m; ++i) {
    auto [u, v] = edg[i];
    if (u == root || v == root) continue;
    Union(u, v);
  }

  vector<vector<int>> con_to(n);
  for (int i = 0; i < m; ++i) {
    if (!on_tree[i]) continue;
    auto [u, v] = edg[i];
    if (u != root && v != root) continue;
    if (u == root) con_to[Find(v)].push_back(i);
    if (v == root) con_to[Find(u)].push_back(i);
  }

  int root_ch = 0;
  for (int i = 0; i < n; ++i) if (con_to[i].size()) ++root_ch;

  // for (int i = 0; i < n; ++i) {
  //   cerr << "con to " << i << ": ";
  //   for (int j : con_to[i]) cerr << j << ' ';
  //   cerr << endl;
  // }

  // cerr << "root_ch = " << root_ch << endl;

  if (root_ch > n / 2) { cout << "No" << '\n'; return; }

  int plug = deg[root] - n / 2;

  for (int i = 0; i < n; ++i) if (con_to[i].size() > 1u) {
    while (con_to[i].size() > 1u) {
      if (!plug) break;
      int ei = con_to[i].back();
      con_to[i].pop_back();
      on_tree[ei] = 0;
      --plug;
    }
  }

  iota(djs.begin(), djs.end(), 0);
  for (int i = 0; i < m; ++i) if (on_tree[i]) {
    auto [u, v] = edg[i];
    Union(u, v);
  }

  for (int i = 0; i < m; ++i) {
    if (on_tree[i]) continue;
    auto [u, v] = edg[i];
    if (u == root || v == root) continue;
    if (Find(u) == Find(v)) continue;
    Union(u, v);
    on_tree[i] = 1;
  }

  fill(deg.begin(), deg.end(), 0);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) if (on_tree[i]) {
    auto [u, v] = edg[i];
    ++deg[u];
    ++deg[v];
    g[u].push_back(v);
    g[v].push_back(u);
  }


  for (int i = 0; i < n; ++i) if (deg[i] > n / 2) {
    int root2 = i;

    set<int> to_root, to_root2;
    for (int i = 0; i < m; ++i) {
      auto [u, v] = edg[i];
      if (!on_tree[i]) {
      if (u == root) to_root.insert(v);
      if (v == root) to_root.insert(u);
      } else {
      if (u == root2) to_root2.insert(v);
      if (v == root2) to_root2.insert(u);
      }
    }

    to_root.erase(root2);
    to_root2.erase(root);

    for (int ano : to_root2) {
      if (to_root.count(ano)) {
        for (int i = 0; i < m; ++i) {
          auto [u, v] = edg[i];
          if (minmax(u, v) == minmax(root, root2)) {
            if (!on_tree[i]) continue;
            on_tree[i] = 0;
          }
          if (minmax(u, v) == minmax(root, ano)) {
            if (on_tree[i]) continue;
            on_tree[i] = 1;
          }
        }
        break;
      }
    }

    break;
  }

  cout << "Yes" << '\n';
  vector<pair<int, int>> tree;
  for (int i = 0; i < m; ++i) if (on_tree[i]) {
    tree.emplace_back(edg[i]);
    cout << edg[i].first + 1 << ' ' << edg[i].second + 1 << '\n';
  }
  checkTree(tree);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) {
    solve();
  }
}
