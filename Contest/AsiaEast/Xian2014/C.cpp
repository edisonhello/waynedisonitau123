#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev;

    Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

int Flow(vector<vector<Edge>> g, int S, int T) {
    int N = g.size();
    vector<int> lev(N, -1), iter(N);
    int res = 0;
    while (true) {
        fill(lev.begin(), lev.end(), -1);
        vector<int> que(1, S);
        lev[S] = 0;
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            for (Edge &e : g[x]) {
                if (e.cap > 0 && lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    que.push_back(e.to);
                }
            }
        }
        if (lev[T] == -1) break;

        auto Dfs = [&](auto dfs, int x, int f = 1E9) {
            if (x == T) return f;
            int res = 0;
            for (int &it = iter[x]; it < g[x].size(); ++it) {
                Edge &e = g[x][it];
                if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                    int p = dfs(dfs, e.to, min(f - res, e.cap));
                    res += p;
                    e.cap -= p;
                    g[e.to][e.rev].cap += p;
                }
            }
            if (res == 0) lev[x] = -1;
            return res;
        };

        fill(iter.begin(), iter.end(), 0);
        res += Dfs(Dfs, S);
    }
    return res;
}

double Solve() {
    int N;
    cin >> N;
    vector<int> p(N);
    for (int i = 0; i < N; ++i) {
        cin >> p[i];
    }
    vector<pair<int, int>> bins;
    bins.emplace_back(0, 1);
    for (int B = 1; B <= N; ++B) {
        for (int T = 1; T <= B * B; ++T) {
            int G = __gcd(B, T);
            bins.emplace_back(T / G, B / G);
        }
    }

    sort(bins.begin(), bins.end(), [&](auto X, auto Y) {
        return X.first * Y.second < X.second * Y.first;
    });

    bins.resize(unique(bins.begin(), bins.end()) - bins.begin());

    vector<int> deg(N);
    int K = N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (p[j] > p[i]) {
                deg[i]++;
                deg[j]++;
                K++;
            }
        }
    }
    vector<vector<Edge>> g(N + 2);

    auto AddBiEdge = [&](int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size());
        g[b].emplace_back(a, c, g[a].size() - 1);
    };

    auto AddEdge = [&](int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size());
        g[b].emplace_back(a, 0, g[a].size() - 1);
    };

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (p[j] > p[i]) {
                AddBiEdge(i, j, 0);
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        AddEdge(N, i, 0);
    }
    for (int i = 0; i < N; ++i) {
        AddEdge(i, N + 1, 0);
    }

    auto Check = [&](int P, int Q) {
        // cout << "Check P = " << P << " Q = " << Q << endl;
        for (int i = 0; i < N; ++i) {
            for (auto &e : g[i]) {
                if (e.to < N) e.cap = Q;
                if (e.to == N) e.cap = 0;
                if (e.to == N + 1) e.cap = K * Q + 2 * P - deg[i] * Q - 2 * Q;
            }
        }
        for (auto &e : g[N]) e.cap = K * Q;
        for (auto &e : g[N + 1]) e.cap = 0;
        int F = Flow(g, N, N + 1);
        // cout << "F = " << F << endl;
        // cout << "K = " << K << endl;
        return F < K * N * Q ? -1 : F == K * N * Q ? 0 : 1;
    };

    int ptr = 0;
    for (int d = 30; d >= 0; --d) {
        if (ptr + (1 << d) < bins.size()) {
            if (Check(bins[ptr + (1 << d)].first, bins[ptr + (1 << d)].second) < 0) {
                ptr += (1 << d);
            }
        }
    }
    ptr++;
    double res = static_cast<double>(bins[ptr].first) / bins[ptr].second;
    return res - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cout << fixed << setprecision(20) << "Case #" << tc << ": " << Solve() << "\n";
    }
}

