#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
      cin >> A[i];
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) { return A[i] < A[j]; });
    int64_t ans = 0;
    vector<int> B(N);
    for (int u : order) {
      int prv = -1;
      if (u > 0 && A[u - 1] < A[u]) {
        prv = max(prv, B[u - 1]);
      }
      if (u + 1 < N && A[u + 1] < A[u]) {
        prv = max(prv, B[u + 1]);
      }
      B[u] = prv + 1;
    }
    for (int i = 0; i < N; ++i) {
      ans += A[i] - B[i];
    }
    cout << "Case " << tc << ": ";
    if (ans & 1) {
      cout << "Alice\n";
    } else {
      cout << "Bob\n";
    }
  }
}
