#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int64_t cap;

    Edge(int a, int64_t b, int c) : to(a), cap(b), rev(c) {}
};

constexpr int kN = 1'000'000;
int gap[kN], d[kN], iter[kN];

int64_t Flow(vector<vector<Edge>> &g, const int S, const int T) {
    int N = g.size();
    fill(gap, gap + N, 0);
    fill(d, d + N, 0);
    gap[0] = N;
    vector<int> iter(N);
    int64_t res = 0;
    vector<int> que;

    auto Dfs = [&](auto dfs, int x, int64_t f = 1'000'000'000'000'000) -> int64_t {
        if (x == T) return f;
        for (int &it = iter[x]; it < g[x].size(); ++it) {
            Edge &e = g[x][it];
            if (e.cap > 0 && d[e.to] == d[x] - 1) {
                int64_t v = dfs(dfs, e.to, min<int64_t>(f, e.cap));
                if (v > 0) {
                    e.cap -= v;
                    g[e.to][e.rev].cap += v;
                    return v;
                }
            }
        }
        if (--gap[d[x]] == 0) d[x] = N;
        else d[x]++, iter[x] = 0, ++gap[d[x]];
        return 0;
    };

    while (d[S] < N) res += Dfs(Dfs, S);

    // while (true) {
    //     fill(lev.begin(), lev.end(), -1);
    //     fill(iter.begin(), iter.end(), 0);
    //     que.clear();
    //     que.push_back(S);
    //     lev[S] = 0;
    //     for (int it = 0; it < que.size(); ++it) {
    //         int x = que[it];
    //         for (Edge &e : g[x]) {
    //             if (e.cap > 0 && lev[e.to] == -1) {
    //                 lev[e.to] = lev[x] + 1;
    //                 que.push_back(e.to);
    //             }
    //         }
    //     }
    //     if (lev[T] == -1) break;

    //     auto Dfs = [&](auto dfs, int x, int64_t f = 1'000'000'000'000'000) -> int64_t {
    //         if (x == T) return f;
    //         if (f == 0) return 0;
    //         int64_t res = 0;
    //         for (int &it = iter[x]; it < g[x].size(); ++it) {
    //             Edge &e = g[x][it];
    //             if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
    //                 int64_t v = dfs(dfs, e.to, min(f - res, static_cast<int64_t>(e.cap)));
    //                 e.cap -= v;
    //                 g[e.to][e.rev].cap += v;
    //                 res += v;
    //             }
    //         }
    //         if (res == 0) lev[x] = -1;
    //         return res;
    //     };

    //     int64_t add = Dfs(Dfs, S);
    //     // cout << "add = " << add << endl;
    //     res += add;
    // }
    return res;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, M, S;
    cin >> N >> M >> S;
    vector<int> P(N);
    for (int i = 0; i < N; ++i) cin >> P[i];
    vector<vector<pair<int, int>>> g(N);
    for (int i = 0; i < M; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        g[x].emplace_back(y, w);
        g[y].emplace_back(x, w);
    }

    vector<int> s(S), c(S);
    for (int i = 0; i < S; ++i) {
        cin >> s[i] >> c[i];
        s[i]--;
    }

    vector<int> U;
    for (int i = 0; i < N; ++i) {
        if (P[i] > 0) U.push_back(i);
    }

    vector<vector<int64_t>> dist(S);

    auto Dijkstra = [&](int source) {
        vector<int64_t> d(N, 1'000'000'000'000'000);
        d[source] = 0;
        priority_queue<pair<int64_t, int>> pq;
        pq.emplace(0, source);
        vector<int> vis(N);
        while (!pq.empty()) {
            int x = pq.top().second;
            pq.pop();
            if (vis[x]++) continue;
            for (auto e : g[x]) {
                if (d[e.first] > d[x] + e.second) {
                    d[e.first] = d[x] + e.second;
                    pq.emplace(-d[e.first], e.first);
                }
            }
        }
        return d;
    };

    vector<int64_t> V(1, 0);
    for (int i = 0; i < S; ++i) {
        dist[i] = Dijkstra(s[i]);
        V.insert(V.end(), dist[i].begin(), dist[i].end());
    }

    sort(V.begin(), V.end());
    V.resize(unique(V.begin(), V.end()) - V.begin());

    vector<vector<Edge>> fg((1 << S) + S + 2);
    auto Check = [&](int64_t D) {
        for (int i = 0; i < U.size(); ++i) {
            int64_t dd = 1'000'000'000'000'000;
            for (int j = 0; j < S; ++j) {
                dd = min(dd, dist[j][U[i]]);
            }
            if (dd > D) return false;
        }
        // cout << "Check D = " << D << endl;
        for (int i = 0; i < (1 << S) + S + 2; ++i) fg[i].clear();
        auto AddEdge = [&](int a, int b, int64_t c) {
            if (c == 0) return;
            fg[a].emplace_back(b, c, fg[b].size());
            fg[b].emplace_back(a, 0, fg[a].size() - 1);
        };

        int64_t sum = accumulate(P.begin(), P.end(), 0LL);
        vector<int64_t> fs(1 << S);
        for (int i = 0; i < U.size(); ++i) {
            int mask = 0;
            for (int j = 0; j < S; ++j) {
                if (dist[j][U[i]] <= D) {
                    mask ^= (1 << j);
                }
            }
            fs[mask] += P[U[i]];
        }
        // cout << "U.size() = " << U.size() << endl;
        for (int i = 0; i < S; ++i) AddEdge((1 << S) + S, i, c[i]);
        for (int i = 0; i < (1 << S); ++i) {
            AddEdge(i + S, (1 << S) + S + 1, fs[i]);
            for (int j = 0; j < S; ++j) {
                if (i >> j & 1) {
                    AddEdge(j, i + S, 1'000'000'000'000'000);
                }
            }
        }
        return Flow(fg, (1 << S) + S, S + (1 << S) + 1) == sum;
    };

    int res = V.size() - 1;
    for (int bit = 20; bit >= 0; --bit) {
        if (res - (1 << bit) >= 0 && Check(V[res - (1 << bit)])) {
            res -= (1 << bit);
        }
    }
    cout << V[res] << "\n";
}

