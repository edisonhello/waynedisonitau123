#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 9;
const int maxn = 3e6 + 5;
int fa[maxn], sz[maxn], fc[maxn], cnt[maxn];
bool ok;

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    fa[x] = y;
    --cnt[sz[x]];
    --cnt[sz[y]];
    sz[y] += sz[x];
    ++cnt[sz[y]];
    if (sz[y] > 3) ok = false;
}

int fpow(int x, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * x % mod;
        x = x * 1LL * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    vector<pair<int, int>> v, w;
    vector<int> ds;
    for (int i = 0; i < m; ++i) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        --a, --b;
        if (c == 0) v.emplace_back(a, b);
        else w.emplace_back(a, b);
        ds.push_back(a);
        ds.push_back(b);
    }

    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

    for (auto &p : v) {
        p.first = lower_bound(ds.begin(), ds.end(), p.first) - ds.begin();
        p.second = lower_bound(ds.begin(), ds.end(), p.second) - ds.begin();
    }
    for (auto &p : w) {
        p.first = lower_bound(ds.begin(), ds.end(), p.first) - ds.begin();
        p.second = lower_bound(ds.begin(), ds.end(), p.second) - ds.begin();
    }

    int k = (int)w.size(), p = (int)ds.size();

    fc[0] = 1;
    for (int i = 1; i < maxn; ++i) fc[i] = fc[i - 1] * 1LL * i % mod;

    auto solve = [&]() {
        if (!ok) return 0LL;
        int x = cnt[1] + 3 * n - p, y = cnt[2];
        // printf("x = %d y = %d\n", x, y);
        if (y > x) return 0LL;
        int d = fpow(6, (x - y) / 3) * 1LL * fc[(x - y) / 3] % mod;
        return 1LL * fc[x] * fpow(d, mod - 2) % mod;
    };

    int ans = 0;
    for (int s = 0; s < (1 << k); ++s) {
        ok = true;
        for (int i = 0; i <= p; ++i) fa[i] = i, sz[i] = 1, cnt[i] = 0; 
        cnt[1] = p;
        for (int i = 0; i < (int)v.size(); ++i) merge(v[i].first, v[i].second);
        for (int i = 0; i < k; ++i) {
            if (s >> i & 1) merge(w[i].first, w[i].second);
        }
        // printf("s = %d\n", s);
        if (__builtin_popcount(s) & 1) (ans += mod - solve()) %= mod;
        else (ans += solve()) %= mod;
    }
    printf("%d\n", ans);
}
