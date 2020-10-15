#include <bits/stdc++.h>
using namespace std;

int djs[300005];
int sz[300005];
vector<int> mem[300005];

int F(int x) {
    return djs[x] == x ? x : djs[x] = F(djs[x]);
}

void U(int x, int y) {
    x = F(x);
    y = F(y);
    if (x == y) return;
    djs[x] = y;
    sz[y] += sz[x];
}

vector<pair<int, int>> g[300005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<tuple<int, int, int>> eg;
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        eg.emplace_back(u, v, w);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    sort(eg.begin(), eg.end(), [&] (const auto &a, const auto &b) {
        return get<2>(a) > get<2>(b);
    });

    for (int i = 1; i <= n; ++i) djs[i] = i;
    for (int i = 1; i <= n; ++i) sz[i] = 1;
    for (int i = 1; i <= n; ++i) mem[i].push_back(i);

    long long ans = 0;

    vector<tuple<int, int, int>> mst;
    for (auto &tp : eg) {
        int u, v, w; tie(u, v, w) = tp;

        if (F(u) == F(v)) continue;
        int uu = F(u);
        int vv = F(v);
        // cerr << "u v w " << u << ' ' << v << ' ' << w << ' ' << sz[uu] << ' ' << sz[vv] << ' ' << w << endl;
        ans += 1ll * sz[uu] * sz[vv] * w;

        if (sz[uu] < sz[vv]) swap(uu, vv);

        for (auto &pp : g[vv]) {
            int to = pp.first;
            if (F(to) == uu) {
                if (pp.second != w) {
                    cout << -1 << endl;
                    exit(0);
                }
            } else {
                g[uu].emplace_back(pp);
            }
        }

        djs[vv] = uu;
        sz[uu] += sz[vv];
    }

    vector<int> szs;
    for (int i = 1; i <= n; ++i) if (F(i) == i) szs.push_back(sz[i]);

    long long sum = 0;
    for (int i : szs) {
        sum += 1ll * i * (n - i);
    }
    // cerr << "sum = " << sum << endl;

    ans += sum / 2;

    cout << ans << endl;

}

