#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;
  if (K == 0) {
    cout << "-1\n";
    return 0;
  }
  for (int i = 0; i < K; ++i) cout << (i + 1) % K + 1 << " ";
  for (int i = K; i < N; ++i) cout << i + 1 << " ";
  cout << "\n";
}
