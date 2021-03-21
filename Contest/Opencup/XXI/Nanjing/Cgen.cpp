#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(clock() + time(0));
  int T = 1;
  cout << T << endl;
  for (int i = 0; i < T; ++i) {
    int N = 5;
    cout << N << endl;
    for (int i = 0; i < N; ++i) {
      cout << rand() % 10 - 5 << " " << rand() % 10 - 5 << endl;
    }
  }
}
