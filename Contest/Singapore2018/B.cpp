#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn];
int color[maxn];

bool dfs(int x, int c) {
    color[x] = c;
    bool res = true;
    for (const int &u : g[x]) {
        if (color[u] == -1) res &= dfs(u, c ^ 1);
        else res &= color[u] != color[x];
    }
    return res;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    memset(color, -1, sizeof(color));
    int bip = 0, c = 0;
    for (int i = 0; i < n; ++i) {
        if (color[i] != -1) continue;
        if (dfs(i, 0)) ++bip;
        ++c;
    }
    if (bip == c) c++;
    printf("%d\n", c - 1);
}
