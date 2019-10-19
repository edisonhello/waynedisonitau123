#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<pair<int, int>> add[maxn], sub[maxn], query[maxn];
int sum[maxn * 4], tg[maxn * 4];
bool ok[maxn];

void Push(int o) {
    tg[o * 2 + 1] += tg[o];
    sum[o * 2 + 1] += tg[o];
    tg[o * 2 + 2] += tg[o];
    sum[o * 2 + 2] += tg[o];
}

void Modify(int l, int r, int ql, int qr, int v, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) {
        tg[o] += v;
        sum[o] += v;
        return;
    }
    Push(o);
    Modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
    Modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
}

int Query(int l, int r, int p, int o = 0) {
    if (r - l == 1) return sum[o];
    Push(o);
    if (p < (l + r) >> 1) return Query(l, (l + r) >> 1, p, o * 2 + 1);
    else return Query((l + r) >> 1, r, p, o * 2 + 2);
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < maxn; ++i) {
            query[i].clear();
            add[i].clear();
            sub[i].clear();
        }
        memset(sum, 0, sizeof(sum));
        memset(tg, 0, sizeof(tg));
        int n, m; scanf("%d%d", &n, &m);
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &v[i].first, &v[i].second);
            ++v[i].first, ++v[i].second;
        }
        long long area = 0;
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            area += 1LL * v[i].first * v[j].second - 1LL * v[i].second * v[j].first;
        }
        if (area < 0) {
            reverse(v.begin(), v.end());
        }
        vector<pair<int, int>> w(v.begin(), v.end());
        for (int i = 1; i < n; ++i) {
            assert(w[i] != w[i - 1]);
        }
        for (int i = 0; i < m; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            ++x, ++y;
            query[x - 1].emplace_back(y - 1, i);
            query[x - 1].emplace_back(y, i);
            query[x].emplace_back(y - 1, i);
            query[x].emplace_back(y, i);
            ok[i] = false;
        }
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            assert(v[i].first == v[j].first || v[i].second == v[j].second);
            if (v[i].first == v[j].first) {
                if (v[i].second > v[j].second)
                    add[v[i].first].emplace_back(v[j].second, v[i].second);
                else
                    sub[v[i].first].emplace_back(v[i].second, v[j].second);
            }
        }
        for (int i = 0; i < maxn; ++i) {
            for (auto e : add[i]) Modify(0, maxn, e.first, e.second, 1);
            for (auto e : sub[i]) Modify(0, maxn, e.first, e.second, -1);
            for (auto e : query[i]) ok[e.second] |= Query(0, maxn, e.first) > 0;
        }
        int ans = 0;
        for (int i = 0; i < m; ++i) ans += ok[i];
        printf("%d\n", ans);
    }
    return 0;
}
