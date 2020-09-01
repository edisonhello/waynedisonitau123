#include <bits/stdc++.h>
using namespace std;

int Solve() {
  int N, K;
  cin >> N >> K;
  vector<int64_t> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  sort(A.begin(), A.end());

  auto Check = [&](int v) {
    assert(v * K <= N);
    vector<bool> used(N);
    vector<int64_t> last(v);
    for (int i = 0; i < v; ++i) {
      used[i] = true;
      last[i] = A[i];
    }
    int ptr = v;
    for (int s = 0; s < K - 1; ++s) {
      for (int i = 0; i < v; ++i) {
        while (ptr < N && A[ptr] < last[i] * 2) ptr++;
        if (ptr == N) return false;
        last[i] = A[ptr++];
      }
    }
    return true;
  };

  int ans = 0;
  for (int bit = 20; bit >= 0; --bit) {
    if (K * (ans + (1 << bit)) > N) continue;
    if (Check(ans + (1 << bit))) ans += (1 << bit);
  }
  return ans;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    cout << "Case #" << i + 1 << ": ";
    cout << Solve() << "\n";
  }
}
