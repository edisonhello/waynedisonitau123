#include <bits/stdc++.h>
using namespace std;


int main() {
  int n; cin >> n;
  string s; cin >> s;

  for (int i = 1; i < n; ++i) {
    if (s[i] == s[0]) {
      cout << "Wrong Answer" << '\n';
      exit(0);
    }
  }
  cout << "Correct" << endl;
}
