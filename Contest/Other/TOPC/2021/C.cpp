#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    A[i]--;
  }

  vector<int> fw(N + 1);

  auto Update = [&](int p) {
    for (int i = p + 1; i <= N; i += i & -i) {
      fw[i]++;
    }
  };

  auto Query = [&](int p) {
    int res = 0;
    for (int i = p + 1; i > 0; i -= i & -i) {
      res += fw[i];
    }
    return res;
  };

  int64_t ans = 0;
  for (int i = N - 1; i >= 0; --i) {
    ans += Query(A[i]);
    Update(A[i]);
  }
  cout << ans << "\n";
}
