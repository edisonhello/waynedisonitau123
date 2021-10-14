#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A.rbegin(), A.rend());
  cout << accumulate(A.begin(), A.begin() + K, 0LL) << "\n";
}
