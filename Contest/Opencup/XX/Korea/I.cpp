#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;

    constexpr int64_t kInf = 1'000'000'000'000;
    vector<vector<int64_t>> dist(n, vector<int64_t>(n, kInf));
    vector<vector<int64_t>> ed(n, vector<int64_t>(n, kInf));
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    while (m--) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        u--, v--;
        dist[u][v] = min(dist[u][v], (int64_t)w);
        dist[v][u] = min(dist[v][u], (int64_t)w);
        ed[u][v] = ed[v][u] = w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }


    vector<vector<int>> gord(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        iota(gord[i].begin(), gord[i].end(), 0);
        sort(gord[i].begin(), gord[i].end(), [&](int a, int b) { return dist[i][a] < dist[i][b]; });
    }

    auto Solve2 = [&](int u, int v, int w) {
        vector<pair<int64_t, int64_t>> ds(n);
        for (int i = 0; i < n; ++i) ds[i] = make_pair(dist[u][gord[u][i]], dist[v][gord[u][i]]);
        vector<int64_t> suff(n);
        for (int i = n - 1; i >= 0; --i) {
            suff[i] = ds[i].second;
            if (i + 1 < n) suff[i] = max(suff[i], suff[i + 1]);
        }
        int64_t res = kInf;
        for (int i = 0; i < n - 1; ++i) {
            int64_t a = ds[i].first;
            int64_t b = suff[i + 1];
            if (abs(a - b) <= w) res = min(res, a + b + w);
        }
        return res;
    };

    int64_t ans = kInf;
    // for (int root = 0; root < n; ++root) ans = min(ans, Solve(root));
    // cout << ans << "\n";
    int fu = -1, fv = -1, fw = -1;
    for (int i = 0; i < n; ++i) {
        for (auto e : g[i]) {
            int u = e.first, w = e.second;
            int64_t res = Solve2(i, u, w);
            if (res < ans) {
                ans = res;
                fu = i, fv = u;
                fw = w;
            }
        }
    }
    cout << ans << "\n";
    int u = fu, v = fv, w = fw;;
    vector<tuple<int64_t, int64_t, int>> ds(n);
    for (int i = 0; i < n; ++i) ds[i] = make_tuple(dist[u][gord[u][i]], dist[v][gord[u][i]], gord[u][i]);
    vector<int64_t> suff(n);
    for (int i = n - 1; i >= 0; --i) {
        suff[i] = get<1>(ds[i]);
        if (i + 1 < n) suff[i] = max(suff[i], suff[i + 1]);
    }

    auto PrintAnswer = [&](int u, int v, int w, int64_t a, int64_t b) {
        a <<= 1, b <<= 1, w <<= 1;
        int k = (b - a + w) / 2;
        assert(k >= 0 && k <= w);
        // printf("u = %d v = %d w = %d\n", u, v, w);
        if (k == 0 || k == w) {
            if (k == w) swap(u, v);
            vector<int> ord(n);
            iota(ord.begin(), ord.end(), 0);
            sort(ord.begin(), ord.end(), [&](int i, int j) { return dist[u][i] < dist[u][j]; });
            vector<int> pv(n, -1);
            for (int i = 1; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[u][ord[j]] + ed[ord[j]][ord[i]] == dist[u][ord[i]]) {
                        pv[ord[i]] = ord[j];
                    }
                }
            }
            // assert(pv[v] == u);
            for (int i = 0; i < n; ++i) {
                if (pv[i] >= 0) printf("%d %d\n", pv[i] + 1, i + 1);
            }
            return;
        }
        vector<vector<int64_t>> ked(n + 1, vector<int64_t>(n + 1, kInf));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) ked[i][j] = ed[i][j] * 2;
        }
        ked[u][v] = ked[v][u] = kInf;
        ked[n][u] = ked[u][n] = k;
        ked[n][v] = ked[v][n] = w - k;
        vector<int64_t> ds(n + 1, kInf);
        ds[n] = 0;
        priority_queue<pair<int64_t, int>> pq;
        vector<int> pv(n + 1, -1), used(n + 1, 0);
        pq.emplace(0, n);
        while (!pq.empty()) {
            int x = pq.top().second;
            pq.pop();
            if (used[x]++) continue;
            for (int i = 0; i <= n; ++i) {
                if (ds[i] > ds[x] + ked[x][i]) {
                    ds[i] = ds[x] + ked[x][i];
                    pv[i] = x;
                    pq.emplace(-ds[i], i);
                }
            }
        }
        set<pair<int, int>> ed;
        for (int i = 0; i <= n; ++i) {
            if (pv[i] >= 0) ed.insert(minmax(i, pv[i]));
        }
        assert(ed.count(minmax(u, n)));
        assert(ed.count(minmax(v, n)));
        ed.erase(minmax(u, n));
        ed.erase(minmax(v, n));
        ed.insert(minmax(u, v));
        for (auto it : ed) cout << it.first + 1 << ' ' << it.second + 1 << "\n";
    };

    for (int i = 0; i < n - 1; ++i) {
        int64_t a = get<0>(ds[i]);
        int64_t b = suff[i + 1];
        if (abs(a - b) <= w) {
            if (a + b + fw == ans) {
                PrintAnswer(u, v, w, a, b);
                exit(0);
            }
        }
    }
    assert(false);
    return 0;
}

