#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n), ig(n);
        while (m--) {
            int u, v; cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            ig[v].push_back(u);
        }

        string team; cin >> team;
        string actor; cin >> actor;
        for (char &c : actor) c -= '0';

        auto solve1 = [&] () {
            vector<int> res(n * 6, 0);
            queue<int> q;
            auto &inq = res;

            for (int i = 0; i < n; ++i) {
                if (g[i].empty()) {
                    for (int j = 0; j < 6; ++j) {
                        if (team[j] == 'B') {
                            res[i * 6 + j] = 1;
                            q.push(i * 6 + j);
                        }
                    }
                }
            }
            
            vector<int> cnt(n * 6, 0);
            while (q.size()) {
                int nowz = q.front(); q.pop();
                int now = nowz / 6;
                int turn = nowz % 6;
                int prev = turn - 1 == -1 ? 5 : turn - 1;
                int next = turn + 1 == 6 ? 0 : turn + 1;

                if (team[prev] == 'A' && !actor[prev]) {
                    for (int i : ig[now]) {
                        int prevz = i * 6 + prev;
                        if (!inq[prevz]) {
                            res[prevz] = 1;
                            q.push(prevz);
                        }
                    }
                } else if (team[prev] == 'A' && actor[prev]) {
                    for (int i : ig[now]) {
                        int prevz = i * 6 + prev;
                        ++cnt[prevz];
                        if (cnt[prevz] == g[i].size()) {
                            res[prevz] = 1;
                            q.push(prevz);
                        }
                    }
                } else if (team[prev] == 'B' && !actor[prev]) {
                    for (int i : ig[now]) {
                        int prevz = i * 6 + prev;
                        ++cnt[prevz];
                        if (cnt[prevz] == g[i].size()) {
                            res[prevz] = 1;
                            q.push(prevz);
                        }
                    }
                } else {
                    for (int i : ig[now]) {
                        int prevz = i * 6 + prev;
                        if (!inq[prevz]) {
                            res[prevz] = 1;
                            q.push(prevz);
                        }
                    }
                }
            }

            // cerr << "solve 1 res: ";
            // for (int i = 0; i < n * 6; ++i) {
            //     cerr << res[i] << ' ';
            //     if (i % 6 == 5) cerr << ';';
            // }
            // cerr << endl;

            vector<int> ret(n, 0);
            for (int i = 0; i < n; ++i) ret[i] = res[i * 6];

            return ret;
        };

        auto solve2 = [&] () {
            vector<int> res(n * 6, 0);
            queue<int> q;
            auto &inq = res;

            for (int i = 0; i < n; ++i) {
                if (g[i].empty()) {
                    for (int j = 0; j < 6; ++j) {
                        if (team[j] == 'A') {
                            res[i * 6 + j] = 1;
                            q.push(i * 6 + j);
                        }
                    }
                }
            }
            
            vector<int> cnt(n * 6, 0);
            while (q.size()) {
                int nowz = q.front(); q.pop();
                int now = nowz / 6;
                int turn = nowz % 6;
                int prev = turn - 1 == -1 ? 5 : turn - 1;
                int next = turn + 1 == 6 ? 0 : turn + 1;
                // cerr << "q in " << now << " turn " << turn << endl;

                if (team[prev] == 'A' && !actor[prev]) {
                    for (int i : ig[now]) {
                        int prevz = i * 6 + prev;
                        ++cnt[prevz];
                        if (cnt[prevz] == g[i].size()) {
                            res[prevz] = 1;
                            // cerr << "  1: push " << i << ' ' << prev << endl;
                            q.push(prevz);
                        }
                    }
                } else if (team[prev] == 'A' && actor[prev]) {
                    for (int i : ig[now]) {
                        int prevz = i * 6 + prev;
                        if (!inq[prevz]) {
                            res[prevz] = 1;
                            // cerr << "  2: push " << i << ' ' << prev << endl;
                            q.push(prevz);
                        }
                    }
                } else if (team[prev] == 'B' && !actor[prev]) {
                    for (int i : ig[now]) {
                        int prevz = i * 6 + prev;
                        if (!inq[prevz]) {
                            res[prevz] = 1;
                            // cerr << "  3: push " << i << ' ' << prev << endl;
                            q.push(prevz);
                        }
                    }
                } else {
                    for (int i : ig[now]) {
                        int prevz = i * 6 + prev;
                        ++cnt[prevz];
                        if (cnt[prevz] == g[i].size()) {
                            res[prevz] = 1;
                            // cerr << "  4: push " << i << ' ' << prev << endl;
                            q.push(prevz);
                        }
                    }
                }
            }

            // cerr << "solve 2 res: ";
            // for (int i = 0; i < n * 6; ++i) {
            //     cerr << res[i] << ' ';
            //     if (i % 6 == 5) cerr << ';';
            // }
            // cerr << endl;

            vector<int> ret(n, 0);
            for (int i = 0; i < n; ++i) ret[i] = !res[i * 6];

            return ret;
        };

        vector<int> awin = solve1();
        vector<int> atie = solve2();

        // cerr << "awin: ";
        // for (int i : awin) cerr << i << ' ';
        // cerr << endl;
        // cerr << "atie: ";
        // for (int i : atie) cerr << i << ' ';
        // cerr << endl;

        for (int i = 0; i < n; ++i) {
            if (awin[i]) cout << "A";
            else if (atie[i]) cout << "D";
            else cout << "B";
        }

        cout << '\n';
    }
}

