#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  int mn = INT_MAX;
  while (n --) {
    int a, b; 
    cin >> a >> b;
    mn = min(mn, b / a);
  }
  cout << mn << endl;
}

