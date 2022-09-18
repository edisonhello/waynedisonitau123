#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int64_t N;
  cin >> N;
  int M;
  cin >> M;
  int64_t x, y;
  cin >> x >> y;
  vector<int64_t> p(M);
  for (int i = 0; i < M; ++i) {
    cin >> p[i];
  }
  int64_t prv = 0;
  int64_t ans = 0;
  for (int i = 0; i < M; ++i) {
    int64_t len = p[i] - (i > 0 ? p[i - 1] : 0) - 1;
    int64_t cur = x;
    if (prv > 0) {
      cur = min(cur, y - prv);
    }
    if (cur >= len) {
      prv = len;
    } else {
      assert(cur <= x && y - cur <= x);
      int64_t U = ((len + y - 1) / y) * 2;
      int64_t rest = U + 1;
      int64_t last = 0;
      for (int d = 60; d >= 0; --d) {
        if (rest - (1LL << d) > 0) {
          int64_t nr = rest - (1LL << d);
          int64_t total = cur * ((nr + 1) / 2) + (y - cur) * (nr / 2) + nr;
          int64_t t = total;
          if (nr & 1) {
            total += y - cur;
          } else {
            total += cur;
          }
          if (total >= len) {
            rest = nr;
            last = len - t;
          }
        }
      }
      assert(rest <= U);
      ans += rest;
      prv = last;
    }
  }
  int64_t len = N - (M > 0 ? p[M - 1] : 0);
  if (len > 0) {
    int64_t cur = x;
    if (prv > 0) {
      cur = min(cur, y - prv);
    }
    if (cur >= len) {
      prv = len;
    } else {
      assert(cur <= x && y - cur <= x);
      int64_t U = ((len + y - 1) / y) * 2;
      int64_t rest = U + 1;
      int64_t last = 0;
      for (int d = 60; d >= 0; --d) {
        if (rest - (1LL << d) > 0) {
          int64_t nr = rest - (1LL << d);
          int64_t total = cur * ((nr + 1) / 2) + (y - cur) * (nr / 2) + nr;
          int64_t t = total;
          if (nr & 1) {
            total += y - cur;
          } else {
            total += cur;
          }
          if (total >= len) {
            rest = nr;
            last = len - t;
          }
        }
      }
      assert(rest <= U);
      ans += rest;
      prv = last;
    }
  }
  cout << ans << "\n";
  return 0;
}
