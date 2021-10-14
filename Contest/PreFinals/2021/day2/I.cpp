#include <bits/stdc++.h>
using namespace std;

constexpr int kP = 1'000'000'000 + 7;

int fpow(int a, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) res = 1LL * res * a % kP;
    a = 1LL * a * a % kP;
    n >>= 1;
  }
  return res;
}

bool Gauss(vector<vector<int>> &D, vector<int> &V) {
  int N = D.size();
  for (int i = 0; i < N; ++i) {
    int p = -1;
    for (int j = i; j < N; ++j) {
      if (D[j][i] > 0) {
        p = j;
        break;
      }
    }
    if (p == -1) return false;
    swap(D[p], D[i]);
    swap(V[p], V[i]);
    for (int j = i + 1; j < N; ++j) {
      int f = 1LL * D[j][i] * fpow(D[i][i], kP - 2) % kP;
      for (int k = i; k < N; ++k) {
        D[j][k] += kP - 1LL * f * D[i][k] % kP;
        D[j][k] %= kP;
      }
      V[j] += kP - 1LL * f * V[i] % kP;
      V[j] %= kP;
    }
  }
  return true;
}

int main() {
  int N, M, S;
  cin >> N >> M >> S;
  S--;
  vector<vector<int>> g(N), rev(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    rev[v].push_back(u);
  }

  vector<bool> vis(N);
  vector<int> que(1, S);
  vis[S] = true;
  for (int it = 0; it < que.size(); ++it) {
    int x = que[it];
    for (int u : rev[x]) {
      if (!vis[u]) {
        vis[u] = true;
        que.push_back(u);
      }
    }
  }

  if (g[S].empty()) {
    cout << "0\n";
    return 0;
  }

  vector<vector<int>> D(N, vector<int>(N));
  vector<int> V(N);
  for (int i = 0; i < N; ++i) {
    if (vis[i]) {
      int t = fpow(g[i].size(), kP - 2);
      for (int u : g[i]) D[i][u] = t;
      D[i][i] = kP - 1;
      V[i] = kP - 1;
    } else {
      D[i][i] = 1;
      V[i] = 0;
    }
  }
  if (!Gauss(D, V)) {
    cout << "-1\n";
    return 0;
  }
  vector<int> E(N);
  for (int i = N - 1; i >= 0; --i) {
    int s = 0;
    for (int j = i + 1; j < N; ++j) {
      s += 1LL * D[i][j] * E[j] % kP;
      s %= kP;
    }
    E[i] = 1LL * (V[i] + kP - s) * fpow(D[i][i], kP - 2) % kP;
  }
  cout << E[S] << "\n";
  return 0;
}
