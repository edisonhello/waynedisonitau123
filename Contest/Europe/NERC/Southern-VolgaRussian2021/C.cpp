#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int N, K, x, y;
    cin >> N >> K >> x >> y;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; ++i) {
      string s;
      int f;
      cin >> s >> f;
      if (s == "A") {
        A[i] = f;
        B[i] = f - x;
      } else {
        A[i] = f - y;
        B[i] = f;
      }
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
      return make_pair(A[i], B[i]) > make_pair(A[j], B[j]);
    });

    priority_queue<pair<int, int>> pq;
    int64_t sum = 0;
    int64_t ans = -1'000'000'000'000'000'000;

    vector<int> ds(B.begin(), B.end());
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

    int M = ds.size();
    int sz = 1;
    while (sz < M + 1) {
      sz <<= 1;
    }
    sz <<= 1;
    vector<int64_t> fw(sz);
    vector<int> cnt(sz);

    auto Update = [&](int p, int64_t x, int y) {
      for (int i = p + 1; i < sz; i += i & -i) {
        fw[i] += x;
        cnt[i] += y;
      }
    };

    auto Query = [&](int k) {
      int p = 0;
      int64_t res = 0;
      for (int bit = sz / 2; bit > 0; bit >>= 1) {
        if (cnt[p + bit] <= k) {
          res += fw[p + bit];
          k -= cnt[p + bit];
          p += bit;
        }
      }
      if (k > 0) {
        assert(p + 1 < sz && cnt[p + 1] >= k);
        res += 1LL * ds[M - 1 - p] * k;
      }
      return res;
    };

    for (int i = 0; i < N; ++i) {
      int p = lower_bound(ds.begin(), ds.end(), B[i]) - ds.begin();
      Update(M - 1 - p, B[i], 1);
    }

    for (int i = 0; i < N; ++i) {
      int p = lower_bound(ds.begin(), ds.end(), B[order[i]]) - ds.begin();
      Update(M - 1 - p, -B[order[i]], -1);
      pq.emplace(B[order[i]] - A[order[i]], order[i]);
      sum += A[order[i]];
      if (pq.size() > K) {
        sum -= A[pq.top().second];
        int p =
            lower_bound(ds.begin(), ds.end(), B[pq.top().second]) - ds.begin();
        Update(M - 1 - p, B[pq.top().second], 1);
        pq.pop();
      }
      if (pq.size() == K) {
        ans = max(ans, sum + Query(K));
      }
    }
    cout << ans << "\n";
  }
}
