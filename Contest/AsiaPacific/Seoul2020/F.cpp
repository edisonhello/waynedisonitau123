#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> g(N + 1);
    for (int i = 1; i <= M; ++i) g[0].push_back(i);
    for (int i = 0; i < K; ++i) {
        int s, t;
        cin >> s >> t;
        g[s].push_back(t);
    }

    auto Solve = [&](int root) {
        vector<vector<int>> r(N + 1), rdom(N + 1);
        vector<int> dfn(N + 1, -1), rev(N + 1, -1), fa(N + 1, -1), sdom(N + 1, -1), dom(N + 1, -1), val(N + 1, -1), rp(N + 1, -1);

        int stamp = 0;

        auto Dfs = [&](auto dfs, int x) -> void {
            rev[dfn[x] = stamp] = x;
            fa[stamp] = sdom[stamp] = val[stamp] = stamp;
            stamp++;
            for (int u : g[x]) {
                if (dfn[u] == -1) {
                    dfs(dfs, u);
                    rp[dfn[u]] = dfn[x];
                }
                r[dfn[u]].push_back(dfn[x]);
            }
        };

        Dfs(Dfs, root);

        auto Find = [&](auto dfs, int x, int c = 0) -> int {
            if (fa[x] == x) return c ? -1 : x;
            int p = dfs(dfs, fa[x], 1);
            if (p == -1) return c ? fa[x] : val[x];
            if (sdom[val[x]] > sdom[val[fa[x]]]) val[x] = val[fa[x]];
            fa[x] = p;
            return c ? p : val[x];
        };

        auto Merge = [&](int x, int y) { fa[x] = y; };

        for (int i = stamp - 1; i >= 0; --i) {
            for (int u : r[i]) sdom[i] = min(sdom[i], sdom[Find(Find, u)]);
            if (i > 0) rdom[sdom[i]].push_back(i);
            for (int u : rdom[i]) {
                int p = Find(Find, u);
                if (sdom[p] == i) dom[u] = i;
                else dom[u] = p;
            }
            if (i > 0) Merge(i, rp[i]);
        }
        vector<int> p(N + 1, -2);
        p[root] = -1;
        for (int i = 1; i < stamp; ++i) {
            if (sdom[i] != dom[i]) dom[i] = dom[dom[i]];
        }
        for (int i = 1; i < stamp; ++i) p[rev[i]] = rev[dom[i]];
        int res = 0;
        for (int i = 1; i <= N; ++i) {
            if (p[i] == 0) res++;
        }
        return res;
    };

    cout << Solve(0) << "\n";
}

