#include <bits/stdc++.h>
using namespace std;

const int kN = 300'000 + 5;
int a[kN], b[kN], s[kN], f[kN], c[kN], uf[kN], st[kN], ga[kN];
long long cost[kN];

int Find(int x) {
    if (uf[x] == x) return uf[x];
    return uf[x] = Find(uf[x]);
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d%d", &a[i], &b[i]);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &s[i], &f[i], &c[i]);
        --s[i], --f[i];
    }

    vector<int> od(m);
    iota(od.begin(), od.end(), 0);
    sort(od.begin(), od.end(), [&](int i, int j) {
        return c[i] < c[j];
    });

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        uf[i] = i;
        ga[i] = a[i];
        st[i] = b[i];
        cost[i] = 1LL * a[i] * b[i];
        ans += 1LL * a[i] * b[i];
    }

    long long cur = ans;

    auto Merge = [&](int x, int y, int w) {
        x = Find(x), y = Find(y);
        cur -= cost[x];
        cur -= cost[y];
        uf[x] = y;
        st[y] = min(st[y], st[x]);
        ga[y] = max(ga[y], max(ga[x], w));
        cost[y] = min(cost[x] + cost[y], 1LL * ga[y] * st[y]);
        cur += cost[y];
        ans = min(ans, cur);
    };

    for (int i = 0; i < m; ++i) {
        int j = od[i];
        if (Find(s[j]) == Find(f[j])) continue;
        Merge(s[j], f[j], c[j]);
    }
    printf("%lld\n", ans);
    return 0;
}
