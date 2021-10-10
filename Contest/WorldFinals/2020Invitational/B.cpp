#include <bits/stdc++.h>
using namespace std;

int djs[100005];

int F(int x) {
  return x == djs[x] ? x : djs[x] = F(djs[x]);
}

void U(int x, int y) {
  djs[F(x)] = F(y);
}


int main() {
  int n, m; cin >> n >> m;

  iota(dfs, dfs + 1 + n, 0);

  string ans;

  for (int i = 0; i < m; ++i) {
    int e, u, v; cin >> e >> u >> v;
    if (e == 1) {
      
    } else {
      ans += (F(u) == F(v) ? "1" : "0");
    }
  }

  cout << ans << endl;
}
