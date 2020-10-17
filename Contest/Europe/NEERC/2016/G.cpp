#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005];
vector<int> ig[100005];

bool vis[100005][2];
int cnt[100005][2];
char ans[2][100005];

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    int n, m; cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        ig[v].push_back(u);
    }

    queue<pair<int, int>> q;
    for (int i = 1; i <= n; ++i) {
        if (g[i].empty()) {
            q.emplace(i, 0);
            q.emplace(i, 1);

            vis[i][0] = 1;
            vis[i][1] = 1;
        }
    }

    while (q.size()) {
        auto p = q.front(); q.pop();
        // cerr << "first view p = " << p.first << ' ' << p.second << endl;
        
        if (p.second == 1) {
            for (int i : ig[p.first]) {
                cnt[i][0]++;
                if (cnt[i][0] == (int)g[i].size()) {
                    vis[i][0] = 1;
                    q.emplace(i, 0);
                }
            }
        } else {
            for (int i : ig[p.first]) {
                if (!vis[i][1]) {
                    vis[i][1] = 1;
                    q.emplace(i, 1);
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) if (!vis[i][0]) ans[0][i] = 'D';
    for (int i = 1; i <= n; ++i) if (!vis[i][1]) ans[1][i] = 'D';

    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i <= n; ++i) {
        if (g[i].empty()) {
            q.emplace(i, 0);
            vis[i][0] = 1;
        }
    }

    while (q.size()) {
        auto p = q.front(); q.pop();
        // cerr << "second view p = " << p.first << ' ' << p.second << endl;
        
        if (p.second == 1) {
            for (int i : ig[p.first]) {
                cnt[i][0]++;
                if (cnt[i][0] == (int)g[i].size()) {
                    vis[i][0] = 1;
                    q.emplace(i, 0);
                }
            }
        } else {
            for (int i : ig[p.first]) {
                if (!vis[i][1]) {
                    vis[i][1] = 1;
                    q.emplace(i, 1);
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) if (!ans[0][i]) {
        if (!vis[i][0]) ans[0][i] = 'W';
        else ans[0][i] = 'L';
    }
    for (int i = 1; i <= n; ++i) if (!ans[1][i]) {
        if (vis[i][1]) ans[1][i] = 'W';
        else ans[1][i] = 'L';
    }

    cout << ans[0] + 1 << endl << ans[1] + 1 << endl;
}

