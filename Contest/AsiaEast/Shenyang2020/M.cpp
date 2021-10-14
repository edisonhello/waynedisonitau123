#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  int64_t K;
  cin >> N >> M >> K;
  vector<int64_t> A(1 << M), B(1 << M);
  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s;
    assert(s.size() == M);
    int mask = 0;
    for (int j = 0; j < M; ++j) {
      if (s[j] == 'B') mask ^= (1 << j);
    }
    A[mask]++;
    B[((1 << M) - 1) ^ mask]++;
  }

  auto Transform = [&](auto dfs, vector<int64_t>& A, int p, int L) -> void {
    if (L == 1) return;
    dfs(dfs, A, p, L / 2);
    dfs(dfs, A, p + L / 2, L / 2);
    for (int i = 0; i < L / 2; ++i) {
      int64_t x = A[p + i];
      A[p + i] += A[p + i + L / 2];
      A[p + i + L / 2] = x - A[p + i + L / 2];
    }
  };

  auto InvTransform = [&](auto dfs, vector<int64_t>& A, int p, int L) -> void {
    if (L == 1) return;
    for (int i = 0; i < L / 2; ++i) {
      int64_t x = A[p + i];
      int64_t y = A[p + i + L / 2];
      A[p + i] = (x + y) / 2;
      A[p + i + L / 2] = (x - y) / 2;
    }
    dfs(dfs, A, p, L / 2);
    dfs(dfs, A, p + L / 2, L / 2);
  };

  Transform(Transform, A, 0, (1 << M));
  Transform(Transform, B, 0, (1 << M));
  for (int i = 0; i < (1 << M); ++i) A[i] *= B[i];
  InvTransform(InvTransform, A, 0, (1 << M));

  A[(1 << M) - 1] -= N;
  for (int i = 0; i < (1 << M); ++i) A[i] /= 2;

  for (int i = 0; i < M; ++i) {
    for (int s = 0; s < (1 << M); ++s) {
      if ((s >> i & 1) == 0) A[s] += A[s ^ (1 << i)];
    }
  }
  int ans = 0;
  for (int i = 0; i < (1 << M); ++i) {
    if (1LL * N * (N - 1) / 2 - A[i] >= K) ans++;
  }
  cout << ans << "\n";
}
