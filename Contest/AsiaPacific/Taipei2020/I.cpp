#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> g(N);
    vector<int> ed(M);
    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        ed[i] = x ^ y;
        g[x].push_back(i);
        g[y].push_back(i);
    }

    vector<int> dfn(N, -1), low(N);
    vector<bool> in(M);
    vector<int> stk;
    vector<int> comp;
    vector<bool> cut(N);
    int bridge = 0, stamp = 0;

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        dfn[x] = low[x] = stamp++;
        int child = 0;
        for (int e : g[x]) {
            if (e == p) continue;
            int u = ed[e] ^ x;
            if (!in[e]) {
                in[e] = true;
                stk.push_back(e);
            }
            if (dfn[u] != -1) {
                low[x] = min(low[x], dfn[u]);
            } else {
                child++;
                dfs(dfs, u, e);
                low[x] = min(low[x], low[u]);
                if (low[u] >= dfn[x]) {
                    int sz = 0;
                    while (true) {
                        int f = stk.back();
                        stk.pop_back();
                        sz++;
                        if (f == e) break;
                    }
                    cut[x] = true;
                    comp.push_back(sz);
                }
            }
        }
        if (child == 1 && p == -1) cut[x] = false;
        if (dfn[x] == low[x] && p != -1) bridge++;
    };

    for (int i = 0; i < N; ++i) {
        if (dfn[i] != -1) continue;
        stamp = 0;
        Dfs(Dfs, i);
        if (!stk.empty()) {
            comp.push_back(stk.size());
            stk.clear();
        }
    }
    int cnt = 0;
    for (int i = 0; i < N; ++i) cnt += (int)cut[i];
    int p = comp.size(), q = *max_element(comp.begin(), comp.end());
    int z = __gcd(p, q);
    p /= z;
    q /= z;
    cout << cnt << " " << bridge << " " << p << " " << q << "\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        Solve();
    }
}
