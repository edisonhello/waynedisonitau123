#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> st(N - 1), ed(N - 1), w(N - 1);
    vector<vector<int>> g(N);
    for (int i = 0; i < N - 1; ++i) {
        cin >> st[i] >> ed[i] >> w[i];
        st[i]--;
        ed[i]--;
        g[st[i]].push_back(i);
        g[ed[i]].push_back(i);
    }

    vector<int> fa(N, -1);
    auto Get = [&](const vector<int> &A) {
        vector<int> sz(N);
        for (int u : A) sz[u] = 1;

        auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
            for (int e : g[x]) {
                int u = st[e] ^ ed[e] ^ x;
                if (u == p) continue;
                fa[u] = x;
                dfs(dfs, u, x);
                sz[x] += sz[u];
            }
        };

        Dfs(Dfs, 0);
        return sz;
    };

    vector<vector<int>> A(3);
    vector<vector<int>> sz(3);
    for (int i = 0; i < 3; ++i) {
        int M;
        cin >> M;
        A[i].resize(M);
        for (int j = 0; j < M; ++j) {
            cin >> A[i][j];
            A[i][j]--;
        }
        sz[i] = Get(A[i]);
    }
    double res = 0.0;
    for (int i = 0; i < N - 1; ++i) {
        int u = st[i], v = ed[i];
        assert(fa[u] == v || fa[v] == u);
        if (fa[u] == v) swap(u, v);

        double P1 = static_cast<double>(sz[0][v]) / A[0].size();
        double Q1 = 1 - P1;
        double P2 = static_cast<double>(sz[1][v]) / A[1].size();
        double Q2 = 1 - P2;
        double P3 = static_cast<double>(sz[2][v]) / A[2].size();
        double Q3 = 1 - P3;
        
        double P = P1 * Q2 * Q3 + P2 * Q1 * Q3 + P3 * Q1 * Q2;
        double Q = Q1 * P2 * P3 + Q2 * P1 * P3 + Q3 * P1 * P2;
        res += w[i] * (P + Q);
    }
    cout << fixed << setprecision(20) << res << "\n";
}

