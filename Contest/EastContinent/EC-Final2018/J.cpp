#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;

namespace sfxarray {
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
}

using namespace sfxarray;
vector<pair<int, int>> v[maxn];
int fa[maxn];
long double mg[maxn];

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

const long double eps = 1e-12;

bool equal(long double x, long double y) {
    return fabs(x - y) < eps;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        build(s);
        int n = (int)s.size();
        for (int i = 0; i <= n; ++i) v[i].clear();
        for (int i = 0; i < n; ++i) fa[i] = i;
        for (int i = 0; i < n; ++i) mg[i] = n - sa[i];
        for (int i = 1; i < n; ++i) v[hi[i]].emplace_back(i - 1, i);
        for (int i = n; i >= 0; --i) {
            sort(v[i].begin(), v[i].end());
            for (int j = 0; j < (int)v[i].size(); ) {
                int k = j + 1;
                int last = find(v[i][j].second);
                while (k < (int)v[i].size() && find(v[i][k].first) == last) {
                    last = find(v[i][k].second);
                    ++k;
                }
                long double sum = 0.0;
                bool f = false;
                for (int p = j; p < k; ++p) {
                    int l = find(v[i][p].first);
                    int r = find(v[i][p].second);
                    if (equal(i, mg[l])) f = true;
                    else sum += 1.0 / (mg[l] - i);
                    if (p == k - 1) {
                        if (equal(i, mg[r])) f = true;
                        else sum += 1.0 / (mg[r] - i);
                    }
                }
                int top = -1;
                for (int p = j; p < k; ++p) {
                    int l = find(v[i][p].first);
                    int r = find(v[i][p].second);
                    top = l;
                    fa[l] = r;
                }
                if (f) mg[find(top)] = i;
                else mg[find(top)] = (sum * i + 1) / sum;
                j = k;
            }
        }
        cout << fixed << setprecision(20) << mg[find(0)] << endl;
    }
    return 0;
}
