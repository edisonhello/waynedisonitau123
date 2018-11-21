#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const int inf = 1e9 + 100;
int ed[maxn], w[maxn];
int fd, fi, fa[maxn], last[maxn], s[maxn], dp[maxn], fr[maxn], dep[maxn], far[maxn];
vector<int> g[maxn];

void dfs(int x, int p) {
    fr[x] = x;
    far[x] = 0;
    int ga = x;
    dp[x] = 0;
    pair<int, int> a = make_pair(-inf, -1), b = make_pair(-inf, -1);
    for (const int &e : g[x]) {
        int u = (ed[e] ^ x);
        if (u == p) continue;
        dfs(u, x);
        if (far[u] + w[e] > far[x]) {
            far[x] = far[u] + w[e];
            ga = dep[u];
        }
        if (dp[u] > dp[x]) {
            dp[x] = dp[u];
            fr[x] = fr[u];
        }
        pair<int, int> hey = make_pair(far[u] + w[e], u);
        if (hey > a) b = a, a = hey;
        else if (hey > b) b = hey;
    }
    dep[x] = ga;
    if (far[x] > dp[x]) {
        dp[x] = far[x];
        fr[x] = ga;
    }
    int aa = a.first, bb = b.first;
    if (aa + bb > dp[x]) {
        dp[x] = aa + bb;
        fr[x] = dep[a.second];
    }
}

void dfs2(int x, int p, int l, int d) {
    if (d > fd) fi = x, fd = d;
    fa[x] = p; last[x] = l;
    for (const int &e : g[x]) {
        int u = (ed[e] ^ x);
        if (u == p) continue;
        dfs2(u, x, e, d + w[e]);
    }
}


vector<int> diameter() {
     dfs(0, -1);
     fd = -inf; fi = -1;
     dfs2(fr[0], -1, -1, 0);
     vector<int> res;
     while (~last[fi]) {
         res.push_back(last[fi]);
         fi = fa[fi];
     }
     return res;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m, k; scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; ++i) g[i].clear();
        int res = 0;
        for (int i = 0; i < n - 1; ++i) {
            int x, y, d; scanf("%d%d%d", &x, &y, &d);
            --x, --y;
            w[i] = d;
            ed[i] = x ^ y;
            res += d + d;
            g[x].push_back(i);
            g[y].push_back(i);
        }
        for (int i = 0; i < m; ++i) {
            vector<int> e = diameter();
            int sum = 0;
            for (int j = 0; j < (int)e.size(); ++j) sum += w[e[j]];
            s[i + 1] = s[i] + sum - k;
            for (int j = 0; j < (int)e.size(); ++j) w[e[j]] = -w[e[j]];
        }
        int ans = 0;
        for (int i = 1; i <= m; ++i) ans = max(ans, s[i]);
        printf("%d\n", res - ans);
    }
}
