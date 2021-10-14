#include <bits/stdc++.h>
using namespace std;

struct Median {
  priority_queue<int> lq;
  priority_queue<int, vector<int>, greater<int>> rq;
  int64_t ls, rs;
  int sz;

  Median() : sz(0), ls(0), rs(0) {}

  void Push(int v) {
    sz++;
    lq.push(v);
    ls += v;
    while (lq.size() > sz / 2) {
      rs += lq.top();
      ls -= lq.top();
      rq.push(lq.top());
      lq.pop();
    }
    while (!lq.empty() && !rq.empty() && lq.top() > rq.top()) {
      int x = lq.top();
      lq.pop();
      int y = rq.top();
      rq.pop();
      ls -= x;
      ls += y;
      rs += x;
      rs -= y;
      lq.push(y);
      rq.push(x);
    }
  }

  int64_t GetCost() const {
    assert(!rq.empty());
    int med = rq.top();
    return 1LL * med * lq.size() - ls + rs - 1LL * med * rq.size();
  }
};

int main() {
  int N;
  cin >> N;
  vector<int> A(N + 1);
  for (int i = 1; i <= N; ++i) cin >> A[i];

  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  vector<int64_t> dp(N + 1);
  for (int i = 1; i <= N; ++i) {
    Median med;
    dp[i] = kInf;
    for (int j = i; j > 0; --j) {
      med.Push(A[j]);
      if (j < i) {
        dp[i] = min(dp[i], dp[j] + med.GetCost());
      }
    }
    dp[i] = min(dp[i], med.GetCost());
  }
  cout << dp[N] << "\n";
  return 0;
}
