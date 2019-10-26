#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 100000;
const int kSqrt = 2000;
vector<int> g[kN];
bitset<kSqrt> bs[kN];
int ans[kN], id[kN], dg[kN], qu[kN];

int main() {
#ifdef ONLINE_JUDGE
    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);
#endif
    int n, m;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        scanf("%d", &m);
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < m; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            g[v].push_back(u);
        }
        for (int i = 0; i < n; ++i) ans[i] = 0;
        for (int i = 0; i < n; i += kSqrt) {
            for (int j = 0; j < n; ++j) bs[j].reset();
            for (int j = i, k = 0; j < n && j - i < kSqrt; ++j, ++k) {
                id[j] = k;
                bs[j].set(k);
            }
            for (int j = 0; j < n; ++j) {
                for (int u : g[j]) ++dg[u];
            }
            int ql = 0, qr = 0;
            for (int j = 0; j < n; ++j) {
                if (dg[j] == 0) qu[qr++] = j;
            }
            while (ql < qr) {
                int x = qu[ql++];
                for (int u : g[x]) {
                    bs[u] |= bs[x];
                    if (--dg[u] == 0)
                        qu[qr++] = u;
                }
            }
            for (int j = 0; j < n; ++j) ans[j] += bs[j].count();
        }
        int v = max_element(ans, ans + n) - ans;
        printf("%d %d\n", v + 1, ans[v]);
    }
    return 0;
}
