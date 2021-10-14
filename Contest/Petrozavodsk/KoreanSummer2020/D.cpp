#pragma GCC optimize("O3")
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, T;
  cin >> N >> T;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  vector<pair<int, int>> segs;
  vector<int> current(N), ed(N);
  int e = N - 1;
  for (int i = N - 1; i >= 0; --i) {
    if (i + 1 < N && A[i + 1] < A[i]) {
      segs.emplace_back(e, i + 1);
      e = i;
    }
    ed[i] = e;
  }
  segs.emplace_back(e, 0);
  reverse(segs.begin(), segs.end());
  const int M = segs.size();
  vector<int64_t> sum(M + 1);
  for (int i = 0; i < M; ++i) {
    sum[i + 1] = sum[i] + 1LL * (segs[i].first - segs[i].second + 1) *
                              (segs[i].first - segs[i].second + 2) / 2;
  }
  vector<int> which(N, -1);
  for (int i = 0; i < M; ++i) {
    for (int j = segs[i].second; j <= segs[i].first; ++j) which[j] = i;
  }

  auto GetScore = [&](int l, int r) -> int64_t {
    if (ed[l] >= r) return 1LL * (r - l + 1) * (r - l + 2) / 2;
    int64_t res = 1LL * (ed[l] - l + 1) * (ed[l] - l + 2) / 2;
    l = ed[l] + 1;
    if (ed[l] >= r) {
      res += 1LL * (r - l + 1) * (r - l + 2) / 2;
    } else {
      int nxt =
          upper_bound(segs.begin(), segs.end(), make_pair(r, N)) - segs.begin();
      res += sum[nxt] - sum[which[l]];
      l = segs[nxt - 1].first + 1;
      if (l <= r) {
        assert(ed[l] >= r);
        res += 1LL * (r - l + 1) * (r - l + 2) / 2;
      }
    }
    return res;
  };
  
  constexpr int64_t kInf = 1'000'000'000'000'000'000;

  while (T--) {
    int L, R;
    cin >> L >> R;
    L--;
    R--;
    int pos = L;
    for (int d = 20; d >= 0; --d) {
      if (pos + (1 << d) <= R) {
        int64_t x = GetScore(L, pos + (1 << d));
        int64_t y = GetScore(pos + (1 << d), R);
        if (y >= x) {
          pos += (1 << d);
        }
      }
    }
    int64_t res = kInf;
    for (int i = 0; i <= 1; ++i) {
      if (pos + i >= L && pos + i <= R) {
        int64_t x = GetScore(L, pos + i);
        int64_t y = GetScore(pos + i, R);
        res = min(res, max(x, y));
      }
    }
    cout << res << "\n";
  }
  return 0;
}
