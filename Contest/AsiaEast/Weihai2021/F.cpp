#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  while (true) {
    int p = -1;
    for (int i = 0; i < N; ++i) {
      if (A[i] % 2 == 1) {
        if (p == -1 || A[i] < A[p]) {
          p = i;
        }
      }
    }
    if (p != -1) {
      cout << (A[p] + 1) / 2 << "\n";
      return 0;
    }
    for (int i = 0; i < N; ++i) {
      A[i] /= 2;
    }
  }
}

