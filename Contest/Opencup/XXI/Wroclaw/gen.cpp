#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(clock() + time(0));
  cout << 1 << "\n";
  int N = 20;
  cout << N << "\n";
  for (int i = 0; i < N; ++i) cout << rand() % 20 + 1 << " ";
  cout << "\n";
  int Q = rand() % 20 + 1;
  int P = rand() % 20 + 1 + Q;
  cout << P << " " << Q << "\n";
}
