#include <bits/stdc++.h>
using namespace std;

int Query(vector<int> v) {
  cout << "? " << v.size();
  for (int u : v) {
    cout << " " << u + 1;
  }
  cout << endl;
  int res;
  cin >> res;
  return res;
}

int main() {
  int N;
  cin >> N;
  mt19937 rng(0x7122);
  vector<int> all(N);
  iota(all.begin(), all.end(), 0);
  int M = Query(all);
  for (int i = 0; i < 29; ++i) {
    while (true) {
      vector<int> A, B;
      for (int j = 0; j < N; ++j) {
        if (rng() & 1) {
          A.push_back(j);
        } else {
          B.push_back(j);
        }
      }
      if (A.empty() || B.empty()) {
        continue;
      }
      int X = Query(A);
      int Y = Query(B);
      if ((M - X - Y) % 2 == 1) {
        cout << "! NO" << endl;
        return 0;
      }
      break;
    }
  }
  cout << "! YES" << endl;
  return 0;
}
