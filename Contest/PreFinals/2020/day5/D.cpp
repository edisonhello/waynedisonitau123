#include <bits/stdc++.h>
using namespace std;

namespace sfx {

constexpr int kN = 1'000'123;
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
    for (int i = n - 2; i >= 0; --i) t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
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
    for (int i = 0; i < s.size(); ++i) _s[i] = s[i];
    _s[s.size()] = 0;
    SAIS(_s, sa, p, q, t, c, s.size() + 1, 256);
    return vector<int>(sa + 1, sa + s.size() + 1);
}

}  // namespace sfx

int64_t Solve() {
    int k;
    cin >> k;
    string s;
    cin >> s;
    string t = s;
    int m = s.size();
    if (k == 1) {
        return 1LL * m * (m + 1) / 2;
    }
    reverse(t.begin(), t.end());
    s = s + "#" + t;
    auto sa = sfx::Build(s);

    int n = s.size();
    vector<int> rev(n);
    for (int i = 0; i < n; ++i) rev[sa[i]] = i;

    vector<int> hei(n);
    int ptr = 0;
    for (int i = 0; i < n; ++i) {
        if (!rev[i]) {
            ptr = 0;
            continue;
        }
        while (i + ptr < n && s[i + ptr] == s[sa[rev[i] - 1] + ptr]) ptr++;
        hei[rev[i]] = ptr ? ptr-- : 0;
    }

    vector<vector<int>> sp(1, vector<int>(n));
    for (int i = 0; i < n; ++i) sp[0][i] = hei[i];
    for (int i = 1; (1 << i) <= n; ++i) {
        sp.emplace_back(n);
        for (int j = 0; j + (1 << i) <= n; ++j) {
            sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
        }
    }

    auto Query = [&](int i, int j) {
        int l = rev[i];
        int r = rev[j];
        if (l > r) swap(l, r);
        int p = 31 - __builtin_clz(r - l);
        return min(sp[p][l + 1], sp[p][r - (1 << p) + 1]);
    };

    auto Rev = [&](int p) {
        return m + m - p;
    };

    auto DivideConquer = [&](auto self, int l, int r) -> int64_t {
        if (r - l == 1) {
            if (k == 1) return 1;
            return 0;
        }
        int m = (l + r) >> 1;
        int64_t res = self(self, l, m) + self(self, m, r);
        // cout << "l = " << l << " r = " << r << endl;
        for (int i = 1; i <= max(r - m, m - l); ++i) {
            if (i <= r - m && i <= m - l && Query(m - i, m) >= i) {
                int x = min((m + i < r ? Query(m, m + i) : 0) + i, r - m);
                int y = min(Query(Rev(m + i - 1), Rev(m - 1)), m - l);
                // cout << "equal i = " << i << " x = " << x << " y = " << y << endl;
                x = min(x, i * k - 1);
                y = min(y, i * k - 1);
                res += max(0, x + y - i * k + 1);
                continue;
            }
            if (i <= r - m) {
                int x = min((m + i < r ? Query(m, m + i) : 0) + i, r - m);
                int y = min(Query(Rev(m + i - 1), Rev(m - 1)), m - l);
                // cout << "right i = " << i << " x = " << x << " y = " << y << endl;
                x = min(x, i * k - 1);
                y = min(y, i * k - 1);
                // cout << "add = " << x + y - i * k + 1 << endl;
                res += max(0, x + y - i * k + 1);
            }
            if (i <= m - l) {
                int y = min((m - 1 - i >= l ? Query(Rev(m - 1 - i), Rev(m - 1)) : 0) + i, m - l);
                int x = min(Query(m - i, m), r - m);
                // cout << "left i = " << i << " x = " << x << " y = " << y << endl;
                x = min(x, i * k - 1);
                y = min(y, i * k - 1);
                // cout << "add = " << x + y - i * k + 1 << endl;
                res += max(0, x + y - i * k + 1);
            }
        }
        // cout << "res = " << res << endl;
        return res;
    };

    return DivideConquer(DivideConquer, 0, m);
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

