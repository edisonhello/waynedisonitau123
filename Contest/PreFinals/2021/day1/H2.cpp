#include <bits/stdc++.h>
using namespace std;

int c[200005];
set<int> g[200005];
vector<int> plugg[200005];
vector<int> ans;

void plug(int now) {
  ans.push_back(now);
  for (int i : plugg[now]) plug(i);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int n; cin >> n;

  for (int i = 1; i <= n; ++i) cin >> c[i];

  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    g[u].insert(v);
    g[v].insert(u);
  }

  if (n == 1) {
    if (c[1] == 1) {
      cout << "YES" << endl;
      cout << 1 << endl;
      exit(0);
    } else {
      cout << "NO" << endl;
    }
  }

  vector<int> cbcl(n + 2, 0);

  vector<int> leaf;
  for (int i = 1; i <= n; ++i) if (g[i].size() == 1u) leaf.push_back(i);

  while (leaf.size()) {
    int now = leaf.back(); leaf.pop_back();
    int pa = *g[now].begin();

    // cerr << "now = " << now << endl;

    if (c[now]) {
      plug(now);
      c[pa] ^= 1;
    } else {
      plugg[pa].push_back(now);
    }
    g[pa].erase(now);

    if (g[pa].size() == 1u) {
      leaf.push_back(pa);
    }
  }


  if ((int)ans.size() == n) {
    cout << "YES" << endl;
    for (int i : ans) cout << i << ' ';
    cout << endl;
  } else {
    cout << "NO" << endl;
  }


}
