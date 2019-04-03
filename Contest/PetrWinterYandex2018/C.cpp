#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
vector<int> g[maxn];
bool adj[maxn], v[maxn];
int match[maxn];

bool dfs(int x) {
    v[x] = true;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (adj[u]) continue;
        if (match[u] == -1 || !v[match[u]] && dfs(match[u])) {
            match[u] = x;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        memset(adj, false, sizeof(adj));
        memset(match, -1, sizeof(match));

        for (int j = 0; j < (int)g[i].size(); ++j)
            adj[g[i][j]] = true;
        adj[i] = true;

        vector<int> other;
        for (int j = 0; j < n; ++j) {
            if (!adj[j])
                other.push_back(j);
        }

        if ((int)g[i].size() < (int)other.size())
            continue;

        int ans = 0;
        for (int j = 0; j < (int)g[i].size(); ++j) {
            memset(v, false, sizeof(v));
            if (dfs(g[i][j]))
                ans++;
        }


        if (ans == (int)other.size()) {
            vector<pair<int, int>> team;
            set<int> used;
            for (int j = 0; j < (int)other.size(); ++j) {
                team.emplace_back(match[other[j]], other[j]);
                used.insert(match[other[j]]);
            }
            for (int j = 0; j < (int)g[i].size(); ++j) {
                if (!used.count(g[i][j]))
                    team.emplace_back(g[i][j], -2);
            }

            puts("Yes");
            printf("%d %d\n", i + 1, (int)team.size());
            for (int j = 0; j < (int)team.size(); ++j)
                printf("%d %d\n", team[j].first + 1, team[j].second + 1);
            return 0;
        }
    }
    puts("No");
    return 0;
}
