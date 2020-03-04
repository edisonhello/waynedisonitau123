#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;

namespace sfxarray {
    int sa[maxn], tmp[2][maxn], c[maxn], hi[maxn], rev[maxn];
    void build(const vector<int> &s) {
        int sigma = (int)s.size();
        int *rnk = tmp[0], *rkn = tmp[1];
        for (int i = 0; i < sigma; ++i) c[i] = 0;
        for (int i = 0; i < s.size(); ++i) c[rnk[i] = s[i]]++;
        for (int i = 1; i < sigma; ++i) c[i] += c[i - 1];
        for (int i = s.size() - 1; i >= 0; --i) sa[--c[s[i]]] = i;
        for (int n = 1; n < s.size(); n *= 2) {
            for (int i = 0; i < sigma; ++i) c[i] = 0;
            for (int i = 0; i < s.size(); ++i) c[rnk[i]]++;
            for (int i = 1; i < sigma; ++i) c[i] += c[i - 1];
            int *sa2 = rkn;
            int r = 0;
            for (int i = s.size() - n; i < s.size(); ++i) sa2[r++] = i;
            for (int i = 0; i < s.size(); ++i) {
                if (sa[i] >= n) sa2[r++] = sa[i] - n;
            }
            for (int i = s.size() - 1; i >= 0; --i) sa[--c[rnk[sa2[i]]]] = sa2[i];
            rkn[sa[0]] = r = 0;
            for (int i = 1; i < s.size(); ++i) {
                if (!(rnk[sa[i - 1]] == rnk[sa[i]] && sa[i - 1] + n < s.size() && rnk[sa[i - 1] + n] == rnk[sa[i] + n])) r++;
                rkn[sa[i]] = r;
            }
            swap(rnk, rkn);
            if (r == s.size() - 1) break;
            sigma = r + 1;
        }
        for (int i = 0; i < s.size(); ++i) rev[sa[i]] = i;
        int ind = 0; hi[0] = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (!rev[i]) { ind = 0; continue; }
            while (i + ind < s.size() && sa[rev[i] - 1] + ind < (int)s.size() && s[i + ind] == s[sa[rev[i] - 1] + ind]) ++ind;
            hi[rev[i]] = ind ? ind-- : 0;
        }
    }
}

int a[maxn], l[maxn], r[maxn];

long long solve(int n) {
    for (int i = 0; i < n; ++i) {
        l[i] = i - 1;
        r[i] = i + 1;
    }
    for (int i = 0; i < n; ++i) {
        while (l[i] >= 0 && a[i] > a[l[i]]) l[i] = l[l[i]];
    }
    for (int i = n - 1; i >= 0; --i) {
        while (r[i] < n && a[i] >= a[r[i]]) r[i] = r[r[i]];
    }
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        res += a[i] * 1ll * (i - l[i]) * (r[i] - i);
    }
    return res;
}

namespace segtree {
    long long st[maxn * 4], tg[maxn * 4];
    void init(int n) {
        for (int i = 0; i < 4 * n; ++i) {
            st[i] = 0;
            tg[i] = 0;
        }
    }
    void push(int o, int l, int r) {
        if (tg[o] == 0) return;
        st[o * 2 + 1] += ((l + r) / 2 - l) * 1ll * tg[o], tg[o * 2 + 1] += tg[o];
        st[o * 2 + 2] += (r - (l + r) / 2) * 1ll * tg[o], tg[o * 2 + 2] += tg[o];
        tg[o] = 0;
    }
    void modify(int l, int r, int ql, int qr, int v, int o = 0) {
        if (r - l > 1) push(o, l, r);
        if (l >= qr || ql >= r) return;
        if (l >= ql && r <= qr) return st[o] += (r - l) * 1ll * v, tg[o] += v, void();
        modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
        modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
        st[o] = st[o * 2 + 1] + st[o * 2 + 2];
    }
    long long query(int l, int r, int ql, int qr, int o = 0) {
        if (r - l > 1) push(o, l, r);
        if (l >= qr || ql >= r) return 0;
        if (l >= ql && r <= qr) return st[o];
        return query(l, (l + r) >> 1, ql, qr, o * 2 + 1) + 
               query((l + r) >> 1, r, ql, qr, o * 2 + 2);
    }
}

int sp[20][maxn];

using namespace sfxarray;

int lcp(int x, int y) {
    int l = x, r = y;
    if (l > r) swap(l, r);
    ++l;
    int p = 31 - __builtin_clz(r - l + 1);
    // printf("query l = %d r = %d res = %d\n", l, r, min(sp[p][l], sp[p][r - (1 << p) + 1]));
    return min(sp[p][l], sp[p][r - (1 << p) + 1]);
}

vector<int> discrete(int n) {
    vector<int> v(n), ds;
    for (int i = 0; i < n; ++i) ds.push_back(a[i]);
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < n; ++i) v[i] = lower_bound(ds.begin(), ds.end(), a[i]) - ds.begin();
    return v;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        vector<int> v = discrete(n);
        sfxarray::build(v);
        long long res = solve(n);
        // for (int i = 0; i < n; ++i) printf("%d ", hi[i]);
        for (int i = 0; i < n; ++i) sp[0][i] = hi[i];
        for (int i = 1; (1 << i) <= n; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
            }
        }
        stack<tuple<int, int, int>> stk;
        segtree::init(n);
        segtree::modify(0, n, n - 1, n, a[n - 1]);
        stk.emplace(a[n - 1], n - 1, n);
        set<int> st;
        st.insert(rev[n - 1]);
        // printf("res = %lld\n", res);
        for (int i = n - 2; i >= 0; --i) {
            auto it = st.lower_bound(rev[i]);
            int lxp = 0;
            if (it != st.end()) {
                // printf("it = %d\n", *it);
                lxp = max(lxp, lcp(rev[i], *it));
            }
            if (it != st.begin()) {
                it = prev(it);
                // printf("it = %d\n", *it);
                lxp = max(lxp, lcp(rev[i], *it));
            }
            while (stk.size() && get<0>(stk.top()) < a[i]) {
                segtree::modify(0, n, get<1>(stk.top()), get<2>(stk.top()), -get<0>(stk.top()));
                stk.pop();
            }
            int r = stk.size() ? get<1>(stk.top()) : n;
            segtree::modify(0, n, i, r, a[i]);
            stk.emplace(a[i], i, r);
            st.insert(rev[i]);
            // printf("lcp = %d\n", lxp);
            // printf("query = %lld\n", segtree::query(0, n, i, i + lxp));
            res -= segtree::query(0, n, i, i + lxp);
        }
        printf("%lld\n", res);
    }
    return 0;
}
