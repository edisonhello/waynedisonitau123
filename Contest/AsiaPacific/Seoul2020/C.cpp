#include <bits/stdc++.h>
using namespace std;


vector<int> g[100005];
int mark[100005];

void dfs(int now, int pa) {
    int init = mark[now];
    for (int i : g[now]) if (i != pa) {
        dfs(i, now);
        mark[now] += mark[i];
    }
    if (!init && mark[now]) ++mark[now];
}

int main() {
    int n, m; cin >> n >> m;

    if (m == 1) {
        cout << 1 << endl;
        exit(0);
    }


    for (int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> spe;
    for (int i = 1; i <= m; ++i) {
        int t; cin >> t;
        spe.push_back(t);
        mark[t] = 1;
    }

    mark[spe[0]] = 0;

    dfs(spe[0], 0);

    cout << mark[spe[0]] << endl;
}

