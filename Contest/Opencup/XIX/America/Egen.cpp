#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());

  int n = rand() % 5 + 1;
  int m = rand() % 5 + 1;
  cout << n << ' ' << m << endl;

  vector<int> v(n * m);
  iota(v.begin(), v.end(), 1);

  random_shuffle(v.begin(), v.end());
  for (int i : v) cout << i << ' ';
  cout << endl;
}
