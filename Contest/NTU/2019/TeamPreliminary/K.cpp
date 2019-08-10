#include <bits/stdc++.h>
using namespace std;

vector<int> G[200005];
int sz[200005], mxch[200005];
vector<int> ans[200005];

void dfs(int now, int pa) {
    sz[now] = 1;
    for (int i : G[now]) if (i != pa) {
        dfs(i, now);
        sz[now] += sz[i];
        if (mxch[now] == 0 || sz[i] > sz[mxch[now]]) mxch[now] = i;
    }
}

void dfs2(int now, int pa, int cent) {
    auto get = [&] (int cent) -> int {
        return max(sz[mxch[cent]], sz[now] - sz[cent]);
    };
    while (mxch[cent] && get(mxch[cent]) < get(cent)) cent = mxch[cent];
    if (mxch[cent] && get(mxch[cent]) == get(cent)) ans[now] = {cent, mxch[cent]};
    else ans[now] = {cent};
    sort(ans[now].begin(), ans[now].end());
    for (int i : G[now]) if (i != pa) {
        if (i == mxch[now]) dfs2(i, now, cent);
        else dfs2(i, now, i);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    dfs2(1, 0, 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < (int)ans[i].size(); ++j) cout << ans[i][j] << " \n"[j + 1 == ans[i].size()];
    }
}
