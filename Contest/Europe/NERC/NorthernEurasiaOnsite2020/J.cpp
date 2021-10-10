#include <bits/stdc++.h>
using namespace std;

vector<int> get_must(vector<int> v) {
  int one = 0;
  for (int i : v) if (i) ++one;
  // cerr << "one " << one << endl;
  if (!one) return v;

  for (int i = 1; i < v.size(); ++i) {
    if (v[i]) {
      if (v[i - 1]) {
        v[i] = v[i - 1];
      } else {
        v[i] = i;
      }
    }
  }
  int le = 0;
  for (int i = 0; i < v.size(); ++i) if (!v[i]) ++le; else break;
  int ri = 0;
  for (int i = v.size() - 1; i >= 0; --i) if (!v[i]) ++ri; else break;
  vector<int> vl(v.size()), vr(v.size());

  // cerr << "le ri " << le << ' ' << ri << endl;

  for (int i = 0; i < v.size(); ++i) {
    if (i + le >= v.size()) vl[i] = 0;
    else vl[i] = v[i + le];
  }
  for (int i = 0; i < v.size(); ++i) {
    if (i - ri < 0) vr[i] = 0;
    else vr[i] = v[i - ri];
  }

  vector<int> vv(v.size());
  for (int i = 0; i < v.size(); ++i) if (vl[i] && vr[i] && vl[i] == vr[i]) vv[i] = 1;
  return vv;
}

void output(vector<int> v) {
  vector<int> r = {0};
  for (int i : v) {
    if (i) ++r.back();
    else {
      if (r.back()) r.push_back(0);
    }
  }
  if (r.back() == 0) r.pop_back();
  cout << r.size() << endl;
  if (r.size()) {
    for (int i : r) cout << i << ' ';
    cout << endl;
    }
  exit(0);
}

void t0(vector<int> v) {
  // cerr << "v ";
  // for (int i : v) cerr << i << ' ';
  // cerr << endl;
  auto vv = get_must(v);
  // cerr << "vv ";
  // for (int i : vv) cerr << i << ' ';
  // cerr << endl;
  if (vv == v) {
    output(v);
  }
}

void t1(vector<int> v) {
  if (v[0] == 1) return;
  if (v.back() == 1) return;
  v.pop_back();
  for (int i = 0; i < (int)v.size() - 1; ++i) {
    if (v[i + 1]) {
      if (!v[i]) {
        if (i && v[i - 1]) return;
        v[i] |= v[i + 1];
      }
    }
  }
  int le = 0;
  for (int i = 0; i < v.size(); ++i) if (v[i] == 0) ++le; else break;
  int ri = 0;
  for (int i = (int)v.size() - 1; i >= 0; --i) if (v[i] == 0) ++ri; else break;
  if (le & 1) return;
  if (ri & 1) return;
  v[0] = v.back() = 1;
  for (int i = 2; i < (int)v.size() - 1; ++i) {
    if (!v[i] && !v[i - 1]) {
      if (v[i + 1]) return;
      v[i] = 1;
    }
  }
  output(v);
}

void t(vector<int> v, int t) {
  if (v.size() < t) return;
  for (int i = 0; i < t; ++i) if (v[i]) return;
  for (int i = 1; i <= t; ++i) if (v[v.size() - i]) return;
  for (int i = 0; i < t; ++i) v.pop_back();

  for (int _ = 0; _ < t; ++_) {
    for (int i = 0; i < (int)v.size() - 1; ++i) {
      if (v[i + 1] && !v[i]) {
        if (i && v[i - 1]) return;
        v[i] = 1;
      }
    }
  }

  for (int i = 0, j; i < v.size(); i = j) {
    j = i;
    if (v[i]) { j = i + 1; continue; }
    while (j < v.size() && !v[j]) ++j;
    int l = i, r = j - 1;
    int len = r - l + 1;

    if (l == 0) {
      if (len == 1) return;
      if (len & 1) {
        v[0] = v[1] = 1;
        for (int i = 3; i <= r; i += 2) v[i] = 1;
      } else {
        for (int i = l; i <= r; i += 2) v[i] = 1;
      }
    } else if (r == v.size() - 1) {
      if (len == 1) return;
      if (len & 1) {
        v[l + 1] = v[l + 2] = 1;
        for (int i = l + 4; i <= r; i += 2) v[i] = 1;
      } else {
        for (int i = l + 1; i <= r; i += 2) v[i] = 1;
      }
    } else {
      if (len == 1) continue;
      if (len == 2) return;
      if (len & 1) {
        for (int i = l + 1; i <= r; i += 2) v[i] = 1;
      } else {
        v[l + 1] = v[l + 2] = 1;
        for (int i = l + 4; i <= r; i += 2) v[i] = 1;
      }
    }
  }

  output(v);
}

int main() {
  string s; cin >> s;
  vector<int> v;
  for (char c : s) v.push_back(c == '#');

  t0(v);
  t1(v);
  t(v, 2);
  t(v, 3);
  t(v, 4);

  cout << -1 << endl;
}
