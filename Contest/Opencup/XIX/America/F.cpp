#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw(int b, int n) {
  int a = 1;
  while (n) {
    if (n & 1) a = 1ll * a * b % mod;
    b = 1ll * b * b % mod;
    n >>= 1;
  }
  return a;
}

int inv(int x) {
  return pw(x, mod - 2);
}

int b[305], p[305];
vector<int> g[305];

struct Poly {
  vector<int> poly;

  Poly() = default;
  Poly(int v) {
    poly.resize(1);
    poly[0] = v;
  }
  Poly(vector<int> v) {
    poly = v;
  }

  Poly get_integral() const {
    vector<int> tmp(poly.size() + 1);
    for (int i = 0; i < (int)poly.size(); ++i) {
      tmp[i + 1] = 1ll * poly[i] * inv(i + 1) % mod;
    }
    return Poly(tmp);
  }

  int fill(int base) {
    int res = 0;
    int x = 1;
    for (int i = 0; i < (int)poly.size(); ++i) {
      res = (res + 1ll * poly[i] * x) % mod;
      x = 1ll * x * base % mod;
    }
    return res;
  }

  Poly operator-(const Poly p) const {
    vector<int> v(max(poly.size(), p.poly.size()));

    for (int i = 0; i < (int)v.size(); ++i) {
      v[i] = (i < (int)poly.size() ? poly[i] : 0) - (i < (int)p.poly.size() ? p.poly[i] : 0);
      if (v[i] < 0) v[i] += mod;
    }

    return Poly(v);
  }

  Poly& operator*=(const Poly p) {
    vector<int> tmp(p.poly.size() + poly.size() - 1);
    for (int i = 0; i < (int)poly.size(); ++i) {
      for (int j = 0; j < (int)p.poly.size(); ++j) {
        tmp[i + j] = (tmp[i + j] + 1ll * poly[i] * p.poly[j]) % mod;
      }
    }
    poly.swap(tmp);
    return *this;
  }

  Poly& operator/=(int b) {
    b = inv(b);
    // cerr << "b = " << b << endl;
    for (int &i : poly) {
      // cerr << "i = " << i << endl;
      i = 1ll * i * b % mod;
      // cerr << "i = " << i << endl;
    }
    return *this;
  }
};

ostream& operator<< (ostream &o, Poly p) {
  for (int i : p.poly) o << i << " ";
  return o;
}

pair<int, Poly> dfs(int now) {
  Poly res(1);
  int mxx = b[now];

  vector<pair<int, Poly>> chs;

  for (int i : g[now]) {
    auto tmp = dfs(i);
    chs.push_back(tmp);
  }

  sort(chs.begin(), chs.end(), [&](auto &a, auto &b) { return a.first < b.first; });

  if (chs.empty()) {
    return make_pair(mxx, vector<int>(1, inv(mxx)));
  }

  int x0 = chs[0].first;

  for (auto [xx, pol] : chs) {
    // cerr << "pol from chs " << pol << endl;
    auto itg = pol.get_integral();
    // cerr << "itg = " << itg << endl;
    // cerr << "fill " << x0 << " = " << itg.fill(x0) << endl;
    auto tmp = Poly(itg.fill(xx)) - itg;
    // cerr << "tmp = " << tmp << endl;
    res *= tmp;
    // cerr << "res = " << res << endl;
  }

  res /= b[now];

  // cerr << "now = " << now << endl;
  // cerr << "res = " << res << endl;


  return make_pair(min(b[now], x0), res);
}

int main() {
  int n; 
  cin >> n;

  int root = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> b[i] >> p[i];
    if (!p[i]) root = i;
    g[p[i]].push_back(i);
  }

  auto p = dfs(root);

  int ans = p.second.get_integral().fill(p.first);
  cout << ans << endl;
}
