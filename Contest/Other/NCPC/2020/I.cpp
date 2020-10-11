#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 500 + 50;
constexpr int kInf = 1'000'000'000;

struct DMST {
    int g[kN][kN], fw[kN];
    int n, fr[kN];
    bool vis[kN], inc[kN];

    void Clear() {
        for (int i = 0; i < kN; ++i) {
            for (int j = 0; j < kN; ++j) g[i][j] = kInf;
            vis[i] = inc[i] = false;
        }
    }

    void AddEdge(int u, int v, int w) {
        g[u][v] = min(g[u][v], w);
    }

    int operator()(int root, int _n) {
        n = _n;
        if (Dfs(root) != n) return -1;
        int ans = 0;
        while (true) {
            for (int i = 1; i <= n; ++i) fw[i] = kInf, fr[i] = i;
            for (int i = 1; i <= n; ++i) if (!inc[i]) {
                for (int j = 1; j <= n; ++j) {
                    if (!inc[j] && i != j && g[j][i] < fw[i]) {
                        fw[i] = g[j][i];
                        fr[i] = j;
                    }
                }
            }
            int x = -1;
            for (int i = 1; i <= n; ++i) {
                if (i != root && !inc[i]) {
                    int j = i, c = 0;
                    while (j != root && fr[j] != i && c <= n) ++c, j = fr[j];
                    if (j == root || c > n) continue;
                    x = i;
                    break;
                }
            }
            if (x == -1) {
                for (int i = 1; i <= n; ++i) {
                    if (i != root && !inc[i]) ans += fw[i];
                }
                return ans;
            }
            int y = x;
            for (int i = 1; i <= n; ++i) vis[i] = false;
            do {
                ans += fw[y];
                y = fr[y];
                vis[y] = inc[y] = true;
            } while (y != x);
            inc[x] = false;
            for (int k = 1; k <= n; ++k) if (vis[k]) {
                for (int j = 1; j <= n; ++j) if (!vis[j]) {
                    if (g[x][j] > g[k][j]) g[x][j] = g[k][j];
                    if (g[j][k] < kInf && g[j][k] - fw[k] < g[j][x]) g[j][x] = g[j][k] - fw[k];
                }
            }
        }
        return ans;
    }
    int Dfs(int now) {
        int r = 1;
        vis[now] = true;
        for (int i = 1; i <= n; ++i) {
            if (g[now][i] < kInf && !vis[i]) r += Dfs(i);
        }
        return r;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    DMST dmst;
    vector<int> pw(2000, 1);

    constexpr int kH = 7122;
    constexpr int kP = 1'000'000'000 + 123;

    for (int i = 1; i < 2000; ++i) {
        pw[i] = 1LL * pw[i - 1] * kH % kP;
    }
    while (T--) {
        int N;
        cin >> N;
        vector<string> S(N + 1);
        for (int i = 0; i <= N; ++i) cin >> S[i];

        vector<int> fail(2000);

        auto Failure = [&](const string &S, const string &T) {
            int N = S.size(), M = T.size();
            auto Get = [&](int p) -> int {
                if (p < N) return S[p];
                if (p == N) return 7122;
                return T[p - N - 1];
            };

            for (int i = 1, k = 0; i < N + M + 1; ++i) {
                while (k > 0 && Get(i) != Get(k)) k = fail[k - 1];
                if (Get(i) == Get(k)) ++k;
                fail[i] = k;
            }
            return fail[N + M];
        };

        dmst.Clear();

        vector<vector<int>> pref(N + 1), suff(N + 1);
        for (int i = 0; i <= N; ++i) {
            int M = S[i].size();
            pref[i].resize(M);
            suff[i].resize(M);
            for (int j = 0, p = 0; j < M; ++j) {
                pref[i][j] = (1LL * p * kH + S[i][j]) % kP;
                p = pref[i][j];
            }
            for (int j = M - 1, p = 0, k = 0; j >= 0; --j, k++) {
                suff[i][j] = (1LL * S[i][j] * pw[k] + p) % kP;
                p = suff[i][j];
            }
        }

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                if (i == j) continue;
                int X = S[i].size(), Y = S[j].size();
                int cost = 0;
                for (int k = min(X, Y); k >= 1; --k) {
                    if (suff[i][X - k] == pref[j][k - 1]) {
                        cost = k;
                        break;
                    }
                }
                cost = S[j].size() - cost;
                // int cost = S[j].size();
                dmst.AddEdge(i + 1, j + 1, cost);
            }
        }
        cout << dmst(1, N + 1) << "\n";
    }
}
