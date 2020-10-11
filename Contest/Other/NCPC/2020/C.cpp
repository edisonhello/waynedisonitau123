#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    int M;
    cin >> M;
    int H = M / N;
    assert(__builtin_popcount(H) == 1);
    vector<vector<int>> g(N);
    vector<int> st(M), ed(M);
    for (int i = 0; i < M; ++i) {
        cin >> st[i] >> ed[i];
        g[st[i]].push_back(i);
        g[ed[i]].push_back(i);
    }
    for (int i = 0; i < N; ++i) {
        assert(g[i].size() % 2 == 0);
    }
    vector<bool> used(M);
    while (M >= N) {
        fill(used.begin(), used.end(), false);
        vector<bool> vis(N);
        vector<int> euler;

        auto Dfs = [&](auto dfs, int x) -> void {
            vis[x] = true;
            while (!g[x].empty()) {
                int e = g[x].back();
                g[x].pop_back();
                if (!used[e]) {
                    used[e] = true;
                    dfs(dfs, st[e] ^ ed[e] ^ x);
                    euler.push_back(e);
                }
            }
        };

        for (int i = 0; i < N; ++i) {
            if (!vis[i]) Dfs(Dfs, i);
        }
        assert(euler.size() == M);
        vector<vector<int>> ng(N);
        for (int i = 0; i < M; i += 2) {
            ng[st[euler[i]]].push_back(euler[i]);
            ng[ed[euler[i]]].push_back(euler[i]);
        }
        if (M > N) {
            for (int i = 0; i < N; ++i) {
                assert(ng[i].size() % 2 == 0);
            }
        }
        g = ng;
        M >>= 1;
    }
    vector<bool> match(N);
    for (int i = 0; i < N; ++i) {
        assert(g[i].size() == 1);
        if (!match[i]) {
            int e = g[i][0];
            cout << i << " " << (st[e] ^ ed[e] ^ i) << "\n";
            match[i] = true;
            match[st[e] ^ ed[e] ^ i] = true;
        }
    }
}
