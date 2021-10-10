#include <bits/stdc++.h>
using namespace std;

vector<int> req[500005];

int main() {
  int n; cin >> n;

  map<int, vector<int>> posx;

  map<int, int> loadcnt;

  int tota = 0;

  for (int i = 1; i <= n; ++i) {
    int k; cin >> k;
    tota += k;
    while (k--) {
      int t; cin >> t;
      if (req[i].size() && t == req[i].back()) {
        --tota;
        continue;
      }

      loadcnt[t]++;

      if (req[i].size()) {
        posx[t - req[i].back() + 1].push_back(t);
      }

      req[i].push_back(t);
    }
  }

  int a; cin >> a;
  vector<int64_t> b(n + 5);
  for (int i = 1; i <= n; ++i) cin >> b[i], b[i] *= i;

  int64_t mincost = LLONG_MAX;
  vector<int> ansx;
  auto AddAns = [&] (int x, int64_t cost) {
    if (cost < mincost) {
      mincost = cost;
      ansx = vector{x};
    } else if (cost == mincost) ansx.push_back(x);
  };

  int nowX = 1;
  int64_t cost = tota * 1ll * a;
  for (auto [t, cnt] : loadcnt) {
    cost += b[cnt];
    // cerr << "load cnt " << t << ' ' << cnt << " add " << b[cnt] << endl;
  }

  // cerr << "X = 1 cost " << cost << endl;

  AddAns(nowX, cost);

  for (auto [newX, reqlist] : posx) {
    // cerr << "new X " << newX << endl;

    // int64_t storecost = tota * 1ll * a * (newX - nowX);
    cost += tota * 1ll * a * (newX - nowX - 1) + (tota - reqlist.size()) * 1ll * a;
    tota -= reqlist.size();
    // cerr << "storecost add " << storecost << endl;

    for (auto t : reqlist) {
      // cerr << "loadcost -= " << b[loadcnt[t]] - b[loadcnt[t] - 1] << endl;
      cost -= b[loadcnt[t]];
      loadcnt[t]--;
      cost += b[loadcnt[t]];
    }

    // cerr << "cost = " << cost << endl;

    AddAns(newX, cost);
    nowX = newX;

  }

  sort(ansx.begin(), ansx.end());
  cout << mincost << ' ' << ansx.size() << endl;
  for (int i : ansx) cout << i << ' ';
  cout << endl;


}
