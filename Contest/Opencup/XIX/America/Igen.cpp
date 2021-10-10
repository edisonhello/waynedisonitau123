#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());

  int t; 
  t = 1;
  cout << t << endl;
  while (t--) {

    int n = rand() % 7 + 1;
    string s;
    for (int i = 0; i < n; ++i) {
      s += "abcd"[rand() & 3];
    }

    int k = rand() % s.size() + 1;

    cout << k << ' ' << s << endl;

  }

}
