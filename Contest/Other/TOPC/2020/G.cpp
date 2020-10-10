#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev, flow;
    Edge(int t, int c, int r) : to(t), cap(c), rev(r), flow(0) {}
};

int Flow(vector<vector<Edge>> &g, int S, int T) {
    int N = g.size();
    vector<int> lev(N);
    vector<int> iter(N);
    int res = 0;
    while (true) {
        fill(lev.begin(), lev.end(), -1);
        lev[S] = 0;
        vector<int> que(1, S);
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            for (Edge &e : g[x]) {
                if (e.cap == 0) continue;
                if (lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    que.push_back(e.to);
                }
            }
        }
        if (lev[T] == -1) break;
        fill(iter.begin(), iter.end(), 0);

        auto Dfs = [&](auto dfs, int x, int f = 1'000'000'000) -> int {
            if (x == T) return f;
            int res = 0;
            for (int &it = iter[x]; it < g[x].size(); ++it) {
                Edge &e = g[x][it];
                if (e.cap == 0) continue;
                if (lev[e.to] == lev[x] + 1) {
                    int p = dfs(dfs, e.to, min(f - res, e.cap));
                    res += p;
                    e.cap -= p;
                    e.flow += p;
                    g[e.to][e.rev].cap += p;
                    g[e.to][e.rev].flow -= p;
                }
            }
            if (res == 0) lev[x] = -1;
            return res;
        };

        res += Dfs(Dfs, S);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }

    vector<vector<Edge>> g(N * M + 2);
    auto AddEdge = [&](int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    };

    int good = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '*') continue;
            good++;
            if ((i + j) & 1) {
                AddEdge(N * M, i * M + j, 1);
                if (i > 0 && grid[i - 1][j] != '*') {
                    AddEdge(i * M + j, (i - 1) * M + j, 1);
                }
                if (i + 1 < N && grid[i + 1][j] != '*') {
                    AddEdge(i * M + j, (i + 1) * M + j, 1);
                }
                if (j > 0 && grid[i][j - 1] != '*') {
                    AddEdge(i * M + j, i * M + j - 1, 1);
                }
                if (j + 1 < M && grid[i][j + 1] != '*') {
                    AddEdge(i * M + j, i * M + j + 1, 1);
                }
            } else {
                AddEdge(i * M + j, N * M + 1, 1);
            }
        }
    }
    int res = Flow(g, N * M, N * M + 1);
    cout << good - res << "\n";
    auto ans = grid;
    vector<int> match(N * M, -1);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '*') continue;
            if ((i + j) & 1) {
                for (Edge &e : g[i * M + j]) {
                    if (e.to < N * M && e.flow == 1) {
                        match[i * M + j] = e.to;
                        match[e.to] = i * M + j;
                    }
                }
            }
        }
    }
    vector<pair<int, int>> que;
    vector<vector<bool>> used(N, vector<bool>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '*') continue;
            if (match[i * M + j] == -1) {
                ans[i][j] = 'C';
                used[i][j] = true;
                que.emplace_back(i, j);
            }
        }
    }
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    for (int it = 0; it < que.size(); ++it) {
        int x = que[it].first;
        int y = que[it].second;
        for (int k = 0; k < 4; ++k) {
            if (x + dx[k] < 0 || x + dx[k] >= N) continue;
            if (y + dy[k] < 0 || y + dy[k] >= M) continue;
            if (grid[x + dx[k]][y + dy[k]] == '*') continue;
            int v = (x + dx[k]) * M + (y + dy[k]);
            if (!used[x + dx[k]][y + dy[k]]) {
                used[x + dx[k]][y + dy[k]] = true;
                int u = match[v];
                ans[u / M][u % M] = 'C';
                que.emplace_back(u / M, u % M);
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (match[i * M + j] != -1 && ((i + j) & 1)) {
                int v = match[i * M + j];
                if (used[i][j] || used[v / M][v % M]) continue;
                ans[i][j] = 'C';
                used[i][j] = true;
                used[v / M][v % M] = true;
            }
        }
    }
    for (int i = 0; i < N; ++i) cout << ans[i] << "\n";
}
