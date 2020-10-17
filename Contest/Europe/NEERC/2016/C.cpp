#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("cactus.in", "r", stdin);
    freopen("cactus.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> g(N);
    for (int i = 0; i < M; ++i) {
        int K;
        cin >> K;
        vector<int> path(K);
        for (int j = 0; j < K; ++j) {
            cin >> path[j];
            path[j]--;
        }
        for (int j = 0; j + 1 < K; ++j) {
            g[path[j]].push_back(path[j + 1]);
            g[path[j + 1]].push_back(path[j]);
        }
    }

    vector<bool> vis(N);

    enum Type { RECOLOR, JOIN, CONNECT };

    struct Operation { 
        Type type;
        int x, y, z;
    };

    vector<Operation> V;


    auto ReColor = [&](int x, int c1, int c2) {
        V.push_back({RECOLOR, x, c1, c2});
    };

    auto Join = [&](int x, int y) {
        V.push_back({JOIN, x, y});
    };

    auto Connect = [&](int x, int c1, int c2) {
        V.push_back({CONNECT, x, c1, c2});
    };

    vector<int> up(N, -1);
    vector<int> depth(N);
    vector<bool> has_up(N);

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        // cerr << "x = " << x << " p = " << p << endl;
        vis[x] = true;    
        int f = -1;
        ReColor(x, 1, 3);
        vector<int> child;
        for (int u : g[x]) {
            if (u == p) continue;
            if (vis[u]) {
                if (depth[u] < depth[x]) f = u;
            } else {
                depth[u] = depth[x] + 1;
                dfs(dfs, u, x);
                child.push_back(u);
            }
        }
        sort(child.begin(), child.end(), [&](int i, int j) {
            if (up[i] == -1 && up[j] == -1) return i < j;
            if (up[i] == -1) return false;
            if (up[j] == -1) return true;
            return depth[up[i]] > depth[up[j]];
        });
        for (int u : child) {
            // cerr << "x = " << x << " u = " << u << " up = " << up[u] << endl;
            Join(x, u);
            Connect(x, 3, 2);
            if (has_up[u]) assert(up[u] != x);
            if (has_up[u]) Connect(x, 3, 4);
            if (up[u] == x) {
                Connect(x, 3, 4);
                ReColor(x, 4, 1);
            } else if (up[u] != -1) {
                up[x] = up[u];
            }
            ReColor(x, 2, 1);
        }
        if (f != -1) {
            // cerr << "f = " << f << endl;
            // cerr << "check x = " << x << endl;
            assert(up[x] == -1 || up[x] == f);
            up[x] = f;
            has_up[x] = true;
        }
        if (f != -1) ReColor(x, 3, 4);
        else ReColor(x, 3, 2);
    };

    vector<int> join;
    for (int i = 0; i < N; ++i) {
        if (!vis[i]) {
            Dfs(Dfs, i);
            if (i > 0) join.push_back(i);
        }
    }
    for (int u : join) Join(0, u);
    cout << V.size() << "\n";
    for (int i = 0; i < V.size(); ++i) {
        if (V[i].type == RECOLOR) {
            cout << "r " << V[i].x + 1 << " " << V[i].y << " " << V[i].z << "\n";
        }
        if (V[i].type == JOIN) {
            cout << "j " << V[i].x + 1 << " " << V[i].y + 1 << "\n";
        }
        if (V[i].type == CONNECT) {
            cout << "c " << V[i].x + 1 << " " << V[i].y << " " << V[i].z << "\n";
        }
    }
}

