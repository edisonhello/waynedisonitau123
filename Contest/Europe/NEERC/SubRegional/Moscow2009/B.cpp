#include <bits/stdc++.h>
using namespace std;

namespace sfx {

constexpr int kN = 200'000 + 5;
bool t[kN * 2];
int s[kN * 2], sa[kN * 2], c[kN * 2], x[kN], p[kN], q[kN * 2];

void Pre(int *sa, int *c, int n, int z) {
  memset(sa, 0, sizeof(int) * n);
  memcpy(x, c, sizeof(int) * z);
}

void Induce(int *sa, int *c, int *s, bool *t, int n, int z) {
  memcpy(x + 1, c, sizeof(int) * (z - 1));
  for (int i = 0; i < n; ++i) {
    if (sa[i] && !t[sa[i] - 1]) {
      sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
    }
  }
  memcpy(x, c, sizeof(int) * z);
  for (int i = n - 1; i >= 0; --i) {
    if (sa[i] && t[sa[i] - 1]) {
      sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
    }
  }
}

void SAIS(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z) {
  bool uniq = t[n - 1] = true;
  int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, last = -1;
  memset(c, 0, sizeof(int) * z);
  for (int i = 0; i < n; ++i) {
    uniq &= ++c[s[i]] < 2;
  }
  for (int i = 0; i < z - 1; ++i) {
    c[i + 1] += c[i];
  }
  if (uniq) {
    for (int i = 0; i < n; ++i) {
      sa[--c[s[i]]] = i;
    }
    return;
  }
  for (int i = n - 2; i >= 0; --i) {
    t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
  }
  Pre(sa, c, n, z);
  for (int i = 1; i <= n - 1; ++i) {
    if (t[i] && !t[i - 1]) {
      sa[--x[s[i]]] = p[q[i] = nn++] = i;
    }
  }
  Induce(sa, c, s, t, n, z);
  for (int i = 0; i < n; ++i) {
    if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
      bool neq = last < 0 || memcmp(s + sa[i], s + last, (p[q[sa[i]] + 1] - sa[i]) * sizeof(int));
      ns[q[last = sa[i]]] = nmxz += neq;
    }
  }
  SAIS(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
  Pre(sa, c, n, z);
  for (int i = nn - 1; i >= 0; --i) {
    sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
  }
  Induce(sa, c, s, t, n, z);
}

vector<int> Build(const string &x) {
  int n = x.size();
  for (int i = 0; i < n; ++i) {
    s[i] = x[i];
  }
  s[n] = 0;
  SAIS(s, sa, p, q, t, c, n + 1, 256);
  return vector<int>(sa + 1, sa + n + 1);
}

vector<int> BuildLCP(const vector<int> &sa, const string &s) {
  int n = s.size();
  vector<int> rev(n);
  for (int i = 0; i < n; ++i) {
    rev[sa[i]] = i;
  }
  int ptr = 0;
  vector<int> res(n);
  for (int i = 0; i < n; ++i) {
    if (!rev[i]) {
      ptr = 0;
      continue;
    }
    while (i + ptr < n && s[i + ptr] == s[sa[rev[i] - 1] + ptr]) ptr++;
    res[rev[i]] = ptr ? ptr-- : 0;
  }
  return res;
}

}  // namespace sfx

int Solve(string s, string t) {
  int n = s.size();
  string x = s + '#' + t;
  vector<int> sa = sfx::Build(x);
  vector<int> lcp = sfx::BuildLCP(sa, x);
  vector<int> ord(n + n);
  iota(ord.begin(), ord.end(), 1);
  sort(ord.begin(), ord.end(), [&](int i, int j) { return lcp[i] > lcp[j]; });
  const int m = n + n + 1;
  vector<int> uf(m);
  iota(uf.begin(), uf.end(), 0);

  vector<int> up(m, n), down(m, -n);
  for (int i = 0; i < m; ++i) {
    if (sa[i] < n) {
      up[i] = sa[i];
    }
    if (sa[i] > n) {
      down[i] = sa[i] - n - 1;
    }
  }
  int res = n;

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  auto Merge = [&](int x, int y, int z) {
    x = Find(x);
    y = Find(y);
    assert(x != y);
    res = min(res, n + n - z - z + up[x] - down[y]);
    res = min(res, n + n - z - z + up[y] - down[x]);
    up[y] = min(up[y], up[x]);
    down[y] = max(down[y], down[x]);
    uf[x] = y;
  };

  for (int i = 0; i < ord.size(); ++i) {
    Merge(ord[i] - 1, ord[i], lcp[ord[i]]);
  }
  return res;
}

int main() {
  freopen("blackboard.in", "r", stdin);
  freopen("blackboard.out", "w", stdout);
  string s, t;
  cin >> s >> t;
  int res = Solve(s, t);
  reverse(s.begin(), s.end());
  reverse(t.begin(), t.end());
  res = min(res, Solve(s, t));
  cout << res << "\n";
}
