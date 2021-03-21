#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < M; ++i) cin >> B[i];
    sort(A.begin(), A.end());
    B.push_back(0);
    B.push_back(1'000'000'000 + 123);
    sort(B.begin(), B.end());
    int ans = 0;
    for (int i = 0; i + 1 < B.size(); ++i) {
      if (B[i] < B[i + 1] - 1) {
        int t = upper_bound(A.begin(), A.end(), B[i + 1] - 1) - lower_bound(A.begin(), A.end(), B[i] + 1);
        ans = max(ans, t);
      }
    }
    if (ans == 0) cout << "Impossible\n";
    else cout << ans << "\n";
  }
}
