#include <bits/stdc++.h>
using namespace std;


const int maxn = 350005;
bool t[maxn * 2];
int hi[maxn], rev[maxn];
int _s[maxn * 2], sa[maxn * 2], c[maxn * 2], x[maxn], p[maxn], q[maxn * 2];

void pre(int *sa, int *c, int n, int z) {
  memset(sa, 0, sizeof(int) * n);
  memcpy(x, c, sizeof(int) * z);
}

void induce(int *sa, int *c, int *s, bool *t, int n, int z) {
  memcpy(x + 1, c, sizeof(int) * (z - 1));
  for (int i = 0; i < n; ++i) if (sa[i] && !t[sa[i] - 1]) sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
  memcpy(x, c, sizeof(int) * z);
  for (int i = n - 1; i >= 0; --i) if (sa[i] && t[sa[i] - 1]) sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
}

void sais(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z) {
  bool uniq = t[n - 1] = true;
  int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, last = -1;
  memset(c, 0, sizeof(int) * z);
  for (int i = 0; i < n; ++i) uniq &= ++c[s[i]] < 2;
  for (int i = 0; i < z - 1; ++i) c[i + 1] += c[i];
  if (uniq) {
    for (int i = 0; i < n; ++i) sa[--c[s[i]]] = i;
    return;
  }
  for (int i = n - 2; i >= 0; --i) t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
  pre(sa, c, n, z);
  for (int i = 1; i <= n - 1; ++i) if (t[i] && !t[i - 1]) sa[--x[s[i]]] = p[q[i] = nn++] = i;
  induce(sa, c, s, t, n, z);
  for (int i = 0; i < n; ++i) if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
    bool neq = last < 0 || memcmp(s + sa[i], s + last, (p[q[sa[i]] + 1] - sa[i]) * sizeof(int));
    ns[q[last = sa[i]]] = nmxz += neq;
  }
  sais(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
  pre(sa, c, n, z);
  for (int i = nn - 1; i >= 0; --i) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
  induce(sa, c, s, t, n, z);
}

void build(const string &s) {
  for (int i = 0; i < (int)s.size(); ++i) _s[i] = s[i];
  _s[(int)s.size()] = 0;
  sais(_s, sa, p, q, t, c, (int)s.size() + 1, 256);
  for (int i = 0; i < (int)s.size(); ++i) sa[i] = sa[i + 1];
  for (int i = 0; i < (int)s.size(); ++i) rev[sa[i]] = i;
  int ind = 0;
  hi[0] = 0;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (!rev[i]) {
      ind = 0;
      continue;
    }
    while (i + ind < (int)s.size() && s[i + ind] == s[sa[rev[i] - 1] + ind]) ++ind;
    hi[rev[i]] = ind ? ind-- : 0;
  }
}

int tag[maxn];
int prv[maxn], nxt[maxn];
int st[20][maxn];

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  int fi = s.size();
  for (int i = 2; i <= n; ++i) {
    s += char('z' + 1);
    string t; cin >> t;
    s += t;
  }

  // cout << "s = " << s << endl;

  build(s);
  int pos = -1, len = -1;

  // cout << "sa = ";
  // for (int i = 0; i < (int)s.size(); ++i) cout << sa[i] << ' ';
  // cout << endl;

  // cout << "hi = ";
  // for (int i = 0; i < (int)s.size(); ++i) cout << hi[i] << ' ';
  // cout << endl;

  for (int i = 0; i < (int)s.size(); ++i) st[0][i] = hi[i];
  for (int z = 1; z < 20; ++z) {
    for (int i = 0; i + (1 << z) - 1 < (int)s.size(); ++i) {
      st[z][i] = min(st[z - 1][i], st[z - 1][i + (1 << (z - 1))]);
    }
  }

  auto LCP = [&] (int l, int r) {
    assert(l < r);
    ++l;
    int z = 31 - __builtin_clz(r - l + 1);
    // cerr << "Q " << l << ' ' << r << endl;
    return min(st[z][l], st[z][r + 1 - (1 << z)]);
  };


  for (int i = 0; i < (int)s.size(); ++i) tag[i] = sa[i] >= fi;
  prv[0] = -1;
  for (int i = 1; i < (int)s.size(); ++i) {
    if (tag[i - 1]) prv[i] = i - 1;
    else prv[i] = prv[i - 1];
  }
  nxt[(int)s.size() - 1] = -1;
  for (int i = (int)s.size() - 2; i >= 0; --i) {
    if (tag[i + 1]) nxt[i] = i + 1;
    else nxt[i] = nxt[i + 1];
  }

  for (int i = 0; i < (int)s.size(); ++i) {
    if (s[i] == '{') break;
    int mx = -1;
    // cerr << "rev prv nxt " << rev[i] << ' ' << prv[rev[i]] << ' ' << nxt[rev[i]] << endl;
    if (prv[rev[i]] != -1) mx = max(mx, LCP(prv[rev[i]], rev[i]) + 1);
    if (nxt[rev[i]] != -1) mx = max(mx, LCP(rev[i], nxt[rev[i]]) + 1);
    assert(mx != -1);
    // cerr << "i mx " << i << ' ' << mx << endl;
    if (i + mx > fi) continue;
    if (pos == -1) {
      pos = i; len = mx;
    } else if (mx < len) {
      pos = i; len = mx;
    } else if (mx == len && rev[i] < rev[pos]) {
      pos = i; len = mx;
    }
  }

  if (len == -1 || len > fi) {
    cout << "Impossible" << endl;
    return;
  }

  for (int i = 0; i < len; ++i) cout << s[pos + i];
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": ";
    solve();
  }
}
