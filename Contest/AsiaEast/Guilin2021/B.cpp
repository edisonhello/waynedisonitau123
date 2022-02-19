#include <bits/stdc++.h>
using namespace std;


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, q; cin >> n >> q;

  string s, t; cin >> s >> t;

  reverse(s.begin(), s.end());
  reverse(t.begin(), t.end());

  vector<int> vs, vt, va;

  for (int i = 0; i < n; ++i) vs.push_back(s[i] & 15);
  for (int i = 0; i < n; ++i) vt.push_back(t[i] & 15);
  for (int i = 0; i < n; ++i) va.push_back(vs[i] + vt[i]);
  for (int i = 0; i < n; ++i) {
    if (i < n - 1) va[i + 1] += va[i] / 10;
    va[i] %= 10;
  }

  map<int, int> cont;
  for (int i = 0, j; i < n; i = j) {
    for (j = i; j < n && va[i] == va[j]; ++j);
    cont[i] = va[i];
  }

  auto PrintCont = [&]() {
    // for (auto it = cont.rbegin(); it != cont.rend(); ++it) {
    //   cerr << "(" << it->first << ' ' << it->second << ") ";
    // }
    // cerr << endl;
  };

  auto Query = [&](int x) -> int {
    auto it = cont.upper_bound(x);
    return prev(it)->second;
  };

  auto GetLen = [&](int pos) -> int {
    auto it = cont.lower_bound(pos);
    return next(it) == cont.end() ? n - pos : next(it)->first - pos;
  };

  auto Split = [&](int pos) -> void {
    auto it = prev(cont.upper_bound(pos));
    if (it->first != pos) {
      cont[pos] = it->second;
      it = next(it);
    } 
    if ((next(it) != cont.end() && next(it)->first != pos + 1) || (next(it) == cont.end() && pos != n - 1)) {
      cont[pos + 1] = it->second;
    }
  };

  auto Maintain = [&](int pos) -> void {
    auto it = cont.lower_bound(pos);
    if (it != cont.begin() && it->second == prev(it)->second) {
      cont.erase(it);
      it = prev(cont.lower_bound(pos));
    }

    for (int i = 0; i < 8; ++i) {
      if (next(it) == cont.end()) break;
      if (next(it)->second == it->second) {
        cont.erase(next(it));
      } else {
        it = next(it);
      }
    }
  };

  auto Add = [&](int pos, int val) -> int {
    Split(pos);
    int &ref = cont[pos];
    ref += val;
    int chg = 1;
    if (ref > 9) {
      ref -= 10;
      auto nx = cont.lower_bound(pos + 1);
      if (nx != cont.end()) {
        if (nx->second == 9) {
          nx->second = 0;
          chg += GetLen(nx->first);
          if (next(nx) != cont.end()) {
            int ppos = next(nx)->first;
            Split(ppos);
            cont[ppos]++;
            chg += 1;
          }
        } else {
          Split(pos + 1);
          ++cont[pos + 1];
          ++chg;
        }
      }
    }
    Maintain(pos);
    return chg;
  };

  auto Sub = [&](int pos, int val) -> int {
    Split(pos);
    int &ref = cont[pos];
    ref -= val;
    int chg = 1;
    if (ref < 0) {
      ref += 10;
      auto nx = cont.lower_bound(pos + 1);
      if (nx != cont.end()) {
        if (nx->second == 0) {
          nx->second = 9;
          chg += GetLen(nx->first);
          if (next(nx) != cont.end()) {
            int ppos = next(nx)->first;
            Split(ppos);
            cont[ppos]--;
            chg += 1;
          }
        } else {
          Split(pos + 1);
          --cont[pos + 1];
          ++chg;
        }
      }
    }
    Maintain(pos);
    return chg;
  };

  PrintCont();

  for (int i = 0; i < q; ++i) {
    int r, c, d;
    cin >> r >> c >> d;
    c = n - c;
    int ch = 0;
    int chg = 0;
    if (r == 1) {
      int o = vs[c];
      vs[c] = d;
      
      ch = d - o;
    } else if (r == 2) {
      int o = vt[c];
      vt[c] = d;
      
      ch = d - o;
    }

    if (ch > 0) chg = Add(c, ch);
    if (ch < 0) chg = Sub(c, -ch);

    int v = Query(c);

    cout << v << ' ' << chg + (ch != 0) << '\n';

    PrintCont();
  }

}

