#include <bits/stdc++.h>
using namespace std;

int dd[500005];
vector<int> g[500005];
int d[500005];
bool v[500005];

void bfs(int st) {
    queue<int> q;
    memset(v, 0, sizeof(v));
    memset(d, 0, sizeof(d));
    q.push(st);
    v[st] = 1;
    while (q.size()) {
        int now = q.front(); q.pop();
        for (int i : g[now]) {
            if (!v[i]) {
                d[i] = (d[now] + 1) % 3;
                v[i] = 1;
                q.push(i);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> dd[i];

    while (m--) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) if (dd[i] == 0) {
        bool a1 = true;
        for (int j : g[i]) if (dd[j] != 1) a1 = false;
        if (a1) {
            cout << i << endl;
            exit(0);
        }
    }

}

