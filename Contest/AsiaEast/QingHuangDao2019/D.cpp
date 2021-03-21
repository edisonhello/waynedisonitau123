#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    while (N % 2 == 0) N /= 2;
    while (N % 5 == 0) N /= 5;
    if (N > 1) cout << "Yes\n";
    else cout << "No\n";
  }
}
