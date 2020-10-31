#include <bits/stdc++.h>
using namespace std;

int Matching(vector<vector<int>> g) {
    int N = g.size();
    vector<int> fa(N + 1), pre(N + 1, N), match(N + 1, N), s(N + 1), v(N + 1);

    function<int(int)> Find = [&](int x) {
        if (x == fa[x]) return x;
        return fa[x] = Find(fa[x]);
    };


    auto LCA = [&](int x, int y) {
        static int tk = 0;
        tk++;
        x = Find(x);
        y = Find(y);
        for (; ; swap(x, y)) {
            if (x != N) {
                if (v[x] == tk) return x;
                v[x] = tk;
                x = Find(pre[match[x]]);
            }
        }
    };

    auto Bfs = [&](int r) {
        iota(fa.begin(), fa.end(), 0);
        fill(s.begin(), s.end(), -1);
        queue<int> que;
        que.push(r);
        s[r] = 0;

        auto Blossom = [&](int x, int y, int L) {
            while (Find(x) != L) {
                pre[x] = y;
                y = match[x];
                if (s[y] == 1) que.push(y), s[y] = 0;
                if (fa[x] == x) fa[x] = L;
                if (fa[y] == y) fa[y] = L;
                x = pre[y];
            }
        };

        while (!que.empty()) {
            int x = que.front(); que.pop();
            for (int u: g[x]) {
                if (s[u] == -1) {
                    pre[u] = x;
                    s[u] = 1;
                    if (match[u] == N) {
                        for (int a = u, b = x, last; b != N; a = last, b = pre[a]) {
                            last = match[b];
                            match[b] = a;
                            match[a] = b;
                        }
                        return true;
                    }
                    que.push(match[u]);
                    s[match[u]] = 0;
                } else if (s[u] == 0 && Find(u) != Find(x)) {
                    int L = LCA(u, x);
                    Blossom(x, u, L);
                    Blossom(u, x, L);
                }
            }
        }
        return false;
    };

    int res = 0;
    for (int i = 0; i < N; ++i) {
        if (match[i] == N) res += Bfs(i);
    }
    return res;
}

int main() {
    while (true) {
        vector<string> grid;
        string s;
        while (getline(cin, s)) {
            if (s == "") break;
            grid.push_back(s);
        }
        if (grid.empty()) break;
        int N = grid.size(), M = grid[0].size();
        int K = N * M;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] == 'I') K++;
            }
        }
        vector<vector<int>> g(K);

        auto AddEdge = [&](int x, int y) {
            assert(x < K);
            assert(y < K);
            g[x].push_back(y);
            g[y].push_back(x);
        };

        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] == 'I') {
                    if (i > 0 && grid[i - 1][j] == 'W') {
                        AddEdge(i * M + j, (i - 1) * M + j);
                    }
                    if (i > 0 && grid[i - 1][j] == 'N') {
                        AddEdge(cnt + N * M, (i - 1) * M + j);
                    }
                    if (i + 1 < N && grid[i + 1][j] == 'W') {
                        AddEdge(i * M + j, (i + 1) * M + j);
                    }
                    if (i + 1 < N && grid[i + 1][j] == 'N') {
                        AddEdge(cnt + N * M, (i + 1) * M + j);
                    }
                    if (j > 0 && grid[i][j - 1] == 'W') {
                        AddEdge(i * M + j, i * M + (j - 1));
                    }
                    if (j > 0 && grid[i][j - 1] == 'N') {
                        AddEdge(cnt + N * M, i * M + (j - 1));
                    }
                    if (j + 1 < M && grid[i][j + 1] == 'W') {
                        AddEdge(i * M + j, i * M + (j + 1));
                    }
                    if (j + 1 < M && grid[i][j + 1] == 'N') {
                        AddEdge(cnt + N * M, i * M + (j + 1));
                    }
                    AddEdge(i * M + j, cnt + N * M);
                    cnt++;
                }
            }
        }
        cout << Matching(g) - (K - N * M) << "\n";
    }
}
