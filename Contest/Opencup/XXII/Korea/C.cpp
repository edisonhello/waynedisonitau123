#include <bits/stdc++.h>
using namespace std;

set<int> stg[500005];

int main() {
  int d, n;
  cin >> d >> n;

  vector<pair<vector<int>, int>> trees;
  for (int i = 0; i < d; ++i) {
    vector<tuple<int, int, int>> edg;

    for (int i = 1; i < n; ++i) {
      int u, v , w;
      cin >> u >> v >> w;
      edg.emplace_back(w, u, v);
    }

    sort(edg.begin(), edg.end());
    reverse(edg.begin(), edg.end());

    vector<int> djs(n + 3);
    iota(djs.begin(), djs.end(), 0);

    function<int(int)> F = [&](int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); };
    auto U = [&](int x, int y) {
      x = F(x);
      y = F(y);
      if (x < y) swap(x, y);
      djs[x] = y;
    };

    vector<int> tree;
    for (int i = 0, j; i < n - 1; i = j) {
      vector<pair<int, int>> edg2;
      int noww = get<0>(edg[i]);

      for (j = i; j < n - 1; ++j) {
        if (get<0>(edg[j]) != get<0>(edg[i])) break;
        edg2.emplace_back(F(get<1>(edg[j])), F(get<2>(edg[j])));
      }

      set<int> vset;
      for (auto [u, v] : edg2) {
        vset.insert(u);
        vset.insert(v);
        stg[u].insert(v);
        stg[v].insert(u);
      }

      set<int> vvis;
      vector<int> vcur;

      auto dfs = [&](auto dfs, int now) -> void {
        vvis.insert(now);
        vcur.push_back(now);

        for (int i : stg[now]) {
          if (!vvis.count(i)) {
            dfs(dfs, i);
          }
        }
      };

      for (int i : vset) {
        if (vvis.count(i)) continue;
        dfs(dfs, i);
        sort(vcur.begin(), vcur.end());
        tree.push_back(noww);
        // cerr << "noww = " << noww << endl;
        tree.push_back(vcur.size());
        // cerr << "size = " << vcur.size() << endl;
        // cerr << "i = ";
        for (int i : vcur) {
          tree.push_back(i);
          // cerr << i << ' ';
        }
        // cerr << endl;
        vcur.clear();
      }

      for (auto [u, v] : edg2) {
        U(u, v);
      }

      for (int i : vset) stg[i].clear();
    }

    // cerr << "Tree " << i << endl;
    // for (int i : tree) cerr << i << ' ';
    // cerr << endl;
    trees.emplace_back(tree, i);
  }

  sort(trees.begin(), trees.end());

  vector<int> ans(d + 4);
  for (int i = 0, j; i < d; i = j) {
    for (j = i; j < d; ++j) {
      if (trees[i].first == trees[j].first) {
        ans[trees[j].second] = trees[i].second;
      }
      else break;
    }
  }

  for (int i = 0; i < d; ++i) {
    cout << ans[i] + 1 << ' ';
  }
  cout << endl;
}

