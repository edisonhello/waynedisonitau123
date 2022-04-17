#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define int int64_t

double len(pair<int, int> p) {
  return hypot(p.first, p.second);
}

template <typename T>
tuple<T, T, T> extgcd(T a, T b) {
  if (!b) return make_tuple(a, 1, 0);
  auto [d, x, y] = extgcd(b, a % b);
  return make_tuple(d, y, x - (a / b) * y);
}

vector<pair<int, int>> Simp(vector<pair<int, int>> orig) {
  auto [x, y, z] = [&]() {
    int a1 = orig[0].first;
    int b1 = orig[1].first;
    int c1 = orig[2].first;
    int a2 = orig[0].second;
    int b2 = orig[1].second;
    int c2 = orig[2].second;

    // cout << "a b c 1 " << a1 << ' ' << b1 << ' '<< c1 << endl;
    // cout << "a b c 2 " << a2 << ' ' << b2 << ' '<< c2 << endl;

    if (b2 * c1 == b1 * c2) {
      if (b2 * c1 == 0) {
        if (b1 && c1) {
          int g = __gcd(c1, b1);
          return make_tuple((int)0, c1 / g, -b1 / g);
        } else if (b2 && c2) {
          int g = __gcd(c2, b2);
          return make_tuple((int)0, c2 / g, -b2 / g);
        } else if (c1 == 0 && c2 == 0) {
          return make_tuple((int)0, (int)0, (int)1);
        } else if (b1 == 0 && b2 == 0) {
          return make_tuple((int)0, (int)1, (int)0);
        } else assert(0);
      }
      int g = __gcd(c1, b1);
      return make_tuple((int)0, c1 / g, -b1 / g);
    }

    int d = b1 * c2 - b2 * c1;
    int yu = -a1 * c2 + a2 * c1;
    int zu = b1 * (-a2) - b2 * (-a1);
    int x = d;
    int y = yu;
    int z = zu;

    // if (c1 && c2) {
    //   int oc1 = c1, oc2 = c2;
    //   a1 *= oc2;
    //   b1 *= oc2;
    //   c1 *= oc2;
    //   a2 *= oc1;
    //   b2 *= oc1;
    //   c2 *= oc1;
    // } else {
    //   assert(b1 && b2);
    //   int ob1 = b1, ob2 = b2;
    //   a1 *= ob2;
    //   b1 *= ob2;
    //   c1 *= ob2;
    //   a2 *= ob1;
    //   b2 *= ob1;
    //   c2 *= ob1;
    // }

    // int yu = -(a2 - a1);
    // int yd = b2 - b1;
    // int zu = -(a1 * yd + b1 * yu);
    // int zd = yd * c1;
    // cout << "yu yd zu zd " << yu << ' ' << yd << ' ' << zu << ' ' << zd << endl;

    // int x = yd * zd;
    // int y = yu * zd;
    // int z = zu * yd;
    int g = __gcd(__gcd(x, y), z);
    // cout << "x y z g " << x << ' ' << y << ' ' << z << ' ' << g << endl;
    x /= g;
    y /= g;
    z /= g;
    // cerr << "x y z " << x << ' ' << y << ' ' << z << endl;
    return make_tuple(x, y, z);
  }();

  while (abs(__gcd(x, z)) != 1) {
    /// cout << "x y z " << x << ' ' << y << ' ' << z << endl;
    x += y;
    orig[1].first -= orig[0].first;
    orig[1].second -= orig[0].second;
  }

  // auto [a, b, c] = [&]() {
  //   int d = __gcd(x, y);
  //   auto [_, aa, c] = extgcd(d, z);
  //   auto [__, a, b] = extgcd(x, y);
  //   a *= aa;
  //   b *= aa;
  //   cerr << "a b c " << a << ' ' << b << ' ' << c << endl;
  //   return make_tuple(a, b, c);
  // }();
  auto [a, b] = [&]() {
    auto [_, a, b] = extgcd(x, z);
    return make_tuple(a, b);
  }();

  pair<int, int> u = orig[1];
  pair<int, int> v(b * orig[0].first + 0 + -a * orig[2].first,
      b * orig[0].second + 0 + -a * orig[2].second);

  if (len(u) < len(v)) swap(u, v);
  while (len(v) < len(u)) {
    double lv = len(v) * len(v);
    double vx = v.first / lv;
    double vy = v.second / lv;
    int t = floor(u.first * vx + u.second * vy);
    pair<int, int> nv(u.first - t * v.first, u.second - t * v.second);
    u = v;
    v = nv;
  }

  return vector<pair<int, int>>{u, v};
}

int CanGo(vector<pair<int, int>> go, pair<int, int> to) {
  if (go.empty()) return false;
  if (go.size() == 1u) {
    if (go[0].first == 0) {
      if (to.first) return false;
      if (to.second % go[0].second) return false;
      return true;
    }
    if (go[0].second == 0) {
      if (to.second) return false;
      if (to.first % go[0].first) return false;
      return true;
    }
    if (to.first % go[0].first) return false;
    if (to.second % go[0].second) return false;
    if (to.first / go[0].first != to.second / go[0].second) return false;
    return true;
  }

  int d = go[0].first * go[1].second - go[0].second * go[1].first;
  int au = to.first * go[1].second - to.second * go[1].first;
  int bu = go[0].first * to.second - go[0].second * to.first;

  if (d == 0) return false;
  if (au % d || bu % d) return false;
  return true;
}

int64_t solve() {
  vector<pair<int, int>> go;
  int64_t rew = 0;
  int q;
  cin >> q;
  int dim = 0;
  while (q--) {
    int c;
    cin >> c;
    if (c == 1) {
      int x, y;
      cin >> x >> y;
      if (x == 0 && y == 0) continue;

      if (dim == 1) {
        if (go[0].first * y == go[0].second * x) {
          int xx = __gcd(go[0].first, x);
          int t = x / xx;
          go[0].first /= t;
          go[0].second /= t;
        } else {
          dim = 2;
          go.emplace_back(x, y);
        }
      } else if (dim == 0 || dim == 2) {
        go.emplace_back(x, y);
        if (dim == 0) dim = 1;
        if (go.size() > 2u) go = Simp(go);
      }
    } else if (c == 2) {
      int x, y, r;
      cin >> x >> y >> r;
      if (CanGo(go, make_pair(x, y))) rew += r;
    }
  }
  return rew;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": " << solve() << '\n';
  }
}

