#include <bits/stdc++.h>
using namespace std;;
#define int int64_t


int32_t main() {
  int n, x, r, p, k;
  cin >> n >> x >> r >> p >> k;

  string s;
  cin >> s;

  auto next_heal = [&](int x) {
    while (x < s.size() && s[x] == '0') ++x;
    return x;
  };

  int front = 0;
  int heal = next_heal(0);

  vector<int> casted(n + 2, 0);

  int pohp = 0;

  while (k--) {
    int cast_front = (n - front) * p;
    int cast_heal = (n - heal) * (p + r);

    if (cast_front >= cast_heal) {
      pohp += cast_front;
      casted[front] = 1;
    } else {
      pohp += cast_heal;
      casted[heal] = 1;

      if (heal < n)
        heal = next_heal(heal + 1);
    }

    while (front < n && casted[front]) ++front;
  }

  int nowp = 0, nowr = 0, diff = 0;

  for (int i = 0; i < n; ++i) {
    if (s[i] == '1') ++nowr;
    if (casted[i]) {
      if (nowr > 0) --nowr;
      ++nowp;
    }
    diff += x + p * nowp - r * nowr;
  }

  cout << diff << endl;

}

