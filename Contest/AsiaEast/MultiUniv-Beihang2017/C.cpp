#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define dec asd
 
using namespace __gnu_pbds;
using namespace std;
 
const int maxn = 2e5 + 5;
vector<int> g[maxn];
cc_hash_table<int, int> cnt[maxn];
int c[maxn], sz[maxn];
bool ok[maxn];
long long dec[maxn];
 
void dfs(int x, int p) {
    sz[x] = 1;
    long long res = 0;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
 
        int p = sz[u] - (cnt[u].find(c[x]) == cnt[u].end() ? 0 : cnt[u][c[x]]);
        dec[c[x]] += 1ll * p * (p - 1) / 2;
 
        if (cnt[u].size() > cnt[x].size()) cnt[x].swap(cnt[u]);
 
        for (auto it : cnt[u]) cnt[x][it.first] += it.second;
    }
 
    // int siz = sz[x] - 1 - cnt[x][c[x]];
    cnt[x][c[x]] = sz[x];
 
    // dec[c[x]] += siz * 1ll * (siz - 1) / 2;
}
 
int main() {
    int n, tc = 0; 
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 1; i <= n; ++i) ok[i] = false;
        for (int i = 0; i < n; ++i) scanf("%d", &c[i]), ok[c[i]] = true;
 
        for (int i = 0; i < n - 1; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            --x, --y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
 
        for (int i = 0; i < n; ++i) cnt[i].clear();
        for (int i = 1; i <= n; ++i) dec[i] = 0;
        dfs(0, -1);
 
        for (auto it : cnt[0]) {
            if (it.first == c[0]) continue;
            int p = n - it.second;
            dec[it.first] += 1ll * p * (p - 1) / 2;
        }
        /* for (int i = 1; i <= n; ++i) {
            if (!ok[i]) continue;
            int x = n - cnt[0][i];
            dec[i] += 1ll * x * (x - 1) / 2;
        } */
 
        long long ans = 0;
        for (int i = 1; i <= n; ++i) if (ok[i]) ans += n * 1ll * (n - 1) / 2 - dec[i];
 
        printf("Case #%d: %lld\n", ++tc, ans);
    }
}
