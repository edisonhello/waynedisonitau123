#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<vector<int>> g(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<int>> subtree(N);
    vector<map<int, pair<int, array<int, 20>>>> cnt(N);

    auto Dfs = [&](auto dfs, int x, int p = -1) -> int64_t {
        subtree[x] = {x};
        cnt[x][A[x]] = make_pair(1, array<int, 20>{});
        for (int i = 0; i < 20; ++i) {
            if ((x + 1) >> i & 1) cnt[x][A[x]].second[i]++;
        }
        int64_t res = 0;
        for (int u : g[x]) {
            if (u == p) continue;
            res += dfs(dfs, u, x);
            if (subtree[u].size() > subtree[x].size()) {
                subtree[x].swap(subtree[u]);
                cnt[x].swap(cnt[u]);
            }
            for (int v : subtree[u]) {
                auto it = cnt[x].find(A[x] ^ A[v]);
                if (it == cnt[x].end()) continue;
                for (int i = 0; i < 20; ++i) {
                    if ((v + 1) >> i & 1) res += (1LL << i) * (it->second.first - it->second.second[i]);
                    else res += (1LL << i) * it->second.second[i];
                }
            }
            for (int v : subtree[u]) {
                subtree[x].push_back(v);
                if (cnt[x].find(A[v]) == cnt[x].end()) cnt[x][A[v]] = make_pair(0, array<int, 20>{});
                auto it = cnt[x].find(A[v]);
                it->second.first++;
                for (int i = 0; i < 20; ++i) {
                    if ((v + 1) >> i & 1) it->second.second[i]++;
                }
            }
            vector<int>().swap(subtree[u]);
            map<int, pair<int, array<int, 20>>>().swap(cnt[u]);
        }
        return res;
    };

    cout << Dfs(Dfs, 0) << "\n";
    return 0;
}

