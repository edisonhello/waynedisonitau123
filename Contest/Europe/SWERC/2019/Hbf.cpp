#include <bits/stdc++.h>
using namespace std;

int64_t ST=350125354;
int64_t ST2=532254563;

int main() {
  int64_t mask = (1ll << 40) - 1;
  int64_t s0 = 0x600DCAFE;

  int64_t n; cin >> n;
  
  int64_t i = 0;

  int64_t to = n;
  int64_t cnt = 0;

  while (true) {
    int b = s0 & ((1 << 20) - 1);
    int a = s0 >> 20;
    if (a < (1 << 16)) {
      int add = a + 12345;
      int t = ((1 << 20) - b - 1) / add;
      
      if (i + add >= to) {
        break;
      }

      if (add & 1) {
        cnt += (t + !(s0 & 1)) >> 1;
      } else {
        if (!(s0 & 1)) {
          cnt += t;
        }
      }

      i += t;
      s0 += 1ll * add * t;

      cnt += (s0 & 1) ^ 1;
      s0 = (s0 + (s0 >> 20) + 12345) & mask;
      ++i;
    } else {
      if (i >= to) break;

      cnt += (s0 & 1) ^ 1;
      s0 = (s0 + (s0 >> 20) + 12345) & mask;
      ++i;
    }
  }

  while (i < to) {
    cnt += (s0 & 1) ^ 1;
    s0 = (s0 + (s0 >> 20) + 12345) & mask;
    ++i;
  }

  cout << cnt << endl;
}

