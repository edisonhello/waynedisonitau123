#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

void Solve() {
    int n, s, thr;
    scanf("%d %d 0.%d", &n, &s, &thr);
    vector<int> x(n), y(n);
    vector<double> z(n);
    const int kB = max(1, s / 11); // TODO: s <= 11 ? 
    for (int i = 0; i < n; ++i) scanf("%d%d%lf", &x[i], &y[i], &z[i]);

    __gnu_pbds::cc_hash_table<int64_t, int> p;

    vector<int> ans;
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return z[i] > z[j]; });

    auto Check = [&](int i, int j) {
        // printf("Check i = %d j = %d\n", i, j);
        int up = max(y[i], y[j]), dn = min(y[i] + s, y[j] + s);
        int lt = max(x[i], x[j]), rg = min(x[i] + s, x[j] + s);
        if (up >= dn || lt >= rg) return false;
        int64_t area = 1LL * (dn - up) * (rg - lt);
        int64_t sum = 2LL * s * s - area;
        return thr * sum < area * 1000;
    };

    for (int i = 0; i < n; ++i) {
        // if (used[ord[i]]) continue;
        int a = x[ord[i]] / kB, b = y[ord[i]] / kB;
        int64_t h = 1LL * a * 1000000000 + b;
        if (p.find(h) != p.end()) continue;
        bool ok = true;
        for (int dx = -11; dx <= 11; ++dx) {
            for (int dy = -11; dy <= 11; ++dy) {
                if (dx == 0 && dy == 0) continue;
                int64_t g = 1LL * (a + dx) * 1000000000 + (b + dy);
                if (p.find(g) == p.end()) continue;
                // assert(!p[make_pair(a + dx, b + dy)].empty());
                int k = p[g];
                if (Check(ord[i], k)) ok = false;
            }
        }
        if (ok) {
            ans.push_back(ord[i]);
            p[h] = ord[i];
        }
    }
    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++i) printf("%d%c", ans[i] + 1, " \n"[i + 1 == ans.size()]);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        printf("Case #%d: ", tc);
        Solve();
    }
}

