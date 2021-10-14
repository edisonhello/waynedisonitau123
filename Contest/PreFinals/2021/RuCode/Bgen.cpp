#include <bits/stdc++.h>
using namespace std;

int main() {
  int N = 10;
  srand(clock() + time(0));
  for (int i = 0; i < N; ++i) cout << rand() % 3;
  cout << endl;
}
