#include <bits/stdc++.h>
using namespace std;

void solove() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n * n * 2);
    vector<vector<int>> ig(n * n * 2);
    vector<vector<int>> og(n);
    vector<int> cnt(n * n * 2);

    while (m--) {
        int u, v; cin >> u >> v;
        --u, --v;
        og[u].push_back(v);
        for (int i = 0; i < n; ++i) {
            g[u * n + i].push_back(v * n + i + n * n);
            g[i * n + u + n * n].push_back(i * n + v);

            ig[v * n + i + n * n].push_back(u * n + i);
            ig[i * n + v].push_back(i * n + u + n * n);
        }
    }

    vector<int> win(n * n * 2, 0), lose(n * n * 2, 0);
    for (int i = 0; i < n; ++i) {
        lose[i * n + i] = 1;
        lose[i * n + i + n * n] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (og[j].empty()) {
                win[i * n + j + n * n] = 1;
            } 
            if (og[i].empty()) {
                lose[i * n + j] = 1;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < n * n * 2; ++i) if (win[i] || lose[i]) q.push(i);

    while (q.size()) {
        int now = q.front(); q.pop();
        // cerr << "now = " << now / 2 / n << ' ' << now / 2 % n << ' ' << now / (n * n) << endl;
        // cerr << "result = " << (win[now] ? "win" : "") << ' ' << (lose[now] ? "lose" : "") << endl;
        // if (win[now] || lose[now]) continue;

        for (int i : ig[now]) ++cnt[i];

        for (int i : ig[now]) {
            if (win[i] || lose[i]) continue;
            if (i < n * n) {
                if (win[now]) {
                    win[i] = 1;
                    q.push(i);
                } else {
                    if (cnt[i] == g[i].size()) {
                        bool alllose = true;
                        for (int j : g[i]) {
                            if (win[j]) alllose = false;
                        }
                        if (alllose) lose[i] = 1;
                        else win[i] = 1;
                        q.push(i);
                    }
                }
            }

            if (i >= n * n) {
                if (lose[now]) {
                    lose[i] = 1;
                    q.push(i);
                } else {
                    if (cnt[i] == g[i].size()) {
                        bool allwin = true;
                        for (int j : g[i]) {
                            if (lose[j]) allwin = false;
                        }
                        if (allwin) win[i] = 1;
                        else lose[i] = 1;
                        q.push(i);
                    }
                }
            }
        }
    }

    int x, y; cin >> x >> y;
    --x, --y;

    if (lose[x * n + y]) {
        cout << "No" << '\n';
    } else {
        cout << "Yes" << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t, T = 0;
    cin >> t;
    while (t--) {
        cout << "Case #" << (++T) << ": ";
        solove();
    }
}

