#include <bits/stdc++.h>
using namespace std;

vector dx{1, 0, -1, 0};
vector dy{0, 1, 0, -1};

int main() {
    int n, m, k, q; cin >> n >> m >> k >> q;
    set<pair<int, int>> hole;
    vector<vector<int>> pre(n + 2, vector<int>(m + 2, 0));

    while (k--) {
        int x, y; cin >> x >> y;
        hole.insert(make_pair(x, y));
        ++pre[x][y];
    }

    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
    }

    map<pair<int, int>, int> pid;
    vector<pair<int, int>> pt;

    for (auto [x, y] : hole) {
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (hole.count(make_pair(nx, ny))) continue;
            if (pid.find(make_pair(nx, ny)) != pid.end()) continue;
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            int z = pid.size();
            pid[make_pair(nx, ny)] = z;
            pt.push_back(make_pair(nx, ny));
        }
    }

    // cerr << "pt: " << endl;
    // for (int i = 0; i < (int)pt.size(); ++i) cerr << "i = " << i << ": " << pt[i].first << ' ' << pt[i].second << endl;

    int nn = pt.size();
    vector<vector<int>> d(nn, vector<int>(nn, 1000000000));

    auto calc = [&] (int xa, int ya, int xb, int yb) {
        int mxx = max(xa, xb);
        int mxy = max(ya, yb);
        int mnx = min(xa, xb);
        int mny = min(ya, yb);

        return pre[mxx][mxy] - pre[mnx - 1][mxy] - pre[mxx][mny - 1] + pre[mnx - 1][mny - 1];
    };

    auto getdist = [&] (int xa, int ya, int xb, int yb) {
        int c = calc(xa, ya, xb, yb);

        if (xa == xb || ya == yb) {
            if (c < 1) return abs(xa - xb) + abs(ya - yb);
        } else {
            if (c < 2) return abs(xa - xb) + abs(ya - yb);
        }
        return 500000000;
    };

    for (int i = 0; i < nn; ++i) {
        for (int j = i + 1; j < nn; ++j) {
            auto [xa, ya] = pt[i];
            auto [xb, yb] = pt[j];
            
            d[i][j] = d[j][i] = getdist(xa, ya, xb, yb);
        }
    }

    for (int k = 0; k < nn; ++k) for (int i = 0; i < nn; ++i) for (int j = 0; j < nn; ++j) 
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    while (q--) {
        int sx, sy, tx, ty; cin >> sx >> sy >> tx >> ty;
        if (calc(sx, sy, sx, sy) || calc(tx, ty, tx, ty)) {
            cout << -1 << '\n';
            continue;
        }

        int mn = getdist(sx, sy, tx, ty);
        // cerr << "init mn " << mn << endl;
        int possmin = abs(sx - tx) + abs(sy - ty);

        vector<pair<int, int>> sto, tto;
        for (int i = 0; i < nn; ++i) {
            auto [xx, yy] = pt[i];
            int d = getdist(sx, sy, xx, yy);
            if (d < 500000000) sto.emplace_back(i, d);
        }
        for (int i = 0; i < nn; ++i) {
            auto [xx, yy] = pt[i];
            int d = getdist(tx, ty, xx, yy);
            if (d < 500000000) tto.emplace_back(i, d);
        }

        for (auto [i, d1] : sto) {
            for (auto [j, d2] : tto) {
                mn = min(mn, d1 + d2 + d[i][j]);
                if (mn == possmin) break;
            }
        }

        if (mn >= 500000000) mn = -1;

        cout << mn << '\n';
    }

}

