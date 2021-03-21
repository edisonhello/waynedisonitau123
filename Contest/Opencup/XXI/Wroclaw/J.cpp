#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct ConvexHull {
  deque<pair<int64_t, int64_t>> dq;

  void Add(int64_t a, int64_t b) {
    if (!dq.empty() && dq.back().first == a) return;

    auto Kill = [&](auto L1, auto L2, auto L3) {
      return (L1.second - L3.second) * (L2.first - L1.first) <= (L1.second - L2.second) * (L3.first - L1.first);
    };

    while (dq.size() >= 2 && Kill(dq[dq.size() - 2], dq[dq.size() - 1], make_pair(a, b))) dq.pop_back();
    dq.emplace_back(a, b);
  }

  int64_t Query(int64_t x) {

    auto Eval = [&](auto L, int64_t x) {
      return L.first + L.second;
    };

    while (dq.size() >= 2 && Eval(dq[0], x) <= Eval(dq[1], x)) dq.pop_front();
    return Eval(dq[0], x);
  }
};

void Solve() {
  int N;
  cin >> N;
  vector<vector<int>> v(N, vector<int>(N)), p(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cin >> v[i][j];
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cin >> p[i][j];
  }
  int M = N * N;
  vector<int> x(M), y(M), cnt(M);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i > 0 && p[i][j] != p[i - 1][j]) y[p[i][j]]++;
      if (j > 0 && p[i][j] != p[i][j - 1]) y[p[i][j]]++;
      if (i + 1 < N && p[i][j] != p[i + 1][j]) y[p[i][j]]++;
      if (j + 1 < N && p[i][j] != p[i][j + 1]) y[p[i][j]]++;
      x[p[i][j]] += v[i][j];
      cnt[p[i][j]]++;
    }
  }

  constexpr int kB = 500;
  int Q;
  cin >> Q;
  vector<int64_t> A(Q), B(Q), C(Q);
  vector<tuple<int, int, int>> ops(Q);
  for (int i = 0; i < Q; ++i) {
    cin >> get<0>(ops[i]) >> get<1>(ops[i]) >> get<2>(ops[i]);
    get<0>(ops[i])--;
    get<1>(ops[i])--;
    cin >> A[i] >> B[i] >> C[i];
  }
  vector<bool> upd(M);
  vector<int> Max(4 * M, -2'000'000'000), Min(4 * M, 2'000'000'000);
  vector<bool> sz(4 * M);
  vector<vector<int>> init(N, vector<int>(N, -1));

  constexpr int64_t kInf = 1'000'000'000'000'000'000;

  for (int b = 0; b < Q; b += kB) {
    vector<pair<int, int>> yt;
    for (int it = b; it < min(b + kB, Q); ++it) {
      auto [i, j, k] = ops[it];
      assert(p[i][j] != k);
      upd[k] = true;
      upd[p[i][j]] = true;
      if (i > 0 && p[i][j] != p[i - 1][j]) upd[p[i - 1][j]] = true;
      if (j > 0 && p[i][j] != p[i][j - 1]) upd[p[i][j - 1]] = true;
      if (i + 1 < N && p[i][j] != p[i + 1][j]) upd[p[i + 1][j]] = true;
      if (j + 1 < N && p[i][j] != p[i][j + 1]) upd[p[i][j + 1]] = true;
      if (init[i][j] == -1) {
        init[i][j] = p[i][j];
        yt.emplace_back(i, j);
      }
      p[i][j] = k;
    }
    vector<int> use;
    for (int i = 0; i < M; ++i) {
      if (upd[i]) continue;
      if (cnt[i] == 0) continue;
      if (!sz[y[i]]) {
        sz[y[i]] = true;
        use.push_back(y[i]);
      }
      Max[y[i]] = max(Max[y[i]], x[i]);
      Min[y[i]] = min(Min[y[i]], x[i]);
    }
    vector<int> worklist;
    for (int i = 0; i < M; ++i) {
      if (upd[i]) {
        worklist.push_back(i);
        upd[i] = false;
      }
    }
    for (auto [i, j] : yt) {
      p[i][j] = init[i][j];
      init[i][j] = -1;
    }

    for (int it = b; it < min(b + kB, Q); ++it) {
      auto [i, j, k] = ops[it];
      {
        if (i > 0 && p[i - 1][j] != p[i][j]) y[p[i - 1][j]]--, y[p[i][j]]--;
        if (j > 0 && p[i][j - 1] != p[i][j]) y[p[i][j - 1]]--, y[p[i][j]]--;
        if (i + 1 < N && p[i + 1][j] != p[i][j]) y[p[i + 1][j]]--, y[p[i][j]]--;
        if (j + 1 < N && p[i][j + 1] != p[i][j]) y[p[i][j + 1]]--, y[p[i][j]]--;
        x[p[i][j]] -= v[i][j];
        cnt[p[i][j]]--;
      }
      p[i][j] = k;
      {
        if (i > 0 && p[i - 1][j] != p[i][j]) y[p[i - 1][j]]++, y[p[i][j]]++;
        if (j > 0 && p[i][j - 1] != p[i][j]) y[p[i][j - 1]]++, y[p[i][j]]++;
        if (i + 1 < N && p[i + 1][j] != p[i][j]) y[p[i + 1][j]]++, y[p[i][j]]++;
        if (j + 1 < N && p[i][j + 1] != p[i][j]) y[p[i][j + 1]]++, y[p[i][j]]++;
        x[p[i][j]] += v[i][j];
        cnt[p[i][j]]++;
      }
      int64_t ans = -kInf;
      for (int u : worklist) if (cnt[u] > 0) ans = max(ans, A[it] * x[u] + B[it] * y[u] + C[it] * x[u] * y[u]);
      for (int u : use) {
        ans = max(ans, A[it] * Max[u] + B[it] * u + C[it] * Max[u] * u);
        ans = max(ans, A[it] * Min[u] + B[it] * u + C[it] * Min[u] * u);
      }
      cout << ans << " ";
    }
    for (int u : use) {
      sz[u] = false;
      Max[u] = -2'000'000'000;
      Min[u] = 2'000'000'000;
    }
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) Solve();
}
