#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    int P, Q;
    cin >> P >> Q;
    int M = N;
    for (int s = 0; s + 1 < (1 << N); ++s) {
      vector<int> value;
      for (int i = 0; i < N; ++i) {
        if (!(s >> i & 1)) value.push_back(A[i]);
      }
      sort(value.begin(), value.end());
      int sum = accumulate(value.begin(), value.end(), 0);
      int cnt = value.size();
      if (P * sum >= value.back() * Q * cnt) M = min(M, __builtin_popcount(s));
    }
    int ways = 0;
    vector<int> cover(N);
    for (int s = 0; s + 1 < (1 << N); ++s) {
      if (__builtin_popcount(s) != M) continue;
      vector<int> value;
      for (int i = 0; i < N; ++i) {
        if (!(s >> i & 1)) value.push_back(A[i]);
      }
      sort(value.begin(), value.end());
      int sum = accumulate(value.begin(), value.end(), 0);
      int cnt = value.size();
      if (P * sum >= value.back() * Q * cnt) {
        ways++;
        for (int i = 0; i < N; ++i) {
          if (s >> i & 1) cover[i]++;
        }
      }
    }
    vector<int> res;
    for (int i = 0; i < N; ++i) {
      if (cover[i] == ways) res.push_back(i);
    }
    cout << res.size() << "\n";
    for (int u : res) cout << u + 1 << " ";
    cout << "\n";
  }
}
