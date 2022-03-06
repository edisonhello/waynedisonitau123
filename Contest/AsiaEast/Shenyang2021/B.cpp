#include <bits/stdc++.h>
using namespace std;

int djs[200005];
int cnt[200005];
int vis[200005];

int F(int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); }
void U(int x, int y) { djs[F(x)] = F(y); }

void NO() {
  cout << -1 << endl;
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<tuple<int, int, int>> cons;
  cons.reserve(m);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    cons.emplace_back(u, v, w);
  }

  int64_t ans = 0;
  for (int z = 0; z < 30; ++z) {
    for (int i = 1; i <= 2 * n; ++i) djs[i] = i;
    for (auto &[u, v, w] : cons) {
      int x = !!(w & (1 << z));
      // cout << "u v w x z " << u << ' ' << v << ' ' << w << ' ' << x << ' ' << z << endl;
      if (x) {
        if (F(u) == F(v)) NO();
        U(u, v + n);
        U(u + n, v);
      } else {
        if (F(u) == F(v + n)) NO();
        U(u, v);
        U(u + n, v + n);
      }
    }

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i) {
      ++cnt[F(i)];
    }

    int tot = 0;
    for (int i = 1; i <= n; ++i) {
      int a = F(i);
      int b = F(i + n);
      if (vis[a] == z + 1 || vis[b] == z + 1) continue;
      vis[a] = vis[b] = z + 1;
      tot += min(cnt[a], cnt[b]);
    }

    ans += (1ll << z) * tot;
    // cout << "z tot " << z << ' ' << tot << endl;
  }

  cout << ans << endl;

}

