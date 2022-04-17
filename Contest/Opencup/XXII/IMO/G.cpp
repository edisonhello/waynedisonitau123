#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<string> g(N);
  for (int i = 0; i < N; ++i) {
    cin >> g[i];
  }
  constexpr int kN = 2000;
  vector<bitset<kN>> adj(N);
  vector<bitset<kN>> comp(N);
  vector<int> deg(N), deg_comp(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i != j) {
        if (g[i][j] == 'B') {
          adj[i].set(j);
          deg[i]++;
        } else {
          comp[i].set(j);
          deg_comp[i]++;
        }
      }
    }
  }
  vector<vector<int>> T(N, vector<int>(N));
  vector<vector<int>> Tcomp(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      T[i][j] = (adj[i] & adj[j]).count();
      T[j][i] = T[i][j];
      Tcomp[i][j] = (comp[i] & comp[j]).count();
      Tcomp[j][i] = Tcomp[i][j];
    }
  }
  int64_t A = 0;
  int64_t B = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (g[i][j] == 'B') {
        int x = deg[i] - T[i][j] - 1;
        int y = deg[j] - T[i][j] - 1;
        A += 1LL * x * y;
      } else {
        B += 1LL * T[i][j] * (T[i][j] - 1) / 2;
      }
    }
  }
  int64_t C = 0;
  int64_t D = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (g[i][j] == 'Y') {
        int x = deg_comp[i] - Tcomp[i][j] - 1;
        int y = deg_comp[j] - Tcomp[i][j] - 1;
        C += 1LL * x * y;
      } else {
        D += 1LL * Tcomp[i][j] * (Tcomp[i][j] - 1) / 2;
      }
    }
  }
  cout << (A - 2 * B + C - 2 * D) / 2 << "\n";
  // A = 4 * C_4 + P_4
  // B = 4 * C_4 + 2 * (K_4 - e)
  // A - B = P_4 - 2 * (K_4 - e)
  // A' - B' = P_4 - 2 * e
  return 0;
}
