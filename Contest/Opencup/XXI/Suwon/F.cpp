#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<int> u(M), v(M), w(M);
    vector<vector<int>> g(N);
    for (int i = 0; i < M; ++i) {
        cin >> u[i] >> v[i] >> w[i];
        u[i]--;
        v[i]--;
        g[u[i]].push_back(i);
        g[v[i]].push_back(i);
    }

    vector<bool> tree(M);
    vector<bool> visited(N);
    vector<int> fa(N, -1), depth(N);
    vector<int> value(N);

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        visited[x] = true;
        fa[x] = p;
        for (int e : g[x]) {
            int y = u[e] ^ v[e] ^ x;
            if (visited[y]) continue;
            depth[y] = depth[x] + 1;
            value[y] = value[x] ^ w[e];
            tree[e] = true;
            dfs(dfs, y, x);
        }
    };

    Dfs(Dfs, 0);
    vector<int> basis;

    auto HighBit = [](int v) {
        for (int i = 30; i >= 0; --i) {
            if (v >> i & 1) return i;
        }
        return -1;
    };

    for (int i = 0; i < M; ++i) {
        if (tree[i]) continue;
        int x = u[i], y = v[i];
        int s = w[i] ^ value[x] ^ value[y];
        for (int u : basis) s = min(s, s ^ u);
        if (s > 0) {
            int h = HighBit(s);
            for (int &u : basis) {
                if (u >> h & 1) u ^= s;
            }
            basis.push_back(s);
        }
    }
    vector<vector<int>> cnt(N + 1, vector<int>(30));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 30; ++j) {
            cnt[i + 1][j] = cnt[i][j] + (value[i] >> j & 1);
        }
    }
    vector<int> B(30);
    for (int u : basis) {
        int p = HighBit(u);
        assert(B[p] == 0);
        B[p] = u;
    }
    vector<int> sum(N + 1);
    for (int i = 0; i < N; ++i) sum[i + 1] = sum[i] ^ value[i];
    while (Q--) {
        int l, r;
        cin >> l >> r;
        l--;
        int ans = 0;
        for (int i = 0; i < 30; ++i) {
            int a = cnt[r][i] - cnt[l][i];
            int b = r - l - a;
            int64_t t = 1LL * a * (a - 1) / 2 + 1LL * b * (b - 1) / 2;
            if (t & 1) ans ^= B[i];
        }
        if ((r - l - 1) & 1) ans ^= sum[r] ^ sum[l];
        cout << ans << "\n";
    }
    return 0;
}

