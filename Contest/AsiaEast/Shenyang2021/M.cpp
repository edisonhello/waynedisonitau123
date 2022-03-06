#include <bits/stdc++.h>
using namespace std;

vector<int> Build(const string &s) {
  int n = s.size();
  vector<int> str(n * 2), sa(n * 2), c(max(n, 256) * 2), x(max(n, 256)), p(n), q(n * 2), t(n * 2);
  for (int i = 0; i < n; ++i) str[i] = s[i];
  auto Pre = [&](int *sa, int *c, int n, int z) {
    memset(sa, 0, sizeof(int) * n);
    memcpy(x.data(), c, sizeof(int) * z);
  };
  auto Induce = [&](int *sa, int *c, int *s, int *t, int n, int z) {
    memcpy(x.data() + 1, c, sizeof(int) * (z - 1));
    for (int i = 0; i < n; ++i) if (sa[i] && !t[sa[i] - 1]) sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
    memcpy(x.data(), c, sizeof(int) * z);
    for (int i = n - 1; i >= 0; --i) if (sa[i] && t[sa[i] - 1]) sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
  };
  auto SAIS = [&](auto self, int *s, int *sa, int *p, int *q, int *t, int *c, int n, int z) {
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
    Pre(sa, c, n, z);
    for (int i = 1; i <= n - 1; ++i) if (t[i] && !t[i - 1]) sa[--x[s[i]]] = p[q[i] = nn++] = i;
    Induce(sa, c, s, t, n, z);
    for (int i = 0; i < n; ++i) if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
      bool neq = last < 0 || memcmp(s + sa[i], s + last, (p[q[sa[i]] + 1] - sa[i]) * sizeof(int));
      ns[q[last = sa[i]]] = nmxz += neq;
    }
    self(self, ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
    Pre(sa, c, n, z);
    for (int i = nn - 1; i >= 0; --i) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
    Induce(sa, c, s, t, n, z);
  };
  SAIS(SAIS, str.data(), sa.data(), p.data(), q.data(), t.data(), c.data(), n + 1, 256);
  return vector(sa.begin() + 1, sa.begin() + n + 1);
}

int hh[1000006];
int pp[1000006];

const int pm = 7902131;
const int mod = 1000000007;


int gethh(int l, int r) {
  return (hh[r] - (l == 0 ? 0 : hh[l - 1]) * 1ll * pp[r - l + 1] % mod + mod) % mod;
}

vector<int> BuildLCP(const vector<int> &sa, const string &s) {
  int n = s.size();
  vector<int> lcp(n), rev(n);
  for (int i = 0; i < n; ++i) rev[sa[i]] = i;
  for (int i = 0, ptr = 0; i < n; ++i) {
    if (!rev[i]) {
      ptr = 0;
      continue;
    }
    while (i + ptr < n && s[i + ptr] == s[sa[rev[i] - 1] + ptr]) ++ptr;
    lcp[rev[i]] = ptr ? ptr-- : 0;
  }
  return lcp;
}


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  string s; cin >> s;
  int n = s.size();
  auto sa = Build(s);
  auto lcp = BuildLCP(sa, s);

  // for (int i : sa) cout << s.substr(i) << endl;
  // cout << endl;

  int cur = n - 1;
  int nxt = -1;
  int lcpv = -1;

  auto GetNxt = [&] () {
    if (sa[cur] <= 0) { nxt = lcpv = -1; return; }
    lcpv = 1e9;
    nxt = cur;
    while (sa[nxt] >= sa[cur]) {
      lcpv = min(lcpv, lcp[nxt]);
      --nxt;
    }
  };

  GetNxt();

  hh[0] = s[0];
  for (int i = 1 ; i < n; ++i) hh[i] = hh[i - 1] * 1ll * pm % mod;

  vector<pair<int, int>> ans;
  ans.reserve(n);

  for (int i = n - 1; i >= 0; --i) {
    ans.emplace_back(sa[cur], i);

    while (i == sa[cur] + lcpv) {
      cur = nxt;
      GetNxt();
    }
  }

  reverse(ans.begin(), ans.end());

  for (auto [l, r] : ans) {
    cout << l + 1 << ' ' << r + 1 << '\n';
  }

}


