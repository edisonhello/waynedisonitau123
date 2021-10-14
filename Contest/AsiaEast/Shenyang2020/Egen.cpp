#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(clock() + time(0));
  int M = rand() % 5 + 1;
  cout << M << endl;
  for (int i = 0; i < M; ++i) {
    int K = rand() % 5 + 1;
    vector<int> p(K);
    for (int j = 0; j < K; ++j) p[j] = rand() % 10 + 1;
    sort(p.begin(), p.end());
    cout << K << " ";
    for (int u : p) cout << u << " ";
    cout << endl;
  }
  cout << rand() % 5 + 1;
  for (int i = 0; i < M; ++i) cout << rand() % 5 + 1 << " ";
  cout << endl;
}
