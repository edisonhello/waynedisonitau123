#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<pair<int, int>> p(N);
  for (int i = 0; i < N; ++i) cin >> p[i].first;
  for (int i = 0; i < N; ++i) cin >> p[i].second;
  sort(p.rbegin(), p.rend());

  vector<bool> used(N);

  auto Check = [&](int k) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    priority_queue<pair<int, int>> pq2;
    fill(used.begin(), used.end(), false);
    int sz = 0;
    int64_t ps2 = 0;
    for (int i = k; i < N; ++i) {
      pq2.emplace(p[i].second, i);
      used[i] = true;
      sz++;
      ps2 += p[i].second;
      while (pq2.size() > k) {
        used[pq2.top().second] = false;
        ps2 -= pq2.top().first;
        pq2.pop();
        sz--;
      }
    }
    int64_t ps = 0, ms = 0;
    for (int i = 0; i < N; ++i) {
      pq.emplace(p[i].first + p[i].second, i);
      ms += p[i].first;
      while (pq.size() > k) {
        auto v = pq.top();
        pq.pop();
        ms -= p[v.second].first;
        ps += p[v.second].second;
      }
      if (used[i]) {
        used[i] = false;
        ps2 -= p[i].second;
        sz--;
      }
      if (pq.size() == k) {
        if (i + 1 - k >= k) {
          if (ms >= ps) return true;
        } else {
          int diff = k - (i + 1 - k);
          assert(sz >= diff);
          while (sz > diff) {
            if (used[pq2.top().second]) {
              sz--;
              ps2 -= pq2.top().first;
            } 
            pq2.pop();
          }
          if (ms >= ps + ps2) return true;
        }
      }
    }
    return false;
  };

  int ans = 0;
  for (int bit = 20; bit >= 0; --bit) {
    if (2 * (ans + (1 << bit)) <= N) {
      if (Check(ans + (1 << bit))) ans += (1 << bit);
    }
  }
  cout << ans << "\n";
}
