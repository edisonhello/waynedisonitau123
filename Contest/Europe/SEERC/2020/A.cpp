#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<int> p(N);
  for (int i = 0; i < N; ++i) cin >> p[i];
  vector<int64_t> sum(N + 1);
  sum[N] = 0;
  for (int i = N - 1; i >= 0; --i) {
    sum[i] = sum[i + 1] + p[i];
  }
  priority_queue<int64_t> pq1, pq2;
  int64_t ans = 0;
  if (sum[0] >= sum[1]) {
    ans = sum[0] - sum[1];
    pq2.push(sum[1]);
  } else {
    ans = 0;
    pq1.push(sum[0]);
    pq1.push(sum[1]);
  }
  for (int i = 2; i < sum.size(); ++i) {
    if (!pq1.empty() && !pq2.empty()) {
      int64_t x = pq1.top();
      int64_t y = pq2.top();
      int64_t z = max(x - sum[i], y - sum[i]);
      if (z < 0) {
        pq1.push(sum[i]);
      } else if (x > y) {
        ans += x - sum[i];
        pq2.push(sum[i]);
        pq1.pop();
      } else {
        ans += y - sum[i];
        pq2.pop();
        pq1.push(y);
        pq2.push(sum[i]);
      }
    } else if (!pq1.empty()) {
      int64_t x = pq1.top();
      if (x - sum[i] < 0) {
        pq1.push(sum[i]);
      } else {
        ans += x - sum[i];
        pq2.push(sum[i]);
        pq1.pop();
      }
    } else if (!pq2.empty()) {
      int64_t y = pq2.top();
      if (y - sum[i] < 0) {
        pq1.push(sum[i]);
      } else {
        ans += y - sum[i];
        pq2.pop();
        pq1.push(y);
        pq2.push(sum[i]);
      }
    } else {
      pq1.push(sum[i]);
    }
  }
  cout << ans << "\n";
}
