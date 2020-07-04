#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev, w;
    Edge(int a, int b, int c, int d) : to(a), cap(b), rev(c), w(d) {}
};

vector<int> Solve(vector<vector<int>> a) {
    int n = a.size();
    vector<vector<Edge>> g(2 * n + 2);

    auto AddEdge = [&](int u, int v, int c, int w) {
        g[u].emplace_back(v, c, (int)g[v].size() - 0, +w);
        g[v].emplace_back(u, 0, (int)g[u].size() - 1, -w);
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            AddEdge(i, j + n, 1, a[i][j]);
        }
        AddEdge(n + n, i, 1, 0);
        AddEdge(i + n, n + n + 1, 1, 0);
    }

    constexpr int kInf = 1'000'000'000;
    const int m = 2 * n + 2;
    vector<int> dist(m, -kInf);
    vector<bool> inq(m);
    vector<int> pv(m), ed(m);
    int src = 2 * n, dst = 2 * n + 1;
    while (true) {
        fill(dist.begin(), dist.end(), -kInf);
        fill(inq.begin(), inq.end(), false);
        dist[src] = 0;
        vector<int> que(1, src);
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            inq[x] = false;
            for (int i = 0; i < g[x].size(); ++i) {
                const Edge &e = g[x][i];
                if (e.cap == 0) continue;
                if (dist[e.to] < dist[x] + e.w) {
                    dist[e.to] = dist[x] + e.w;
                    pv[e.to] = x;
                    ed[e.to] = i;
                    if (!inq[e.to]) {
                        inq[e.to] = true;
                        que.push_back(e.to);
                    }
                }
            }
        }
        if (dist[dst] == -kInf) break;
        int dlt = kInf;
        for (int x = dst; x != src; x = pv[x]) {
            dlt = min(dlt, g[pv[x]][ed[x]].cap);
        }
        for (int x = dst; x != src; x = pv[x]) {
            Edge &e = g[pv[x]][ed[x]];
            e.cap -= dlt;
            g[e.to][e.rev].cap += dlt;
        }
    }
    vector<int> match(n, -1);
    for (int i = 0; i < n; ++i) {
        for (auto e : g[i]) {
            if (e.to >= n && e.to < n + n && e.cap == 0) {
                match[i] = e.to - n;
            }
        }
    }
    return match;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    auto z = a;

    vector<int> match = Solve(a);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i][match[i]];
    }
    // cerr << "match = ";
    // for (int i = 0; i < n; ++i) {
    //     cerr << match[i] << " ";
    // }
    // cerr << endl;
    vector<vector<pair<int, int>>> g(n + n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i].emplace_back(j + n, -a[i][j]);
            if (j == match[i]) {
                g[j + n].emplace_back(i, a[i][j]);
            }
        }
        g[i].emplace_back(n + n, 0);
        g[n + n].emplace_back(i + n, 0);
    }
    vector<int> dist(n + n + 1, 1e9);
    dist[n + n] = 0;
    vector<bool> inq(n + n + 1);
    vector<int> que(1, n + n);
    for (int it = 0; it < que.size(); ++it) {
        int x = que[it];
        inq[x] = false;
        for (auto e : g[x]) {
            if (dist[e.first] > dist[x] + e.second) {
                dist[e.first] = dist[x] + e.second;
                if (!inq[e.first]) {
                    inq[e.first] = true;
                    que.push_back(e.first);
                }
            }
        }
    }
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) x[i] = dist[i];
    for (int i = 0; i < n; ++i) y[i] = -dist[i + n];
    for (int i = 0; i < n; ++i) assert(x[i] >= 0);
    for (int i = 0; i < n; ++i) assert(y[i] >= 0);
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         if (j == match[i]) continue;
    //         x[i] = max(x[i], a[i][j]);
    //     } 
    //     for (int j = 0; j < n; ++j) {
    //         a[i][j] -= x[i];
    //     }
    //     int g = a[i][match[i]];
    //     y[match[i]] = g;
    //     for (int j = 0; j < n; ++j) {
    //         a[j][match[i]] -= g;
    //     }
    //     // for (
    //     // if (a[i][match[i]] < 0) {
    //     //     int g = -a[i][match[i]];
    //     //     y[match[i]] -= g;
    //     //     for (int j = 0; j < n; ++j) {
    //     //         a[j][match[i]] += g;
    //     //     }
    //     // }
    // }
    vector<vector<int>> b(n, vector<int>(n));
    int bsum = 0;
    // cerr << "x = ";
    // for (int i = 0; i < n; ++i) cerr << x[i] << " "; cerr << endl;
    // cerr << "y = ";
    // for (int i = 0; i < n; ++i) cerr << y[i] << " "; cerr << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            b[i][j] = x[i] + y[j];
            assert(b[i][j] >= z[i][j]);
            bsum += b[i][j];
        }
    }
    // cerr << "b = " << endl;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) cerr << b[i][j] << " ";
    //     cerr << "\n";
    // }
    assert(bsum == sum * n);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            assert(b[i][j] + b[i + 1][j + 1] == b[i][j + 1] + b[i + 1][j]);
        }
    }
    cout << bsum << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << b[i][j] << " ";
        cout << "\n";
    }
    return 0;
}

