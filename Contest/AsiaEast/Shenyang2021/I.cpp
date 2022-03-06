#include <bits/stdc++.h>
using namespace std;

struct C {
  int64_t r, i;
  C() = default;
  C(int64_t a, int64_t b) : r(a), i(b) {}
  C operator-(const C &b) const { return C{r - b.r, i - b.i}; }
  C operator*(const C &b) const { return C{r * b.r - i * b.i, r * b.i + i * b.r}; }
  C Rev() const { return C{r, -i}; }
};

istream& operator>>(istream &i, C &c) {
  return i >> c.r >> c.i;
}

void solve() {
  C z0, z1, z2, z3, w1, w2, w3;
  cin >> z1 >> w1 >> z2 >> w2 >> z3 >> w3 >> z0;
  C x = (z1 - z2) * (z3 - z0) * (w1 - w3);
  C y = (z1 - z3) * (z2 - z0) * (w1 - w2);
  C u = (x * w2 - y * w3);
  C d = (x - y);
  C res = u * d.Rev();
  int64_t div = d.r * 1ll * d.r + d.i * 1ll * d.i;
  cout << fixed << setprecision(12) << (double)res.r / div << ' ' << (double)res.i / div << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) solve();
}

