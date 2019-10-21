#include <bits/stdc++.h>
using namespace std;
 
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ks = 0;
    int dx, dy, n, q; while (cin >> dx >> dy >> n >> q) {
        if ((dx|dy|n|q) == 0) break;
        ++ks;
        vector<pair<int, int>> pos(n);
        for (int i = 0; i < n; ++i) {
            int x, y; cin >> x >> y;
            pos[i] = make_pair(x + y, x - y);
        }
        vector<vector<int>> mp(dx + dy + 10, vector<int>(dx + dy + 10, 0));
        auto add = [&] (int xl, int yl, int xr, int yr) {
            yl += dy + 1, yr += dy + 1;
            // cout << xl << ' ' << yl << ' ' << xr << ' ' << yr << endl;
            xl = max(xl, 0); yl = max(yl, 0);
            xr = min(xr, (int)mp.size() - 2); yr = min(yr, (int)mp[0].size() - 2);
            // cout << xl << ' ' << yl << ' ' << xr << ' ' << yr << endl;
            // cout << endl;
            mp[xl][yl]++; mp[xl][yr + 1]--;
            mp[xr + 1][yl]--; mp[xr + 1][yr + 1]++;
        };
        auto build = [&] () {
            for (int i = 0; i < (int)mp.size(); ++i) {
                for (int j = 0; j < (int)mp[0].size(); ++j) {
                    if (i) mp[i][j] += mp[i - 1][j];
                    if (j) mp[i][j] += mp[i][j - 1];
                    if (i && j) mp[i][j] -= mp[i - 1][j - 1];
                }
            }
        };
        auto getans = [&] () {
            int mxcvr = 0;
            int ax = 1, ay = 1;
            for (int i = 0; i < (int)mp.size(); ++i) for (int j = 0; j < (int)mp[0].size(); ++j) {
                int xx = i, yy = j - (dy + 1);
                if ((xx + yy) % 2) continue;
                int cvr = mp[i][j];
                int x = (xx + yy) / 2, y = (xx - yy) / 2;
                if (x >= 1 && x <= dx && y >= 1 && y <= dy); else continue;
                if (cvr > mxcvr) {
                    mxcvr = cvr;
                    ax = x, ay = y;
                } else if (cvr == mxcvr) {
                    if (y < ay) {
                        ax = x; ay = y;
                    } else if (y == ay) {
                        if (x < ax) {
                            ax = x;
                        }
                    }
                }
            }
            return make_pair(mxcvr, make_pair(ax, ay));
        };
        cout << "Case " << ks << ":\n";
        while (q--) {
            int d; cin >> d;
            for (auto &v : mp) for (int &i : v) i = 0;
            for (int i = 0; i < n; ++i) {
                int x, y; tie(x, y) = pos[i];
                add(x - d, y - d, x + d, y + d);
            }
            // cout << "finish add " << endl;
            build();
            pair<int, pair<int, int>> ans = getans();
            cout << ans.first << " (" << ans.second.first << "," << ans.second.second << ")\n";
        }
    }
}
