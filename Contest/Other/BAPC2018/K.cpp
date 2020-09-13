#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, H;
    cin >> N >> H;
    vector<vector<int>> g(N);
    vector<int> deg(N);
    for (int i = 0; i < N - 1; ++i) {
        int x, y;
        cin >> x >> y;
        deg[x]++;
        deg[y]++;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    if (N == 2) {
        cout << 1 << "\n";
        cout << 0 << " " << 1 << "\n";
        return 0;
    }
    int root = 0;
    while (deg[root] == 1) root++;

    vector<int> leave;

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        if (deg[x] == 1) leave.push_back(x);
        for (int u : g[x]) {
            if (u == p) continue;
            dfs(dfs, u, x);
        }
    };

    Dfs(Dfs, root);
    int K = leave.size();
    cout << (K + 1) / 2 << "\n";
    for (int i = 0, j = (K + 1) / 2; i < (K + 1) / 2; ++i, j = (j + 1) % K) {
        cout << leave[i] << " " << leave[j] << "\n"; 
    }
}

