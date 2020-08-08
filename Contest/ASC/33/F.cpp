#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("knights.in", "r", stdin);
  freopen("knights.out", "w", stdout);
  int n;
  while (cin >> n) {
    if (n == 0) break;
    int X = 1E9, Y = 1E9;
    for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      X = min(X, x);
      Y = min(Y, y);
    }

    int g = min(X / 3, Y / 3);
    X -= g * 3;
    Y -= g * 3;

    if (X < 2 || Y < 2) {
      if (X / 2 > Y / 2) cout << "Andrew wins the game" << "\n";
      else cout << "Peter wins the game" << "\n";
    } else {
      int a = 0, b = 0;
      if (X == 2) {
        b += (Y - 2) / 2;
        Y -= (Y - 2) / 2 * 2;
      }
      if (Y == 2) {
        a += (X - 2) / 2;
        X -= (X - 2) / 2 * 2;
      }
      if (X == 2 && Y == 3) b++;
      if (X == 3 && Y == 2) a++;
      if (X == 2 && Y == 2) a++;
      if (a > b) cout << "Andrew wins the game" << "\n";
      else cout << "Peter wins the game" << "\n";
    }
  }
}
