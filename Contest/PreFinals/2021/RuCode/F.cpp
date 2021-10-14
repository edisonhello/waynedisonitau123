#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 500 + 5;
int A[kN][kN], f[kN], op[kN];
int p[kN], s[kN], group[kN];
vector<int> gr[kN];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    for (int j = 1; j <= M; ++j) cin >> A[i][j];
    A[i][0] = 0;
  }
  int64_t ans = 0;
  vector<int> left(M + 1);
  vector<vector<int>> buckets;
  for (int i = 0; i < N; ++i) {
    memset(p, 0, sizeof(p));
    memset(group, 0, sizeof(group));
    int G = 0;
    for (int j = i; j < N; ++j) {
      for (int k = 0; k <= M; ++k) p[k] ^= A[j][k];
      s[0] = A[j][0];
      for (int k = 1; k <= M; ++k) s[k] = s[k - 1] ^ A[j][k];
      if (j == i) {
        {
          bool ok = false;
          for (int k = 0; k <= M; ++k) {
            if (s[k] == 0) group[k] = G, ok = true;
          }
          if (ok) G++;
        }
        {
          bool ok = false;
          for (int k = 0; k <= M; ++k) {
            if (s[k] == 1) group[k] = G, ok = true;
          }
          if (ok) G++;
        }
      } else {
        fill(f, f + G, -1);
        fill(op, op + G, -1);
        for (int k = 0; k <= M; ++k) {
          if (f[group[k]] == -1) {
            f[group[k]] = s[k];
          } else {
            if (s[k] != f[group[k]]) {
              if (op[group[k]] == -1) op[group[k]] = G++;
              group[k] = op[group[k]];
            }
          }
        }
      }
      int pv = 0;
      for (int k = 0; k <= M; ++k) {
        if (p[k]) {
          left[k] = -1;
          pv = k + 1;
        } else {
          left[k] = pv;
        }
      }
      for (int k = 0; k <= M; ++k) gr[group[k]].push_back(k);
      for (int g = 0; g < G; ++g) {
        const auto &B = gr[g];
        for (int i = 1, j = 0; i < B.size(); ++i) {
          if (left[B[i]] == -1) continue;
          while (j < i && B[j] + 1 < left[B[i]]) j++;
          ans += i - j;
        }
      }
      for (int g = 0; g < G; ++g) gr[g].clear();
    }
  }
  cout << ans << "\n";
  return 0;
}
