#include <bits/stdc++.h>
using namespace std;

using Vector = bitset<1000>;

int main() {
  ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<Vector> v(n);
  Vector v0;
  for (int i = 0; i <= n; ++i) {
    int a;
    cin >> a;
    for (int j = 0; j < n; ++j) {
      if (a >> j & 1) {
        if (i == 0) v0.set(j);
        else v[i - 1].set(j);
      }
    }
  }
  vector<Vector> adj(n);
  vector<Vector> w = v;
  for (int i = 0; i < n; ++i) {
    adj[i].set(i);
  }
  for (int i = 0; i < n; ++i) {
    int p = -1;
    for (int j = i; j < n; ++j) {
      if (v[j][i]) {
        p = j;
        break;
      }
    }
    assert(p != -1);
    swap(v[i], v[p]);
    swap(adj[i], adj[p]);
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      if (v[j][i]) {
        v[j] ^= v[i];
        adj[j] ^= adj[i];
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    assert(v[i].count() == 1 && v[i][i]);
  }
  vector<Vector> inv = adj;

  auto Solve = [&](const vector<Vector> &inv, const Vector &v) {
    cout << "v = ";
    for (int i = 0; i < n; ++i) cout << v[i];
    cout << endl;
    cout << "inv = \n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << inv[i][j];
      }
      cout << endl;
    }
    vector<int> res = {0};
    for (int i = 0; i < n; ++i) {
      if ((inv[i] & v).count() & 1) res.push_back(i + 1);
    }
    cout << res.size() << "\n";
    int enc = res.size();
    for (int u : res) {
      cout << u << " ";
      enc ^= u;
    }
    cout << "\n";
    return enc;
  };

  int enc = Solve(inv, v0);
  while (m--) {
    int t, x;
    cin >> t >> x;
    // t ^= enc;
    Vector v, u;
    v.set(t);
    for (int i = 0; i < n; ++i) {
      if (w[t][i] != (x >> i & 1)) u.set(i);
      w[t][i] = (x >> i & 1);
    }
    for (int i = 0; i < n; ++i) {
      u[i] = (inv[i] & u).count() & 1;
    }
    for (int i = 0; i < n; ++i) {
      v[i] = inv[i][t];
    }
    for (int i = 0; i < n; ++i) {
      if (u[i]) {
        adj[i] ^= v;
      }
    }
  }
  return 0;
}
