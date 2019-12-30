#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> g[2][100005];
vector<tuple<int, int, int>> ees;
int djs[100005];

int F(int x) {
    return x == djs[x] ? x : djs[x] = F(djs[x]);
}
void U(int x, int y) {
    djs[F(x)] = F(y);
}

int tdfs(int now, int pa, int to, int u) {
    // cerr << "tdfs " << now << " pa " << pa << endl;
    if (to == now) {
        return u;
    }
    for (auto &e : g[1][now]) if (e.first != pa) {
        int res = tdfs(e.first, now, to, e.second);
        if (res <= 1e9) {
            res = min(res, u);
            return res;
        }
    }
    return 2e9;
}

int main() {
    int n, m; cin >> n >> m;
    while (m--) {
        int ty, u, v, w; cin >> ty >> u >> v >> w;
        // cerr << "lol " << ty << ' ' << u << ' ' << v << ' ' << w << endl;
        g[ty][u].emplace_back(v, w);
        g[ty][v].emplace_back(u, w);
        ees.emplace_back(w, u, v);
    }
    sort(ees.begin(), ees.end(), greater<tuple<int, int, int>>());
    // cout << "lol" << endl;
    set<int> ans;
    for (int i = 1; i <= n; ++i) {
        bool bad = 0;
        for (int j = 1; j <= n; ++j) if (i != j) {
            int mn = tdfs(i, 0, j, 2e9);
            // cerr << "mn " << i << " to " << j << " is " << mn << endl;
            for (int k = 1; k <= n; ++k) djs[k] = k;
            for (auto &ee : ees) {
                if (get<0>(ee) <= mn) break;
                U(get<1>(ee), get<2>(ee));
            }
            if (F(i) == F(j)) bad = 1;
            // cerr << "bad = " << bad << endl;
        }
        if (!bad) ans.insert(i);
    }

    cout << ans.size() << endl;
    for (int i : ans) cout << i << ' ';
    cout << endl;
}
