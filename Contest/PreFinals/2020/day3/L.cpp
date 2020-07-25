#include <bits/stdc++.h>
using namespace std;

namespace sfx {


constexpr int kN = 400'000;
bool t[kN * 2];
int hi[kN], rv[kN];
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
        if (sa[i] && t[sa[i] - 1]) sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
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
    for (int i = nn - 1; i >= 0; --i) {
        sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
    }
    Induce(sa, c, s, t, n, z);
}

vector<int> Build(const string &s) {
    for (int i = 0; i < (int)s.size(); ++i) _s[i] = s[i];
    _s[(int)s.size()] = 0;
    SAIS(_s, sa, p, q, t, c, (int)s.size() + 1, 256);
    return vector<int>(sa + 1, sa + s.size() + 1);
}

}  // namespace sfx

int64_t Solve() {
    int n;
    cin >> n;
    vector<pair<string, int>> s(n);
    string t = "";
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i].first >> s[i].second;
        pos[i] = t.size();
        t += s[i].first;
        t += "#";
    }
    auto sa = sfx::Build(t);
    vector<int> rev(sa.size());
    for (int i = 0; i < sa.size(); ++i) {
        rev[sa[i]] = i;
    }
    vector<int> hei(sa.size());
    int ind = 0;
    for (int i = 0; i < sa.size(); ++i) {
        if (!rev[i]) {
            ind = 0;
            continue;
        }
        while (i + ind < t.size() && t[i + ind] == t[sa[rev[i] - 1] + ind]) ind++;
        hei[rev[i]] = ind ? ind-- : 0;
    }

    const int m = t.size();
    vector<int64_t> tree(m * 4);

    auto Modify = [&](int p, int64_t v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (r - l == 1) {
                tree[o] = max(tree[o], v);
                return;
            }
            int m = (l + r) >> 1;
            if (p < m) self(self, l, m, o * 2 + 1);
            else self(self, m, r, o * 2 + 2);
            tree[o] = max(tree[o * 2 + 1], tree[o * 2 + 2]);
        };
        _(_, 0, m);
    };

    auto Query = [&](int ql, int qr) {
        auto _ = [&](auto self, int l, int r, int o = 0) -> int64_t {
            if (l >= qr || ql >= r) return 0LL;
            if (l >= ql && r <= qr) return tree[o];
            int m = (l + r) >> 1;
            return max(self(self, l, m, o * 2 + 1), self(self, m, r, o * 2 + 2));
        };
        return _(_, 0, m);
    };

    vector<vector<int>> sp(1, vector<int>(m));
    for (int i = 0; i < m; ++i) sp[0][i] = hei[i];
    for (int i = 1; (1 << i) <= m; ++i) {
        sp.emplace_back(m);
        for (int j = 0; j + (1 << i) <= m; ++j) {
            sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
        }
    }

    auto QueryLCP = [&](int l, int r) {
        l++;
        int p = 31 - __builtin_clz(r - l + 1);
        return min(sp[p][l], sp[p][r - (1 << p) + 1]);
    };

    int64_t res = 0;
    for (int i = n - 1; i >= 0; --i) {
        int p = rev[pos[i]], l = p, r = p;
        int y = s[i].first.size();
        for (int d = 30; d >= 0; --d) {
            if (l - (1 << d) < 0) continue;
            if (QueryLCP(l - (1 << d), p) >= y) l -= (1 << d);
        }
        for (int d = 30; d >= 0; --d) {
            if (r + (1 << d) >= m) continue;
            if (QueryLCP(p, r + (1 << d)) >= y) r += (1 << d);
        }
        int64_t v = Query(l, r + 1) + s[i].second;
        res = max(res, v);
        for (int j = 0; j < y; ++j) {
            int p2 = rev[pos[i] + j];
            Modify(p2, v);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cout << Solve() << "\n";
    }
}

