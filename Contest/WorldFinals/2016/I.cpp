#include <bits/stdc++.h>
using namespace std;

namespace simplex {

constexpr double kInf = 1E9;
constexpr double kEps = 1E-9;

vector<double> Solve(const vector<vector<double>>& A, const vector<double>& B, const vector<double>& C) {
    int M = B.size(), N = C.size();
    vector<vector<double>> D(M + 2, vector<double>(N + 2));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            D[i][j] = A[i][j];
        }
    }
    vector<int> p(M), q(N + 1);
    for (int i = 0; i < M; ++i) {
        p[i] = N + i;
        D[i][N] = -1;
        D[i][N + 1] = B[i];
    }
    for (int i = 0; i < N; ++i) {
        q[i] = i;
        D[M][i] = -C[i];
    }
    q[N] = -1;
    D[M + 1][N] = 1;
    int r = 0;
    for (int i = 1; i < M; ++i) {
        if (D[i][N + 1] < D[r][N + 1]) r = i;
    }

    auto Pivot = [&](int r, int s) {
        double inv = 1 / D[r][s];
        for (int i = 0; i < M + 2; ++i) {
            for (int j = 0; j < N + 2; ++j) {
                if (i != r && j != s) {
                    D[i][j] -= D[r][j] * D[i][s] * inv;
                }
            }
        }
        for (int i = 0; i < M + 2; ++i) {
            if (i != r) D[i][s] *= -inv;
        }
        for (int j = 0; j < N + 2; ++j) {
            if (j != s) D[r][j] *= inv;
        }
        D[r][s] = inv;
        swap(p[r], q[s]);
    };

    auto Phase = [&](int z) {
        int x = M + z;
        while (true) {
            int s = -1;
            for (int i = 0; i <= N; ++i) {
                if (!z && q[i] == -1) continue;
                if (s == -1 || D[x][i] < D[x][s]) s = i;
            }
            if (D[x][s] > -kEps) return true;
            int r = -1;
            for (int i = 0; i < M; ++i) {
                if (D[i][s] < kEps) continue;
                if (r == -1 || D[i][N + 1] / D[i][s] < D[r][N + 1] / D[r][s]) r = i;
            }
            if (r == -1) return false;
            Pivot(r, s);
        }
    };

    if (D[r][N + 1] < -kEps) {
        Pivot(r, N);
        Phase(1);
        for (int i = 0; i < M; ++i) {
            if (p[i] == -1) {
                int s = min_element(D[i].begin(), D[i].end() - 1) - D[i].begin();
                Pivot(i, s);
            }
        }
    }
    Phase(0);
    vector<double> x(N);
    for (int i = 0; i < M; ++i) {
        if (p[i] < N) x[p[i]] = D[i][N + 1];
    }
    return x;
}

}  // namespace simplex

int main() {
    int N;
    cin >> N;
    vector<vector<int>> g(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) cin >> g[i][j];
    }
    vector<vector<int>> id(N, vector<int>(N, -1));
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j || g[i][j] == -1) continue;
            id[i][j] = cnt++;
        }
    }
    int R;
    cin >> R;
    vector<vector<pair<int, int>>> obs(N);
    for (int i = 0; i < R; ++i) {
        int s, d, t;
        cin >> s >> d >> t;
        obs[s].emplace_back(d, t);
    }
    vector<vector<double>> A;
    vector<double> B;
    for (int i = 0; i < cnt; ++i) {
        vector<double> cf(cnt);
        cf[i] = 1;
        A.push_back(cf);
        B.push_back(2);
        cf[i] = -1;
        A.push_back(cf);
        B.push_back(-1);
    }
    for (int i = 0; i < N; ++i) {
        constexpr int kInf = 1'000'000'000;
        vector<int> dist(N, kInf);
        priority_queue<pair<int, int>> pq;
        vector<int> from(N, -1);
        vector<bool> vis(N);
        dist[i] = 0;
        pq.emplace(0, i);
        while (!pq.empty()) {
            int x = pq.top().second;
            pq.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (int u = 0; u < N; ++u) {
                if (g[x][u] == -1) continue;
                if (dist[u] > dist[x] + g[x][u]) {
                    from[u] = x;
                    dist[u] = dist[x] + g[x][u];
                    pq.emplace(-dist[u], u);
                }
            }
        }
        for (auto [d, t] : obs[i]) {
            int x = d;
            vector<double> cf(cnt);
            while (x != i) {
                cf[id[from[x]][x]] = g[from[x]][x];
                x = from[x];
            }
            A.push_back(cf);
            B.push_back(t);
            for (double& c : cf) c = -c;
            A.push_back(cf);
            B.push_back(-t);
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int s, d;
        cin >> s >> d;
        constexpr int kInf = 1'000'000'000;
        vector<int> dist(N, kInf);
        priority_queue<pair<int, int>> pq;
        vector<int> from(N, -1);
        vector<bool> vis(N);
        dist[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty()) {
            int x = pq.top().second;
            pq.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (int u = 0; u < N; ++u) {
                if (g[x][u] == -1) continue;
                if (dist[u] > dist[x] + g[x][u]) {
                    from[u] = x;
                    dist[u] = dist[x] + g[x][u];
                    pq.emplace(-dist[u], u);
                }
            }
        }
        int x = d;
        vector<double> C(cnt);
        while (x != s) {
            C[id[from[x]][x]] = g[from[x]][x];
            x = from[x];
        }
        vector<double> ans = simplex::Solve(A, B, C);
        double X = 0;
        for (int i = 0; i < cnt; ++i) X += ans[i] * C[i];
        for (auto& c : C) c = -c;
        ans = simplex::Solve(A, B, C);
        double Y = 0;
        for (int i = 0; i < cnt; ++i) Y += ans[i] * C[i];
        cout << fixed << setprecision(20) << s << " " << d << " " << -Y << " " << X << "\n";
    }
}

