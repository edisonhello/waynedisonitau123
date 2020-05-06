#include <bits/stdc++.h>
using namespace std;


namespace sfx {
    constexpr int kN = 2'000'000 + 5;
    bool t[kN * 2];
    int _s[kN * 2], sa[kN * 2], c[kN * 2], x[kN], p[kN], q[kN * 2];

    void Pre(int *sa, int *c, int n, int z) {
        memset(sa, 0, sizeof(int) * n);
        memcpy(x, c, sizeof(int) * z);
    }

    void Induce(int *sa, int *c, int *s, bool *t, int n, int z) {
        memcpy(x + 1, c, sizeof(int) * (z - 1));
        for (int i = 0; i < n; ++i) {
            if (sa[i] && !t[sa[i] - 1]) sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
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
        for (int i = 0; i < n; ++i) uniq &= ++c[s[i]] < 2;
        for (int i = 0; i < z - 1; ++i) c[i + 1] += c[i];
        if (uniq) {
            for (int i = 0; i < n; ++i) sa[--c[s[i]]] = i;
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
        for (int i = nn - 1; i >= 0; --i) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
        Induce(sa, c, s, t, n, z);
    }

    vector<int> Build(const string &s) {
        int n = s.size();
        for (int i = 0; i < n; ++i) _s[i] = s[i];
        _s[n] = 0;
        SAIS(_s, sa, p, q, t, c, n + 1, 256);
        return vector<int>(sa + 1, sa + n + 1);
    }
}  // namespace sfx

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s, t;
    cin >> s >> t;
    string g = s + "#" + t;
    int m = g.size();
    auto sa = sfx::Build(g);
    vector<int> rev(m);
    for (int i = 0; i < m; ++i) {
        rev[sa[i]] = i;
    }
    vector<int> hei(m);
    for (int i = 0, ptr = 0; i < m; ++i) {
        if (!rev[i]) {
            ptr = 0;
            continue;
        }
        while (i + ptr < m && g[i + ptr] == g[sa[rev[i] - 1] + ptr]) ptr++;
        hei[rev[i]] = ptr ? ptr-- : 0;
    }

    vector<vector<int>> sp(1, vector<int>(hei.begin(), hei.end()));
    for (int i = 1; (1 << i) <= m; ++i) {
        sp.emplace_back(m);
        for (int j = 0; j + (1 << i) <= m; ++j) {
            sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
        }
    }

    vector<bool> mark(m);
    for (int i = s.size() + 1; i < m; ++i) {
        mark[rev[i]] = true;
    }
    vector<int> prv(m), nxt(m);
    for (int i = 0, pv = -1; i < m; ++i) {
        if (mark[i]) pv = i;
        prv[i] = pv;
    }
    for (int i = m - 1, pv = -1; i >= 0; --i) {
        if (mark[i]) pv = i;
        nxt[i] = pv;
    }

    auto QueryLCP = [&](int l, int r) {
        int p = 31 - __builtin_clz(r - l);
        return min(sp[p][l + 1], sp[p][r - (1 << p) + 1]);
    };

    pair<int, int> res{-1, -1};
    int best = -1E9;

    for (int i = 0; i < s.size(); ++i) {
        int r = rev[i], lcp = 0;
        if (prv[r] != -1) {
            lcp = max(lcp, QueryLCP(prv[r], r));
        }
        if (nxt[r] != -1) {
            lcp = max(lcp, QueryLCP(r, nxt[r]));
        }
        if (lcp == 0) continue;
        r = i + lcp - 1;
        int score = lcp - max(i, (int)s.size() - r - 1);
        if (score > best) {
            best = score;
            res = make_pair(i, r);
        } else if (score == best) {
            res = min(res, make_pair(i, r));
        }
    }

    cout << res.first << " " << res.second << "\n";
    return 0;
}

