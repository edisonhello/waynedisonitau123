#include <bits/stdc++.h>
using namespace std;

int Solve() {
    int N, M;
    cin >> N >> M;
    vector<int> V(N);
    for (int i = 0; i < N; ++i) {
        cin >> V[i];
        V[i]--;
    }
    vector<vector<int>> g(N);
    while (M--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        g[x].push_back(y);
    }
    int res = N;
    for (int s = 0; s < 2; ++s) {
        vector<int> que;
        vector<int> nque;
        vector<int> deg(N);
        vector<bool> vis(N);
        for (int i = 0; i < N; ++i) {
            for (int u : g[i]) {
                deg[u]++;
            }
        }
        for (int i = 0; i < N; ++i) {
            if (deg[i] == 0) {
                if (V[i] == s) que.push_back(i);
                else nque.push_back(i);
            }
        }
        int cur = s, flip = -1;
        while (!que.empty() || !nque.empty()) {
            flip++;
            for (int it = 0; it < que.size(); ++it) {
                int x = que[it];
                vis[x] = true;
                for (int u : g[x]) {
                    if (--deg[u] == 0) {
                        if (V[u] == cur) {
                            que.push_back(u);
                        } else {
                            nque.push_back(u);
                        }
                    }
                }
            }
            cur ^= 1;
            que = nque;
            nque.clear();
        }
        bool ok = true;
        for (int i = 0; i < N; ++i) ok &= vis[i];
        if (ok) {
            res = min(res, flip);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cout << Solve() << "\n";
    }
}

