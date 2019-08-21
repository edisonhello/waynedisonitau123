#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;

namespace segtree {
    long long st[maxn * 4], sum[maxn * 4];
    void init() {
        memset(st, 0, sizeof(st));
        memset(sum, 0, sizeof(sum));
    }
    void modify(int l, int r, int p, int v, int o = 0) {
        if (r - l == 1) return st[o] += v, sum[o] += l * 1ll * v, void();
        if (p < (l + r) >> 1) modify(l, (l + r) >> 1, p, v, o * 2 + 1);
        else modify((l + r) >> 1, r, p, v, o * 2 + 2);
        st[o] = st[o * 2 + 1] + st[o * 2 + 2];
        sum[o] = sum[o * 2 + 1] + sum[o * 2 + 2];
    }
    long long query(int l, int r, int k, int o = 0) {
        if (r - l == 1) return min(1ll * k, st[o]) * 1ll * l;
        if (st[o * 2 + 1] >= k) return query(l, (l + r) >> 1, k, o * 2 + 1);
        else return sum[o * 2 + 1] + query((l + r) >> 1, r, k - st[o * 2 + 1], o * 2 + 2);
    }
}

int l[maxn], r[maxn], c[maxn], p[maxn];
vector<int> st[maxn], ed[maxn];

int main() {
    int n, k, m; scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d%d", &l[i], &r[i], &c[i], &p[i]);
        st[l[i]].push_back(i);
        ed[r[i]].push_back(i);
    }
    long long ans = 0;
    segtree::init();
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < (int)st[i].size(); ++j) segtree::modify(0, maxn, p[st[i][j]], +c[st[i][j]]);
        ans += segtree::query(0, maxn, k);
        for (int j = 0; j < (int)ed[i].size(); ++j) segtree::modify(0, maxn, p[ed[i][j]], -c[ed[i][j]]);
    }
    printf("%lld\n", ans);
}
