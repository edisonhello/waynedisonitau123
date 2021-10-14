#include <bits/stdc++.h>
using namespace std;

struct P {
  int x, y, z;

  P operator- (const P b) { return P{x - b.x, y - b.y, z - b.z}; }
  int norm2() { return x * x + y * y + z * z; }
};

int main() {
  int t; cin >> t; while (t--) {
    vector<P> ps;
    for (int i = 0; i < 8; ++i) {
      int x, y, z; cin >> x >> y >> z;
      ps.emplace_back(P{x, y, z});
    }

    vector<int> d;
    for (int i = 0; i < 8; ++i) {
      for (int j = i + 1; j < 8; ++j) {
        d.push_back((ps[i] - ps[j]).norm2());
      }
    }

    sort(d.begin(), d.end());

    if (d[0] && 
        d[0] == d[11] && 
        d[0] * 2 == d[12] &&
        d[12] == d[23] && 
        d[0] * 3 == d[24] &&
        d[24] == d[27]) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
}
