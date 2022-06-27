#include <bits/stdc++.h>
using namespace std;


int main() {
  int n; cin >> n;
  vector<int> h(n);
  for (int i = 0; i < n; ++i) cin >> h[i];
  
  set<tuple<int, int, int>> segs;
  for (int i = 0, j; i < n; i = j) {
    for (j = i; j < n && (h[i] & 1) == (h[j] & 1); ++j);
    int mx = 0;
    for (int k = i; k < j; ++k) mx = max(mx, h[k]);
    segs.insert(make_tuple(i, j - 1, mx));
  }

  // [hei, l]
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  for (auto [l, r, h] : segs) {
    // cout << "segs : " << l << ' ' << r << ' ' << h << endl;
    if ((r - l + 1) % 2 == 0) {
      pq.emplace(h, l);
      // cout << "in pq " << h << ' ' << l << endl;
    }
  }

  while (pq.size() && segs.size() > 1u) {
    auto [hei, l] = pq.top();
    pq.pop();

    // cout << "pq top hei l " << hei << ' ' << l << endl;

    auto it = segs.lower_bound(make_tuple(l, -1, -1));
    if (it == segs.end()) continue;
    if (get<0>(*it) != l) continue;
    if (get<2>(*it) != hei) continue;

    int r = get<1>(*it);

    if ((r - l + 1) % 2 == 1) continue;

    // cout << "r = " << r << endl;

    auto prv = segs.find(make_tuple(l, r, hei));
    assert(prv != segs.end());
    auto nxt = prv;

    auto now = *prv;

    if (prv != segs.begin()) --prv;
    if (next(nxt) != segs.end()) ++nxt;

    auto _prv = *prv, _nxt = *nxt;

    auto [ll, lr, lh] = _prv;
    auto [rl, rr, rh] = _nxt;
    auto newl = ll;
    auto newr = rr;
    int newh = hei;
    
    if (lh < hei) lh += hei - lh + 1;
    if (rh < hei) rh += hei - rh + 1;
    newh = max(max(lh, rh), hei);

    segs.erase(now);
    segs.erase(_prv);
    segs.erase(_nxt);
    segs.insert(make_tuple(newl, newr, newh));

    if ((newr - newl + 1) % 2 == 0) {
      pq.emplace(newh, newl);
    }
  }

  if (segs.size() == 1) {
    cout << get<2>(*segs.begin()) << endl;
  } else {
    cout << -1 << endl;
  }
}

