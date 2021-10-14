#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(clock() + time(0));
  int N = 6;
  cout << N << "\n";
  for (int i = 0; i < N; ++i) cout << rand() % N + 1 << " ";
  cout << "\n";
}
