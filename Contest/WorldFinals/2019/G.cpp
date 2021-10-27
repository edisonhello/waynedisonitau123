#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  vector<char> c(N);
  vector<int> p(N);
  int root = -1;
  vector<vector<int>> g(N);
  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s >> p[i];
    c[i] = s[0];
    if (p[i]-- == 0) {
      root = i;
    } else {
      g[p[i]].push_back(i);
    }
  }

  vector<int> dep(N);
  vector<vector<int>> fa(N, vector<int>(20, -1));

  auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
    fa[x][0] = p;
    for (int i = 1; (1 << i) <= dep[x]; ++i) {
      fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int u : g[x]) {
      dep[u] = dep[x] + 1;
      dfs(dfs, u, x);
    }
  };

  Dfs(Dfs, root);
  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return c[i] < c[j];
  });
  vector<int> rnk(N);
  int r = 0;
  for (int i = 0; i < N; ++i) {
    if (i > 0 && c[order[i]] != c[order[i - 1]]) r++;
    rnk[order[i]] = r;
  }
  vector<int> ornk(N);
  vector<vector<int>> bucket(N);
  vector<vector<int>> inner(N);
  vector<int> used;
  for (int k = 1; ; ++k) {
    for (int i = 0; i < N; ++i) ornk[i] = rnk[i];

    auto Get = [&](int x) {
      return make_pair(ornk[x], fa[x][k - 1] == -1 ? -1 : ornk[fa[x][k - 1]]);
    };

    for (int i = 0; i < N; ++i) {
      bucket[ornk[i]].push_back(i);
    }
    for (int i = 0, j = 0; i < N; ++i) {
      if (!bucket[i].empty()) {
        sort(bucket[i].begin(), bucket[i].end(), [&](int x, int y) {
            int X = fa[x][k - 1] == -1 ? -1 : ornk[fa[x][k - 1]];
            int Y = fa[y][k - 1] == -1 ? -1 : ornk[fa[y][k - 1]];
            return X < Y;
        });
        for (int u : bucket[i]) order[j++] = u;
        bucket[i].clear();
      }
    }

    int r = 0;
    for (int i = 0; i < N; ++i) {
      if (i > 0 && Get(order[i]) != Get(order[i - 1])) r++;
      rnk[order[i]] = r;
    }
    if (r == N || (1 << k) >= N) break;
  }

  auto Up = [&](int x, int k) {
    for (int i = 0; i < 20 && k > 0; ++i) {
      if (k >> i & 1) {
        x = fa[x][i];
        k -= (1 << i);
      }
    }
    return x;
  };

  while (Q--) {
    string s;
    cin >> s;
    if (s.size() > N) {
      cout << "0\n";
      continue;
    }
    int l = 0, r = N, ans = 0;
    for (int i = 0; i < s.size(); ++i) {

      auto LessThan = [&](int p, char x) {
        if (dep[p] < i) return true;
        p = Up(p, i);
        return c[p] < x;
      };

      auto Equal = [&](int p, char x) {
        if (dep[p] < i) return false;
        p = Up(p, i);
        return c[p] == x;
      };

      if (LessThan(order[l], s[i])) {
        for (int d = 20; d >= 0; --d) {
          if (l + (1 << d) < r && LessThan(order[l + (1 << d)], s[i])) {
            l += (1 << d);
          }
        }
        l++;
        if (l == r) {
          break;
        }
      }
      if (!Equal(order[l], s[i])) {
        break;
      }
      int p = l;
      for (int d = 20; d >= 0; --d) {
        if (p + (1 << d) < r && Equal(order[p + (1 << d)], s[i])) {
          p += (1 << d);
        }
      }
      r = p + 1;
      if (i + 1 == s.size()) {
        ans = r - l;
      }
    }
    cout << ans << "\n";
  }
}

