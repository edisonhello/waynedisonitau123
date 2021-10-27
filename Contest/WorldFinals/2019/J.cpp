#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> val[505];
vector<pair<int, int>> win_seg;
vector<pair<int, int>> evs;

void go(int ia, int ib) {
  // cerr << "go " << ia << ' ' << ib << endl;
  auto va = val[ia];
  auto vb = val[ib];
  vector<int> allv;
  allv.reserve(va.size() + vb.size());
  for (int i = 0, j = 0; i < va.size() || j < vb.size(); ) {
    if (i == (int)va.size()) {
      allv.push_back(vb[j]);
      ++j;
    } else if (j == (int)vb.size()) {
      allv.push_back(va[i]);
      ++i;
    } else if (va[i] < vb[j]) {
      allv.push_back(va[i]);
      ++i;
    } else if (va[i] > vb[j]) {
      allv.push_back(vb[j]);
      ++j;
    } else {
      allv.push_back(va[i]);
      ++i, ++j;
    }
  }
  allv.resize(unique(allv.begin(), allv.end()) - allv.begin());

  int curh = allv.back(); allv.pop_back();
  int sla = 0, slb = 0;
  ll pa = 0, pb = 0;
  for (int i : va) pa += i;
  for (int i : vb) pb += i;

  auto add_win = [&](int x, int l, int r) {
    if (x == ia) {
      // cerr << "Add win " << x << ' ' << l << ' ' << r << endl;
      win_seg.emplace_back(l, r);
    }
  };

  if (pa > pb) {
    add_win(ia, curh, 1000000000);
  } else if (pa < pb) {
    add_win(ib, curh, 1000000000);
  } else {
    add_win(ia, curh, 1000000000);
    add_win(ib, curh, 1000000000);
  }

  while (allv.size()) {
    while (va.size() && va.back() == curh) va.pop_back(), sla++;
    while (vb.size() && vb.back() == curh) vb.pop_back(), slb++;

    int nowh = allv.back(); allv.pop_back();
    // cerr << "curh = " << curh << endl;
    // cerr << "nowh = " << nowh << endl;

    if (pa > pb && sla > slb) {
      // cerr << "p1" << endl;
      int dsl = sla - slb;
      ll dp = pa - pb;
      ll can_win_more = (dp - 1) / dsl;

      // cerr << "can_win_more = " << can_win_more << endl;

      if (can_win_more > (curh - nowh)) {
        // cerr << "p11" << endl;
        add_win(ia, nowh, curh - 1);
      } else {
        // cerr << "p12" << endl;
        if (can_win_more) {
          // cerr << "p121" << endl;
          add_win(ia, curh - can_win_more, curh - 1);
        }
        if (curh - (can_win_more + 1) >= nowh && pa - (can_win_more + 1) * sla == pb - (can_win_more + 1) * slb) {
          // cerr << "p122" << endl;
          add_win(ia, curh - can_win_more - 1, curh - can_win_more - 1);
        }
        if (nowh <= curh - can_win_more - 1) {
          // cerr << "p123" << endl;
          add_win(ib, nowh, curh - can_win_more - 1);
        }
      }
    } else if (pb > pa && slb > sla) {
      // cerr << "p2" << endl;
      int dsl = slb - sla;
      ll dp = pb - pa;
      ll can_win_more = (dp - 1) / dsl;

      if (can_win_more > (curh - nowh)) {
        // cerr << "p21" << endl;
        add_win(ib, nowh, curh - 1);
      } else {
        // cerr << "p22" << endl;
        if (can_win_more) add_win(ib, curh - can_win_more, curh - 1);
        if (curh - (can_win_more + 1) >= nowh && pa - (can_win_more + 1) * sla == pb - (can_win_more + 1) * slb) {
          add_win(ib, curh - can_win_more - 1, curh - can_win_more - 1);
        }
        if (nowh <= curh - can_win_more - 1)
          add_win(ia, nowh, curh - can_win_more - 1);
      }
    } else if (pa == pb) {
      // cerr << "p3" << endl;
      if (sla > slb) {
        add_win(ib, nowh, curh - 1);
      } else if (slb > sla) {
        add_win(ia, nowh, curh - 1);
      } else {
        add_win(ia, nowh, curh - 1);
        add_win(ib, nowh, curh - 1);
      }
    } else {
      // cerr << "p4" << endl;
      if (pa > pb) add_win(ia, nowh, curh - 1);
      else if (pb > pa) add_win(ib, nowh, curh - 1);
    }

    pa -= 1ll * sla * (curh - nowh);
    pb -= 1ll * slb * (curh - nowh);

    curh = nowh;
  }

  if (curh > 1) {
    if (pa == pb) {
      add_win(ia, 1, curh - 1);
      add_win(ib, 1, curh - 1);
    } else if (pa > pb) {
      add_win(ia, 1, curh - 1);
    } else {
      add_win(ib, 1, curh - 1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    val[i].resize(m);
    for (int j = 0; j < m; ++j) {
      cin >> val[i][j];
    }

    sort(val[i].begin(), val[i].end());
  }

  for (int i = 0; i < n; ++i) {
    win_seg.clear();

    for (int j = 0; j < n; ++j) if (i != j) {
      go(i, j);
    }

    // for (int i = 0; i < n; ++i) {
    //   cerr << "win seg of " << i << endl;
    //   for (auto [s, t] : win_seg[i]) {
    //     cerr << "(" << s << ", " << t << ")" << endl;
    //   }
    // }

    evs.clear();

    int cur = 0;
    for (auto [s, t] : win_seg) {
      if (s == 1) ++cur;
      else evs.emplace_back(s, 1);
      evs.emplace_back(t + 1, -1);
    }

    sort(evs.begin(), evs.end());

    int mn = cur;

    for (int i = 0; i < (int)evs.size(); ++i) {
      cur += evs[i].second;
      while (i + 1 < (int)evs.size() && evs[i + 1].first == evs[i].first) {
        ++i;
        cur += evs[i].second;
      }

      // cerr << "x = " << evs[i].first << " cur " << cur << endl;

      if (evs[i].first <= 1000000000) mn = min(mn, cur);
    }

    cout << mn + 1 << '\n';
  }

}

