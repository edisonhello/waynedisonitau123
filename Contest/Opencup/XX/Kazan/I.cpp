#include <bits/stdc++.h>
using namespace std;

vector<int> g[200005];
bool vis[200005];
int sz[200005];
int mxchi[200005];
vector<int> work;

void DfsSz(int now, int pa) {
    sz[now] = 1;
    mxchi[now] = 0;
    for (int i : g[now]) if (i != pa && !vis[i]) {
        DfsSz(i, now);
        sz[now] += sz[i];
        if (sz[i] > sz[mxchi[now]]) mxchi[now] = i;
    }
    work.push_back(now);
}

void Dfs(int now) {
    work.clear();

    DfsSz(now, 0);
    int n = work.size();

    int cen = -1;
    for (int i : work) {
        if (max(n - sz[i], sz[mxchi[i]]) <= n / 2) {
            cen = i;
        }
    }

    vector<int> nei;
    for (int i : g[cen]) if (!vis[i]) nei.push_back(i);

    if (nei.empty()) {
        printf("! %d\n", now);
        exit(0);
    }

    vector<int> ask;
    int sum = 0;
    int z = 0;
    for (; z < (int)nei.size() && sum * 4 < n; ++z) {
        int i = nei[z];
        int zz = -1;
        if (sz[i] > sz[cen]) zz = n - sz[cen];
        else zz = sz[i];

        sum += zz;
        ask.push_back(i);
    }

    printf("? %d %d", (int)ask.size(), cen);
    for (int i : ask) printf(" %d", i);
    puts("");
    fflush(stdout);
    int rt; scanf("%d", &rt);

    if (rt == 1) {
        for (int i : ask) vis[i] = 1;
        Dfs(cen);
    } else {
        if (ask.size() == 1u) {
            vis[cen] = 1;
            Dfs(ask[0]);
        } else {
            for (int y = z; y < (int)nei.size(); ++y) vis[nei[y]] = 1;
            Dfs(cen);
        }
    }
}

int main() {
    int n; scanf("%d", &n);

    for (int i = 1; i < n; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    Dfs(1);

}

