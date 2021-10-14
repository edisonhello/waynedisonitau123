#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  vector<int> suff(N);
  for (int i = N - 1; i >= 0; --i) {
    suff[i] = A[i];
    if (i + 1 < N) suff[i] = min(suff[i + 1], suff[i]);
  }
  int x = 0, ans = 0;
  for (int i = 0; i < N; ++i) {
    x = max(x, A[i]);
    if (i + 1 == N || x <= suff[i + 1]) ans++;
  }
  cout << ans << "\n";
  return 0;
}
