#include <bits/stdc++.h>
using namespace std;

#define State array<array<int, 6>, 6>

pair<int, int> Hash(const State &x) {
    int v1 = 0, v2 = 0;
    for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) {
        v1 = (v1 * 123ll + x[i][j]) % 1000000007;
        v2 = (v2 * 7902131ll + x[i][j]) % 1000000009;
    }
    return make_pair(v1, v2);
}

int main() {
    State now;
    for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) cin >> now[i][j];
    queue<pair<State, int>> q; q.emplace(now, 0);
    set<pair<int, int>> vis; vis.insert(Hash(now));

    set<int> carid;
    for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) carid.insert(now[i][j]);
    carid.erase(0);

    while (q.size()) {
        State now; int step;
        tie(now, step) = q.front(); q.pop();

        if (now[2][5] == 1) {
            cout << step + 2 << '\n';
            exit(0);
        }

        if (step >= 8) continue;

        // cout << "step = " << step << ", state = ";
        // for (int i = 0; i < 6; ++i) {
        //     for (int j = 0; j < 6; ++j) {
        //         cout << now[i][j] << ' ';
        //     }
        //     cout << endl;
        // }

        auto update = [&] (State s) {
            auto t = Hash(s);
            if (vis.count(t)) return;
            vis.insert(t);
            q.emplace(s, step + 1);
        };

        State backup = now;

        set<int> ign;
        for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) {
            if (ign.count(now[i][j])) continue;
            ign.insert(now[i][j]);
            if (i < 5) {
                if (now[i][j] == now[i + 1][j]) {
                    if (i < 4 && now[i + 1][j] == now[i + 2][j]) { //length 3
                        if (i < 3 && now[i + 3][j] == 0) {
                            now[i + 3][j] = now[i + 2][j];
                            now[i][j] = 0;
                            update(now);
                            now = backup;
                        }
                        if (i > 0 && now[i - 1][j] == 0) {
                            now[i - 1][j] = now[i][j];
                            now[i + 2][j] = 0;
                            update(now);
                            now = backup;
                        }
                    } else { //length 2
                        if (i < 4 && now[i + 2][j] == 0) {
                            now[i + 2][j] = now[i + 1][j];
                            now[i][j] = 0;
                            update(now);
                            now = backup;
                        }
                        if (i > 0 && now[i - 1][j] == 0) {
                            now[i - 1][j] = now[i][j];
                            now[i + 1][j] = 0;
                            update(now);
                            now = backup;
                        }
                    }
                }
            } 
            if (j < 5) {
                if (now[i][j] == now[i][j + 1]) {
                    if (j < 4 && now[i][j + 1] == now[i][j + 2]) { //length 3
                        if (j < 3 && now[i][j + 3] == 0) {
                            now[i][j + 3] = now[i][j + 2];
                            now[i][j] = 0;
                            update(now);
                            now = backup;
                        }
                        if (j > 0 && now[i][j - 1] == 0) {
                            now[i][j - 1] = now[i][j];
                            now[i][j + 2] = 0;
                            update(now);
                            now = backup;
                        }
                    } else { //length 2
                        if (j < 4 && now[i][j + 2] == 0) {
                            now[i][j + 2] = now[i][j + 1];
                            now[i][j] = 0;
                            update(now);
                            now = backup;
                        }
                        if (j > 0 && now[i][j - 1] == 0) {
                            now[i][j - 1] = now[i][j];
                            now[i][j + 1] = 0;
                            update(now);
                            now = backup;
                        }
                    }
                }
            }
        }
    }

    cout << -1 << endl;
}
