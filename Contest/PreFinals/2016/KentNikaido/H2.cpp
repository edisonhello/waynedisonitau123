#include <bits/stdc++.h>
using namespace std;

int main() {
  int l, n;
  cin >> l >> n;
  int res = (l % 2 == 0);

  function<int64_t(int)> Count = [&](int n) -> int64_t {
    if (n <= 1) return 0;
    return n / 2 + Count(n / 2);
  };

  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    int x = l - a;
    int y = b - 1;
    int z = a - b;
    int64_t g = Count(x + y + z);
    int64_t h = Count(x) + Count(y) + Count(z);
    assert(g >= h);
    if (g == h) res ^= 1;
  }
  if (res) cout << "Iori\n";
  else cout << "Yayoi\n";
  return 0;
}
