#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> g(N);
    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> color(N, -1);
    vector<int> cnt(2);

    auto Dfs = [&](auto dfs, int x, int c) -> bool {
        color[x] = c;
        cnt[c]++;
        for (int u : g[x]) {
            if (color[u] != -1) {
                if (color[u] != (c ^ 1)) return false;
            } else {
                if (!dfs(dfs, u, c ^ 1)) return false;
            }
        }
        return true;
    };

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (color[i] != -1) continue;
        cnt[0] = cnt[1] = 0;
        if (!Dfs(Dfs, i, 0)) {
            cout << "-1\n";
            return 0;
        }
        ans += min(cnt[0], cnt[1]);
    }
    cout << ans << "\n";
}

