#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  const int M = 2 * N;
  vector<int> L(N, -1), R(N), which(M, -1);
  for (int i = 0; i < M; ++i) {
    int x;
    cin >> x;
    x--;
    which[i] = x;
    if (L[x] == -1) L[x] = i;
    else R[x] = i;
  }

  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) { return L[i] < L[j]; });

  int Rb = -1;
  vector<int> up(N, -1);
  for (int i = 0; i < N; ++i) {
    if (Rb > R[order[i]]) up[order[i]] = which[Rb];
    Rb = max(Rb, R[order[i]]); 
  }

  sort(order.begin(), order.end(), [&](int i, int j) { return R[i] < R[j]; });

  int Lb = -1;
  vector<int> down(N, -1);
  for (int i = 0; i < N; ++i) {
    if (Lb > L[order[i]]) down[order[i]] = which[Lb];
    Lb = max(Lb, L[order[i]]);
  }

  vector<vector<int>> fup(N, vector<int>(20, -1));
  vector<vector<int>> fdown(N, vector<int>(20, -1));
  for (int i = 0; i < N; ++i) {
    if (up[i] != -1) {
      int j = down[up[i]];
      if (i != j) fdown[i][0] = j;
    }
    if (down[i] != -1) {
      int j = up[down[i]];
      if (i != j) fup[i][0] = j;
    }
  }

  for (int k = 1; k < 20; ++k) {
    for (int i = 0; i < N; ++i) {
      if (fup[i][k - 1] != -1) {
        fup[i][k] = fup[fup[i][k - 1]][k - 1];
      }
      if (fdown[i][k - 1] != -1) {
        fdown[i][k] = fdown[fdown[i][k - 1]][k - 1];
      }
    }
  }

  // cout << "fup: ";
  // for (int i = 0; i < N; ++i) cout << fup[i][0] << " ";
  // cout << endl;
  // cout << "fdown: ";
  // for (int i = 0; i < N; ++i) cout << fdown[i][0] << " ";
  // cout << endl;

  while (Q--) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    if (L[u] < L[v] && R[u] > R[v]) {
      cout << "1\n";
      continue;
    }
    if (L[v] < L[u] && R[v] > R[u]) {
      cout << "1\n";
      continue;
    }
    if (L[u] > L[v]) swap(u, v);
    assert(L[u] < L[v] && R[u] < R[v]);

    constexpr int kInf = 1'000'000'000;

    auto GoUp = [&](int u, int v) {
      if (R[u] >= R[v]) {
        assert(L[u] <= L[v]);
        if (R[u] == R[v]) return 0;
        return 1;
      }
      int ans = 0;
      for (int d = 19; d >= 0; --d) {
        if (fup[u][d] != -1 && R[fup[u][d]] < R[v]) {
          u = fup[u][d];
          ans += (1 << d);
        }
      }
      if (fup[u][0] == -1) return kInf;
      int pu = u;
      u = fup[u][0];
      ans = (ans + 1) * 2;
      if (!(R[u] >= R[v] && L[u] <= L[v])) {
        if (down[pu] == -1) return -1;
        ans--;
        u = down[pu];
        if (L[v] <= L[u] && R[v] >= R[u]) return ans + 1;
        return kInf;
      } else {
        if (R[u] > R[v]) ans++;
        return ans;
      }
    };

    auto GoDown = [&](int u, int v) {
      if (L[u] >= L[v]) {
        assert(R[u] <= R[v]);
        if (L[u] == L[v]) return 0;
        return 1;
      }
      int ans = 0;
      for (int d = 19; d >= 0; --d) {
        if (fdown[u][d] != -1 && L[fdown[u][d]] < L[v]) {
          u = fdown[u][d];
          ans += (1 << d);
        }
      }
      if (fdown[u][0] == -1) return kInf;
      int pu = u;
      u = fdown[u][0];
      ans = (ans + 1) * 2;
      if (!(L[u] >= L[v] && R[u] <= R[v])) {
        if (up[pu] == -1) return -1;
        ans--;
        u = up[pu];
        if (L[u] <= L[v] && R[u] >= R[v]) return ans + 1;
        return kInf;
      } else {
        if (L[u] > L[v]) ans++;
        return ans;
      }
    };

    int ans = min(GoUp(u, v), GoDown(u, v));
    if (up[u] != -1) ans = min(ans, GoUp(up[u], v) + 1);
    if (down[u] != -1) ans = min(ans, GoDown(down[u], v) + 1);
    if (ans > kInf / 2) ans = -1;
    cout << ans << "\n";
  }
  return 0;
}
