#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(clock() + time(0));
  cout << 1 << "\n";
  int N = rand() % 10 + 1;
  int k = rand() % N + 1;
  cout << k << " ";
  for (int i = 0; i < N; ++i) {
    cout << "abcd"[rand() % 4];
  }
  cout << "\n";
}
