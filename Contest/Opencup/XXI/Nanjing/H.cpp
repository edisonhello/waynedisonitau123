#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw3[4000006];

map<pair<int, int>, int> mp;
int solve() {
  int n, m; cin >> n >> m;
  if (n == 1 || m == 1) {
    return 0;
  }

  if (n > 8 || m > 8) {
    return pw3[n * m];
  }

  if (n > m) swap(n, m);
  auto it = mp.find(make_pair(n, m));
  if (it != mp.end()) return it->second;

  vector<int> rec(n * m, 0);

  int cnt = 0;
  auto Dfs = [&] (auto dfs, int now) -> void {
    if (now == n * m) {
      ++cnt;
      return;
    }
    int x = now / m;
    int y = now - x * m;
    for (int z = 1; z <= 3; ++z) {
      bool no = 0;
      for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
          if (rec[i * m + j] * z - rec[i * m + y] * rec[x * m + j] == 0) {
            no = 1;
            break;
          }
        }
        if (no) break;
      }
      if (no) continue;
      rec[now] = z;
      dfs(dfs, now + 1);
    }
  };

  rec[0] = 1;
  Dfs(Dfs, 1);

  return mp[make_pair(n, m)] = (pw3[n * m] - cnt * 3ll % mod + mod) % mod;
}

int main() {
  pw3[0] = 1;
  for (int i = 1; i < 4000004; ++i) {
    pw3[i] = pw3[i - 1] * 3ll % mod;
  }
  int t; cin >> t; while (t--) {
    cout << solve() << '\n';
  }
}
