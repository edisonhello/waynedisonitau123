#include <bits/stdc++.h>
using namespace std;

const int kN = 200'000 + 5;
vector<pair<int, int>> g[kN];
vector<int> y[kN], edg[kN];
int dfn[kN], low[kN], bcc[kN], c[kN], tk, kz, st[kN], ed[kN];
bool bip[kN], instk[kN];
stack<int> stk;

void Dfs(int x, int p) {
    dfn[x] = low[x] = tk++;
    for (auto ee : g[x]) {
        int u = ee.first, e = ee.second;
        if (u == p) continue;
        if (!instk[e]) {
            instk[e] = true;
            stk.push(e);
        }
        if (dfn[u] != -1) {
            low[x] = min(low[x], dfn[u]);
            continue;
        }
        Dfs(u, x);
        low[x] = min(low[x], low[u]);
        if (low[u] >= dfn[x]) {
            while (!stk.empty()) {
                int v = stk.top(); stk.pop();
                bcc[v] = kz;
                edg[kz].push_back(v);
                if (v == e) break;
            }
            kz++;
        }
    } 
}

vector<int> vk;

bool DfsBip(int x, int ck) {
    vk.push_back(x);
    c[x] = ck;
    bool res = true;
    for (int u : y[x]) {
        if (c[u] == -1) res &= DfsBip(u, ck ^ 1);
        else if (c[u] == c[x]) res = false;
    }
    return res;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
        st[i] = u, ed[i] = v;
    }
    memset(dfn, -1, sizeof(dfn));
    Dfs(0, -1);
    vector<int> edd;
    for (int i = 0; i < kz; ++i) {
        int z = -1;
        for (int e : edg[i]) {
            // printf("e = %d\n", e);
            y[st[e]].push_back(ed[e]);
            y[ed[e]].push_back(st[e]);
            c[st[e]] = -1;
            c[ed[e]] = -1;
            z = st[e];
        }
        // printf("z = %d\n", z);
        if (DfsBip(z, 0)) edd.push_back(i);
        for (int e : edg[i]) {
            c[st[e]] = -1;
            c[ed[e]] = -1;
            y[st[e]].clear();
            y[ed[e]].clear();
        }
    }
    for (int i : edd) {
        for (int e : edg[i]) {
            y[st[e]].push_back(ed[e]);
            y[ed[e]].push_back(st[e]);
        }
    }
    long long ev = 0, od = 0;
    memset(c, -1, sizeof(c));
    for (int i = 0; i < n; ++i) {
        if (c[i] != -1) continue;
        vk.clear();
        assert(DfsBip(i, 0));
        int cnt[2] = {0, 0};
        for (int u : vk) cnt[c[u]]++;
        ev += 1LL * cnt[0] * (cnt[0] - 1) / 2 + 1LL * cnt[1] * (cnt[1] - 1) / 2;
        od += 1LL * cnt[0] * cnt[1];
    }
    printf("%lld %lld\n", ev, od);
    return 0;
}
