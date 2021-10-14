#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, D, C;
  cin >> N >> D >> C;
  if (D == 0) {
    if (C == N) {
      cout << "Yes\n";
      for (int i = 0; i < N; ++i) cout << "\n";
    } else {
      cout << "No\n";
    }
    return 0;
  }
  if (D == 1) {
    if (N % 2 == 0 && C == N / 2) {
      cout << "Yes\n";
      for (int i = 0; i < N; ++i) {
        cout << (i ^ 1) + 1 << "\n";
      }
    } else {
      cout << "No\n";
    }
    return 0;
  }
  if (N < 1LL * C * (D + 1)) {
    cout << "No\n";
    return 0;
  }
  if (N % 2 == 1 && D % 2 == 1) {
    cout << "No\n";
    return 0;
  }
  cout << "Yes\n";
  for (int i = 0; i < C - 1; ++i) {
    for (int j = 0; j < D + 1; ++j) {
      for (int k = 0; k < D + 1; ++k) {
        if (j != k) {
          cout << i * (D + 1) + k + 1 << " ";
        }
      }
      cout << "\n";
    }
  }
  int M = N - (C - 1) * (D + 1);
  if (D % 2 == 1) assert(M % 2 == 0);
  int B = (C - 1) * (D + 1);
  for (int i = 0; i < M; ++i) {
    vector<int> E;
    for (int j = 1; j <= D / 2; ++j) {
      int k = (i + j) % M;
      E.push_back(k + B + 1);
      k = (i + M - j) % M;
      E.push_back(k + B + 1);
    }
    if (D % 2 == 1) {
      int k = (i + M / 2) % M;
      E.push_back(k + B + 1);
    }
    sort(E.begin(), E.end());
    for (int u : E) cout << u << " ";
    cout << "\n";
  }
}
