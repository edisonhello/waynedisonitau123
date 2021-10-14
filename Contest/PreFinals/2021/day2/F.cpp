#include <bits/stdc++.h>
using namespace std;
#define ll int64_t
#define sq(x) ((x) * (x))

struct cpl {
  ll x, y; // x + yi

  cpl operator+ (ll b) { return cpl{x + b, y}; }
  cpl operator- (ll b) { return cpl{x - b, y}; }
  cpl operator* (cpl b) { return cpl{x * b.x - y * b.y, x * b.y + y * b.x}; }
  cpl operator/ (ll b) { return cpl{x / b, y / b}; }

  cpl conj() { return cpl{x, -y}; }

  bool divable(cpl w) {
    cpl u = *this * w.conj();
    ll btm = sq(w.x) + sq(w.y);
    return u.x % btm == 0 && u.y % btm == 0;
  }

  cpl operator/ (cpl w) {
    cpl u = *this * w.conj();
    ll btm = sq(w.x) + sq(w.y);
    return u / btm;
  }

  bool operator< (const cpl b) const { return x == b.x ? y < b.y : x < b.x; }
};

vector<int> tak;
set<cpl> appear;
bool nosol;

void go(cpl tar, cpl w, int dt) {
  if (tar.x == 0 && tar.y == 0) return; 
  if (appear.count(tar)) {
    nosol = 1;
    return;
  }
  appear.insert(tar);

  if (tar.divable(w)) {
    cpl z = tar / w;
    go(z, w, dt + 1);
  } else {
    tar = tar - 1;
    if (!tar.divable(w)) {
      nosol = 1;
      return;
    }
    tak.push_back(dt);
    cpl z = tar / w;
    go(z, w, dt + 1);
  }
}

vector<int> solve(ll a, ll b, ll x, ll y) {
  cpl tar{x, y};
  cpl w{a, b};

  nosol = 0;
  tak.clear();
  appear.clear();

  go(tar, w, 0);

  return tak;
}

int main() {
  ll a, b, x, y; 
  while (cin >> a >> b >> x >> y) {
    if ((a | b | x | y) == 0) break;
    auto res = solve(a, b, x, y);
    if (nosol) {
      cout << -1 << '\n';
      continue;
    } else {
      cout << res.size() << '\n';
      sort(res.begin(), res.end());
      for (int i : res) {
        cout << i + 1 << '\n';
      }
    }
  }
}
