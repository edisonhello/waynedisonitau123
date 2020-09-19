
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    int64_t T;
    cin >> N >> T;
    vector<int> x(N), y(N), d(N);
    vector<int> dir(256);
    dir['U'] = 0;
    dir['D'] = 2;
    dir['L'] = 1;
    dir['R'] = 3;
    map<int, vector<pair<int, int>>> Xs, Ys;
    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
        char c;
        cin >> c;
        d[i] = dir[c];
        Xs[x[i]].emplace_back(y[i], i);
        Ys[y[i]].emplace_back(x[i], i);
    }
    for (auto &it : Xs) {
        auto &V = it.second;
        sort(V.begin(), V.end());
    }
    for (auto &it : Ys) {
        auto &V = it.second;
        sort(V.begin(), V.end());
    }
    vector<vector<int64_t>> dist(N, vector<int64_t>(4, T + 1));
    vector<vector<bool>> vis(N, vector<bool>(4));
    vector<int64_t> trigger(N, T + 1);
    dist[0][d[0]] = 0;
    trigger[0] = 0;
    priority_queue<pair<int64_t, pair<int, int>>> pq;
    pq.emplace(0, make_pair(0, d[0]));
    while (!pq.empty()) {
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        if (vis[u][v]) continue;
        if (dist[u][v] > T) break;
        vis[u][v] = true;
        if (v == 2) {
            assert(Xs.find(x[u]) != Xs.end());
            auto &V = Xs[x[u]];
            auto it = lower_bound(V.begin(), V.end(), make_pair(y[u], u));
            if (it != V.begin()) {
                int z = prev(it)->second;
                int64_t k = dist[u][v] + abs(y[z] - y[u]);
                trigger[z] = min(trigger[z], k);
                if (dist[z][v] > k) {
                    dist[z][v] = k;
                    pq.emplace(-dist[z][v], make_pair(z, v));
                }
                if (dist[z][d[z]] > k) {
                    dist[z][d[z]] = k;
                    pq.emplace(-dist[z][d[z]], make_pair(z, d[z]));
                }
            }
        }
        if (v == 0) {
            assert(Xs.find(x[u]) != Xs.end());
            auto &V = Xs[x[u]];
            auto it = lower_bound(V.begin(), V.end(), make_pair(y[u], u));
            if (next(it) != V.end()) {
                int z = next(it)->second;
                int64_t k = dist[u][v] + abs(y[z] - y[u]);
                trigger[z] = min(trigger[z], k);
                if (dist[z][v] > k) {
                    dist[z][v] = k;
                    pq.emplace(-dist[z][v], make_pair(z, v));
                }
                if (dist[z][d[z]] > k) {
                    dist[z][d[z]] = k;
                    pq.emplace(-dist[z][d[z]], make_pair(z, d[z]));
                }
            }
        }
        if (v == 1) {
            assert(Ys.find(y[u]) != Ys.end());
            auto &V = Ys[y[u]];
            auto it = lower_bound(V.begin(), V.end(), make_pair(x[u], u));
            if (it != V.begin()) {
                int z = prev(it)->second;
                int64_t k = dist[u][v] + abs(x[z] - x[u]);
                trigger[z] = min(trigger[z], k);
                if (dist[z][v] > k) {
                    dist[z][v] = k;
                    pq.emplace(-dist[z][v], make_pair(z, v));
                }
                if (dist[z][d[z]] > k) {
                    dist[z][d[z]] = k;
                    pq.emplace(-dist[z][d[z]], make_pair(z, d[z]));
                }
            }
        }
        if (v == 3) {
            assert(Ys.find(y[u]) != Ys.end());
            auto &V = Ys[y[u]];
            auto it = lower_bound(V.begin(), V.end(), make_pair(x[u], u));
            if (next(it) != V.end()) {
                int z = next(it)->second;
                int64_t k = dist[u][v] + abs(x[z] - x[u]);
                trigger[z] = min(trigger[z], k);
                if (dist[z][v] > k) {
                    dist[z][v] = k;
                    pq.emplace(-dist[z][v], make_pair(z, v));
                }
                if (dist[z][d[z]] > k) {
                    dist[z][d[z]] = k;
                    pq.emplace(-dist[z][d[z]], make_pair(z, d[z]));
                }
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        if (trigger[i] > T) {
            cout << x[i] << " " << y[i] << "\n";
        } else {
            int64_t dist = T - trigger[i];
            if (d[i] == 0) cout << x[i] << " " << y[i] + dist << "\n";
            if (d[i] == 2) cout << x[i] << " " << y[i] - dist << "\n";
            if (d[i] == 1) cout << x[i] - dist << " " << y[i] << "\n";
            if (d[i] == 3) cout << x[i] + dist << " " << y[i] << "\n";
        }
    }
}

