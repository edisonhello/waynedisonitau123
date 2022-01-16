#include <bits/stdc++.h>
using namespace std;


int main() {
  int n, a, b; 
  cin >> n >> a >> b;

  string ans = "";
  if (a <= n / 2) {
    for (int i = 0; i < n - 1; ++i) ans += "U";
    for (int i = 1; i < a; ++i) ans += "D";
  } else {
    for (int i = 0; i < n - 1; ++i) ans += "D";
    for (int i = n; i > a; --i) ans += "U";
  }

  if (b <= n / 2) {
    for (int i = 0; i < n - 1; ++i) ans += "L";
    for (int i = 1; i < b; ++i) ans += "R";
  } else {
    for (int i = 0; i < n - 1; ++i) ans += "R";
    for (int i = n; i > b; --i) ans += "L";
  }

  cout << ans << '\n';
}

