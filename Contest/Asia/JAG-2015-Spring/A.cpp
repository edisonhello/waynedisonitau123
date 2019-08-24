#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
vector<int> g[maxn], tour; int sz[maxn], mz[maxn], a[maxn];
map<int, int> v1[maxn], v2[maxn];
int gc[maxn][3], gp[maxn][3];
char s[maxn];
bool v[maxn];

void dfssz(int x) {
    tour.push_back(x);
    v[x] = true;
    sz[x] = 1;
    mz[x] = 0;

    for (int u : g[x]) {
        if (!v[u]) {
            dfssz(u);
            sz[x] += sz[u];
            mz[x] = max(mz[x], sz[u]);
        }
    }
}

int dfsp1(int x, int c, int p, int z = -1) {
    int res = 0;
    c += a[x];
    p = min(a[x], a[x] + p);
    // printf("1 x = %d c = %d p = %d z = %d\n", x, c, p, z);
    if (z != -1 && p >= 0) v1[z][c]++;
    if (p >= 0 && c == 0) ++res;
    v[x] = true;
    for (int u : g[x]) {
        if (!v[u]) {
            res += dfsp1(u, c, p, z == -1 ? u : z);
        }
    }
    return res;
}

void dfsp2(int x, int c, int p, int z = -1) {
    c -= a[x];
    p = min(-a[x], -a[x] + p);
    // printf("2 x = %d c = %d p = %d z = %d\n", x, c, p, z);
    if (z != -1 && p >= 0) v2[z][c]++;
    v[x] = true;
    for (int u : g[x]) {
        if (!v[u]) {
            dfsp2(u, c, p, z == -1 ? u : z);
        }
    }
}

long long solve(int x) {
    for (int u : tour) v1[u].clear(), v2[u].clear(), v[u] = false;
    long long res = dfsp1(x, 0, 0);
    // printf("x = %d res = %lld\n", x, res);
    for (int u : tour) v[u] = false;
    v[x] = true;
    for (int u : g[x]) if (!v[u]) dfsp2(u, 0, 0, u);
    for (int u : tour) v[u] = false;
    map<int, int> pf;
    /* for (int u : g[x]) {
        printf("v1[%d]: ", u);
        for (auto it : v1[u]) printf("(%d, %d) ", it.first, it.second);
        printf("v2[%d]: ", u);
        for (auto it : v2[u]) printf("(%d, %d) ", it.first, it.second);
    } */
    if (a[x] == 1) {
        for (int u : g[x]) res += v2[u][1];
    }
    for (int u : g[x]) {
        if (!v[u]) {
            for (auto it : v1[u]) 
                res += 1LL * it.second * pf[it.first];
            for (auto it : v2[u])
                pf[it.first] += it.second;
        }
    }
    // printf("x = %d res = %lld\n", x, res);
    reverse(g[x].begin(), g[x].end());
    pf.clear();
    for (int u : g[x]) {
        if (!v[u]) {
            for (auto it : v1[u]) 
                res += 1LL * it.second * pf[it.first];
            for (auto it : v2[u])
                pf[it.first] += it.second;
        }
    }
    return res;
}

long long dfs(int x) {
    tour.clear(), dfssz(x);
    int c = -1;
    for (int u : tour) {
        int z = max(mz[u], (int)tour.size() - sz[u]);
        if (z * 2 <= (int)tour.size()) c = u;
        v[u] = false;
    }
    assert(c != -1);
    long long ans = solve(c);
    // printf("c = %d solve = %lld\n", c, ans);
    v[c] = true;
    for (int u : g[c]) {
        if (!v[u]) 
            ans += dfs(u);
    }
    return ans;
}

int main() {
    int n; scanf("%d", &n);
    scanf("%s", s);

    for (int i = 0; i < n; ++i) a[i] = (s[i] == '(' ? 1 : -1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    printf("%lld\n", dfs(0));
}
