#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(clock() * time(0));
  int N = 100, M = 1000;
  cout << N << " " << M << endl;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cout << "BW"[rand() % 2] << " ";
    cout << "\n";
  }
}
