#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N, P;
    cin >> N >> P;
    int s = 0;

    auto Get = [&](auto self, int l, int r) -> int {
      if (1LL * l * P + 1 == r) {
        return 0;
      }
      if (1LL * l * P >= r) {
        return r - l + 1;
      }
      if ((r - 1) % P == 0) {
        return self(self, l, (r - 1) / P - 1);
      }
      return r - ((r + P - 1) / P) + 1;
    };

    for (int i = 0; i < N; ++i) {
      int l, r;
      cin >> l >> r;
      s ^= Get(Get, l, r);
    }

    cout << (s ? "First" : "Second") << "\n";
  }
}
