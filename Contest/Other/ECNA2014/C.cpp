#include <bits/stdc++.h>
using namespace std;

int Solve() {
    vector<vector<int>> B(5, vector<int>(5));
    vector<pair<pair<int, int>, pair<int, int>>> pos(13);
    vector<vector<bool>> used(7, vector<bool>(7));
    int fuck = -1;
    for (int t = 0; t < 13; ++t) {
        string c;
        cin >> c;
        if (c == "V" || c == "H") {
            int x, y;
            cin >> x >> y;
            bool found = false;
            for (int i = 0; !found && i < 5; ++i) {
                for (int j = 0; !found && j < 5; ++j) {
                    if (B[i][j] == 0) {
                        if (c == "V" && i + 1 < 5 && B[i + 1][j] == 0) {
                            B[i][j] = x;
                            B[i + 1][j] = y;
                            pos[t] = {{i, j}, {i + 1, j}};
                            found = true;
                            break;
                        }
                        if (c == "H" && j + 1 < 5 && B[i][j + 1] == 0) {
                            B[i][j] = x;
                            B[i][j + 1] = y;
                            pos[t] = {{i, j}, {i, j + 1}};
                            found = true;
                            break;
                        }
                    }
                }
            }
            assert(!used[x][y]);
            assert(!used[y][x]);
            used[x][y] = true;
            used[y][x] = true;
            assert(found);
        }
        if (c == "S") {
            fuck = t;
            int x;
            cin >> x;
            bool found = false;
            for (int i = 0; !found && i < 5; ++i) {
                for (int j = 0; !found && j < 5; ++j) {
                    if (B[i][j] == 0) {
                        B[i][j] = x;
                        found = true;
                        break;
                    }
                }
            }
            assert(found);
        }
        // for (int i = 0; i < 5; ++i) {
        //     for (int j = 0; j < 5; ++j) cout << B[i][j];
        //     cout << endl;
        // }
        // cout << endl;
    }

    auto Eval = [&](vector<vector<int>> B) {
        int res = 0, yahtzee = 0;

        auto Calc = [&](vector<int> V) {
            vector<int> cnt(7);
            for (int u : V) cnt[u]++;
            for (int i = 1; i <= 6; ++i) {
                if (cnt[i] == 5) {
                    yahtzee++;
                    return 0;
                }
            }
            bool X = false, Y = false;
            for (int i = 1; i <= 6; ++i) {
                if (cnt[i] == 3) X = true;
                if (cnt[i] == 2) Y = true;
            }
            if (X && Y) return 25;
            for (int i = 1; i <= 6; ++i) {
                if (cnt[i] == 4) return i * 4;
            }
            for (int i = 1; i <= 6; ++i) {
                if (cnt[i] == 3) return i * 3;
            }
            if (cnt[1] && cnt[2] && cnt[3] && cnt[4] && cnt[5]) return 40;
            if (cnt[2] && cnt[3] && cnt[4] && cnt[5] && cnt[6]) return 40;
            if (cnt[1] && cnt[2] && cnt[3] && cnt[4]) return 30;
            if (cnt[2] && cnt[3] && cnt[4] && cnt[5]) return 30;
            if (cnt[3] && cnt[4] && cnt[5] && cnt[6]) return 30;
            return 0;
        };

        for (int i = 0; i < 5; ++i) {
            res += Calc(B[i]);
        }
        for (int i = 0; i < 5; ++i) {
            vector<int> V(5);
            for (int j = 0; j < 5; ++j) V[j] = B[j][i];
            res += Calc(V);
        }
        vector<int> V(5);
        for (int i = 0; i < 5; ++i) V[i] = B[i][i];
        res += Calc(V);
        for (int i = 0; i < 5; ++i) V[i] = B[i][4 - i];
        res += Calc(V);
        if (yahtzee > 0) {
            res += 100 * (yahtzee - 1) + 50;
        }
        return res;
    };

    int res = Eval(B);
    // assert(res == 135);
    for (int i = 1; i <= 6; ++i) {
        for (int j = 1; j <= 6; ++j) {
            if (used[i][j]) continue;
            for (int t = 0; t < 13; ++t) {
                if (t == fuck) continue;
                auto x = pos[t].first;
                auto y = pos[t].second;
                int C = B[x.first][x.second];
                int D = B[y.first][y.second];
                B[x.first][x.second] = i;
                B[y.first][y.second] = j;
                res = max(res, Eval(B));
                // if (Eval(B) == 218) {
                //     cout << "218: i = " << i << " j = " << j << endl;
                // }
                // if (Eval(B) == 135) {
                //     cout << "135: i = " << i << " j = " << j << endl;
                // }
                // if (Eval(B) == 188) {
                //     cout << "188: i = " << i << " j = " << j << endl;
                // }
                B[x.first][x.second] = C;
                B[y.first][y.second] = D;
            }
        }
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        cout << "Case " << i + 1 << ": " << Solve() << "\n";
    }
}

