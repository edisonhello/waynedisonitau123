#include <bits/stdc++.h>
using namespace std;

void Solve() {
  int N;
  cin >> N;
  vector<pair<int, int>> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i].first;
    A[i].second = i;
  }
  sort(A.begin(), A.end());
  int P, Q;
  cin >> P >> Q;
  int64_t sum = 0;
  vector<int> to(N);
  vector<int64_t> rsum(N);
  vector<int64_t> psum(N + 1);
  vector<int> H(N + 1);
  for (int i = 0; i < N; ++i) psum[i + 1] = psum[i] + A[i].first;
  for (int i = N - 1; i >= 0; --i) {
    int l = i;
    for (int d = 20; d >= 0; --d) {
      if (l - (1 << d) >= 0) {
        int L = l - (1 << d);
        int64_t sum = psum[i + 1] - psum[L];
        int cnt = i + 1 - L;
        if (1LL * A[i].first * Q * cnt <= 1LL * P * sum) l = L;
      }
    }
    to[i] = l;
  }
  int best = 0;
  for (int i = 0; i < N; ++i) best = max(best, i - to[i] + 1);
  if (best == 1) {
    cout << "0\n\n";
    return;
  }
  vector<pair<int, int>> seg;
  for (int i = 0; i < N; ++i) {
    if (i - to[i] + 1 == best) seg.emplace_back(to[i], i);
  }
  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  vector<vector<int64_t>> rem(N);
  multiset<int64_t> tags;
  for (auto [l, r] : seg) {
    H[l]++;
    H[r + 1]--;
    int64_t target = (1LL * A[r].first * Q * best + P - 1) / P; // must >= target
    assert(psum[r + 1] - psum[l] >= target);
    int left = A[l].first;
    int64_t v = target + left - (psum[r + 1] - psum[l]);
    tags.insert(v);
    rem[l].push_back(v);
  }
  int64_t T = kInf;
  vector<int> res;
  int Z = 0;
  for (int i = 0; i < N; ++i) {
    Z += H[i];
    int64_t x = !tags.empty() ? *tags.begin() : kInf;
    if (Z == 0 && A[i].first < x) res.push_back(A[i].second);
    for (int64_t v : rem[i]) tags.erase(tags.find(v));
  }
  sort(res.begin(), res.end());
  cout << res.size() << "\n";
  for (int u : res) cout << u + 1 << " ";
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) Solve();
}
