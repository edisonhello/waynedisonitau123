#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
vector<int> g[kN], res;
int d[kN], v[kN], dg[kN], pos[kN];

int main() {
#ifdef ONLINE_JUDGE
    freopen("grand.in", "r", stdin);
    freopen("grand.out", "w", stdout);
#endif
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n; ++i) scanf("%d", &d[i]);
        int m; scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            g[v].push_back(u);
        }

        auto Check = [&](int t) {
            for (int i = 0; i < n; ++i) v[i] = d[i] + t;
            priority_queue<pair<int, int>> pq;
            for (int i = 0; i < n; ++i) dg[i] = 0;
            for (int i = 0; i < n; ++i) {
                for (int u : g[i]) dg[u] += 1;
            }
            for (int i = 0; i < n; ++i) {
                if (dg[i] == 0)
                    pq.emplace(v[i], i);
            }
            int p = n;
            vector<int> od;
            while (!pq.empty()) {
                int x = pq.top().second;
                pq.pop();
                od.push_back(x);
                pos[x] = p--;
                for (int u : g[x]) {
                    if (--dg[u] == 0) {
                        pq.emplace(v[u], u);
                    }
                }
            }
            for (int i = 0; i < n; ++i) {
                if (pos[i] > v[i]) return false;
            }
            res = od;
            reverse(res.begin(), res.end());
            return true;
        };

        int ans = 1e6 + 1;
        for (int d = 20; d >= 0; --d) {
            if (ans - (1 << d) < 0) continue;
            if (Check(ans - (1 << d))) 
                ans -= (1 << d);
        }
        printf("%d\n", ans);
        for (int u : res) printf("%d ", u + 1);
        puts("");
    }
    return 0;
}
