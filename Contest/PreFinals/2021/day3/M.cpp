#include <bits/stdc++.h>
using namespace std;

int main() {
  int p = -1;
  double ex = -1E9;
  for (int i = 1; i <= 20; ++i) {
    double s = 0;
    for (int j = 1; j <= 20; ++j) {
      int A = -i + j, B = -j + i;
      if (i > j) A += 10, B -= 10;
      if (j > i) A -= 10, B += 10;
      s += A;
    }
    double e = s / 20;
    if (e > ex) {
      ex = e;
      p = i;
    }
  }
  double s = 0;
  for (int i = 1; i <= 20; ++i) {
    int A = -i + p;
    if (i > p) A += 10;
    if (i < p) A -= 10;
    s += A;
  }
  int n;
  cin >> n;
  cout << fixed << setprecision(20) << s / 20 * (n - 1) << "\n";
}
