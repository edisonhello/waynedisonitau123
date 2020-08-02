#include <bits/stdc++.h>
using namespace std;

int main() {
  auto Read = [&]() {
    int x, y;
    scanf("%d.%d", &x, &y);
    return x * 100 + y;
  };

  int t1 = Read();
  int t2 = Read();
  int t3 = Read();
  int t4 = Read();
  int t = Read();

  int res = -1;
  for (int d = 29; d >= 0; --d) {
    int tres = res + (1 << d);
    vector<int> v = {t1, t2, t3, t4, tres};
    sort(v.begin(), v.end());
    if ((v[1] + v[2] + v[3]) <= t * 3) {
      res = tres;
    }
  }

  if (res == -1) cout << "impossible\n";
  else if (res == (1 << 30) - 2) cout << "infinite\n";
  else printf("%d.%02d\n", res / 100, res % 100);
}
