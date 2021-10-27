#include <bits/stdc++.h>
using namespace std;

void NO() {
  cout << "NaN" << endl;
  exit(0);
}

int main() {
  string s, t; cin >> s >> t;
  int a = 0, b = 0;
  for (char c : s) {
    if (c >= '0' && c <= '9') {
      a = a * 10 + (c & 15);
    } else NO();
  }
  for (char c : t) {
    if (c >= '0' && c <= '9') {
      b = b * 10 + (c & 15);
    } else NO();
  }

  cout << a - b << endl;
}
