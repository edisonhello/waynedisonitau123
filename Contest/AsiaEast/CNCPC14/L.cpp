#include <bits/stdc++.h>
using namespace std;

string mp[105][105];
int d[105][105][105];

int main() {
    int z, x, y; 
    while (cin >> z >> x >> y) {

        memset(d, 0x3f, sizeof(d));
        

        queue<tuple<int, int, int>> q;
        for (int i = 0; i < z; ++i) {
            for (int j = 0; j < x; ++j) {
                cin >> mp[i][j];
                for (int k = 0; k < y; ++k) {
                    if (mp[i][j][k] == '@') {
                        q.emplace(i, j, k);
                        d[i][j][k] = 0;
                    }
                }
            }
        }

        while (q.size()) {
            auto [i, j, k] = q.front(); q.pop();

            for (auto [di, dj, dk] : vector<tuple<int, int, int>>{{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}}) {
                int ni = i + di, nj = j + dj, nk = k + dk;

                if (ni < 0 || ni >= z || nj < 0 || nj >= x || nk < 0 || nk >= y) continue;
                if (d[ni][nj][nk] > d[i][j][k] + 1) {
                    d[ni][nj][nk] = d[i][j][k] + 1;
                    q.emplace(ni, nj, nk);
                }
            }
        }

        int L = 0, R = 350;
        while (L < R) {
            int M = (L + R) >> 1;

            bool ok = false;
            bool out = false;

            int mnw = -1000, mxw = 1000, 
                mnx = -1000, mxx = 1000,
                mny = -1000, mxy = 1000,
                mnz = -1000, mxz = 1000;
            for (int i = 0; i < z; ++i) {
                for (int j = 0; j < x; ++j) {
                    for (int k = 0; k < y; ++k) {
                        if (mp[i][j][k] == '*') {
                            if (d[i][j][k] <= M) continue;
                            out = true;
                            int w = i + j + k;
                            int x = i + j - k;
                            int y = i - j + k;
                            int z = i - j - k;
                            mnw = max(mnw, w - M);
                            mnx = max(mnx, x - M);
                            mny = max(mny, y - M);
                            mnz = max(mnz, z - M);
                            mxw = min(mxw, w + M);
                            mxx = min(mxx, x + M);
                            mxy = min(mxy, y + M);
                            mxz = min(mxz, z + M);
                        }
                    }
                }
            }

            if (!out) ok = true;
            else {

                // cerr << mnw << ' ' << mxw << ' ' << mnx << ' ' << mxx << ' ' << mny << ' ' << mxy << ' ' << mnz << ' ' << mxz << endl;

                for (int i = 0; i < z; ++i) {
                    for (int j = 0; j < x; ++j) {
                        for (int k = 0; k < y; ++k) {
                            if (mp[i][j][k] == '.') {
                                int w = i + j + k;
                                int x = i + j - k;
                                int y = i - j + k;
                                int z = i - j - k;
                                // cerr << "at " << w << ' ' << x << ' ' << y << ' ' << z << endl;
                                if (mnw <= w && w <= mxw &&
                                    mnx <= x && x <= mxx &&
                                    mny <= y && y <= mxy &&
                                    mnz <= z && z <= mxz) ok = true;
                            }
                        }
                    }
                }
            }

            if (ok) R = M;
            else L = M + 1;
        }

        cout << L << endl;

    }
}

