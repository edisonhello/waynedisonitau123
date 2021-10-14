#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());
  int w = rand() % 5 + 1;
  int h = rand() % 5 + 1;
  int k = rand() % 5 + 1;
  cout << h << ' ' << w << ' ' << k << endl;

  vector<int> v;
  for (int i = 0; i < h; ++i) {
    for (int j = 0 ;j < w; ++ j) {
      v.push_back(j + 1);
    }
  }

  random_shuffle(v.begin(), v.end());

  for (int i : v) cout << i << ' ';
  cout << endl;
}
