#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000 + 5;
int x[maxn][2];
long long t[maxn];
map<pair<long long, long long>, int> cnt[maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("astronomy.in", "r", stdin);
    freopen("astronomy.out", "w", stdout);
#endif
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        for (int i = 0; i < n; ++i) scanf("%d%d", &x[i][0], &x[i][1]);
        map<long long, vector<int>> f;
        for (int i = 0; i < n; ++i) {
            t[i] = x[i][0] * 1ll * x[i][0] + x[i][1] * 1ll * x[i][1];
            f[t[i]].push_back(i);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                long long d = (x[i][0] - x[j][0]) * 1ll * (x[i][0] - x[j][0]) + 
                              (x[i][1] - x[j][1]) * 1ll * (x[i][1] - x[j][1]);
                ++cnt[i][make_pair(d, t[j])];
                // ++cnt[j][make_pair(d, t[i])];
            }
        }
        int m; scanf("%d", &m);
        while (m--) {
            long long a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
            if (f.find(a) == f.end()) {
                puts("0");
                continue;
            }
            if (f.find(b) == f.end()) {
                puts("0");
                continue;
            }
            int ans = 0;
            auto it = f.find(a);
            // int sz = f[a].size();
            for (int i = 0; i < (int)it->second.size(); ++i) {
                auto iit = cnt[it->second[i]].find(make_pair(c, b));
                if (iit != cnt[it->second[i]].end()) ans += iit->second;
            }
            if (a == b) ans >>= 1;
            printf("%d\n", ans);
        }
        for (int i = 0; i < n; ++i) cnt[i].clear();
    }
}
