#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K, Q;
  cin >> N >> K >> Q;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  vector<int> B = A;
  vector<double> ans(K + 1);
  sort(A.begin(), A.end());
  vector<int64_t> sum(N + 1);
  for (int i = 0; i < N; ++i) {
    sum[i + 1] = sum[i] + A[i];
  }
  int64_t total = sum[N] * (N - 1);
  int64_t div = 1LL * N * (N - 1) / 2;
  ans[0] = static_cast<double>(total) / div;
  for (int i = 1; i <= K; ++i) {
    int64_t cnt = 0;
    int64_t cur = total;
    for (int j = N - 1, k = 0; j >= 0; --j) {
      while (k < N && A[j] + A[k] <= ans[i - 1]) k++;
      int t = min(j, k);
      cnt += min(j, k);
      cur -= 1LL * A[j] * t + sum[t];
    }
    ans[i] = (cur + ans[i - 1] * cnt) / div;
  }
  cout << fixed << setprecision(20) << ans[K] << "\n";
  constexpr double kEps = 1E-5;
  while (Q--) {
    int i, j, c;
    cin >> i >> j >> c;
    if (c == 0) {
      cout << "accept\n";
      continue;
    }
    i--;
    j--;
    c--;
    if (ans[c] > B[i] + B[j] + kEps) {
      cout << "reselect\n";
    } else if (ans[c] < B[i] + B[j] - kEps) {
      cout << "accept\n";
    } else {
      cout << "both\n";
    }
  }
}

