#include <bits/stdc++.h>
using namespace std;

struct P {
  int x, y;
  void norm() {
    if (!x) y = y > 0 ? 1 : -1;
    else if (!y) x = x > 0 ? 1 : -1;
    else {
      int g = __gcd(x, y);
      g = abs(g);
      x /= g;
      y /= g;
    }
  }

  void spin() {
    swap(x, y);
    x = -x;
  }

  P operator- (const P b) { return P{x - b.x, y - b.y}; }

  bool operator< (const P &b) const { return x == b.x ? y < b.y : x < b.x; }
};

P ps[2005];
vector<P> edg[2005];

int getcount(vector<P> &v, P &t) {
  return upper_bound(v.begin(), v.end(), t) - lower_bound(v.begin(), v.end(), t);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int n, q; 
  cin >> n >> q;

  for (int i = 1; i <= n; ++i) cin >> ps[i].x >> ps[i].y;

  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      P d = ps[i] - ps[j];
      d.norm();
      edg[j].push_back(d);
      d = ps[j] - ps[i];
      d.norm();
      edg[i].push_back(d);
    }
  }

  for (int i = 1; i <= n; ++i) sort(edg[i].begin(), edg[i].end());

  // for (auto p : edg[1]) {
  //   cerr << "edg[1] inc " << p.first.x << ' ' << p.first.y << " has " << p.second << endl;
  // }

  vector<P> to;
  while (q--) {
    P pq;
    cin >> pq.x >> pq.y;

    to.clear();
    for (int i = 1; i <= n; ++i) {
      P d = ps[i] - pq;
      d.norm();
      to.push_back(d);
    }

    sort(to.begin(), to.end());

    int ans = 0;
    for (auto d : to) {
      d.spin();
      ans += getcount(to, d);
    }

    for (int i = 1; i <= n; ++i) {
      P dd = pq - ps[i];
      dd.norm();
      dd.spin();

      // cerr << "i = " << i << " try dd = " << dd.x << ' ' << dd.y << endl;

      ans += getcount(edg[i], dd);

      dd.spin();
      dd.spin();

      // cerr << "i = " << i << " try dd = " << dd.x << ' ' << dd.y << endl;

      ans += getcount(edg[i], dd);
    }

    cout << ans << '\n';
  }
}
