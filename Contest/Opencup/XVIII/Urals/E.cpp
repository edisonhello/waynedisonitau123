#include <bits/stdc++.h>
using namespace std;

bool Octopus(vector<set<int>> g) {
    int n = (int)g.size() - 1;
    vector<int> djs(n + 1);
    iota(djs.begin(), djs.end(), 0);
    function<int(int)> F = [&] (int a) { return a == djs[a] ? a : djs[a] = F(djs[a]); };
    auto U = [&] (int a, int b) { djs[F(a)] = F(b); };
    for (int i = 1; i <= n; ++i) for (int j : g[i]) U(i, j);
    for (int i = 1; i <= n; ++i) if (F(i) != F(1)) return false;

    // cerr << "g = " << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cerr << "i = " << i << ": ";
    //     for (int j : g[i]) cerr << j << ' ';
    //     cerr << endl;
    // }

    stack<int> stk;
    set<int> loop;
    vector<bool> vis(n + 1, 0);
    bool found = 0;
    auto Dfs = [&] (auto self, int now, int pa) -> void {
        // cerr << "dfs " << now << ' ' << pa << endl;
        stk.push(now);
        vis[now] = 1;
        for (int i : g[now]) if (i != pa) {
            if (found) return;
            if (vis[i]) {
                while (stk.top() != i) {
                    loop.insert(stk.top());
                    stk.pop();
                }
                loop.insert(stk.top());
                found = 1;
            } else {
                self(self, i, now);
            }
        }
        vis[now] = 0;
        if (!found) stk.pop();
    };

    Dfs(Dfs, 1, 0);

    // cerr << "loop = "; for (int i : loop) cerr << i << ' '; cerr << endl;
    if (loop.empty()) return false;

    auto IsChain = [&] (auto self, int now, int pa) -> bool {
        if (g[now].size() > 2u) return false;
        if (g[now].size() == 1u) return true;
        return self(self, pa ^ *g[now].begin() ^ *next(g[now].begin()), now);
    };

    for (int i : loop) {
        vector<int> out;
        for (int j : g[i]) {
            if (!loop.count(j)) out.push_back(j);
        }

        if ((int)out.size() > 1) return false;

        if (out.size() && !IsChain(IsChain, out[0], i)) return false;
    }

    return true;
}

int main() {
    auto Answer = [&] (int a, int b) {
        cout << a << ' ' << b << endl;
        exit(0);
    };

    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<set<int>> g(n + 1);
    vector<int> deg(n + 1, 0);
    while (m--) {
        int u, v; cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
        ++deg[u];
        ++deg[v];
    }

    for (int i = 1; i <= n; ++i) {
        if (deg[i] >= 4) {
            set<int> back = g[i];
            for (int j : back) {
                // cerr << "try case 1, remove " << i << " - " << j << endl;
                g[i].erase(j);
                g[j].erase(i);
                if (Octopus(g)) {
                    Answer(i, j);
                }
                g[i].insert(j);
                g[j].insert(i);
            }
        }
    }

    vector<int> dfn(n + 1, 0), low(n + 1, 0);
    stack<int> stk;
    vector<int> bel(n + 1, 0);
    vector<vector<int>> mem(n + 1);
    int cc = 0;
    int nt = 0;
    auto Dfs = [&] (auto self, int now, int pa) -> void {
        // cerr << "Dfs " << now << endl;
        dfn[now] = low[now] = ++nt;
        stk.push(now);
        for (int i : g[now]) {
            if (i == pa) continue;
            else if (dfn[i]) {
                low[now] = min(low[now], dfn[i]);
            } else {
                self(self, i, now);
                low[now] = min(low[now], low[i]);
            }
        }
        // cerr << "Dfs " << now << " fin dfn low " << dfn[now] << ' ' << low[now] << endl;
        if (dfn[now] == low[now]) {
            ++cc;
            // cerr << "mem " << cc << ": ";
            while (stk.top() != now) {
                mem[cc].push_back(stk.top());
                bel[stk.top()] = cc;
                // cerr << stk.top() << ' ';
                stk.pop();
            }
            mem[cc].push_back(stk.top());
            bel[stk.top()] = cc;
            // cerr << stk.top() << ' ';
            stk.pop();
            // cerr << endl;
        }
    };

    Dfs(Dfs, 1, 0);

    vector<vector<int>> icg(n + 1);
    vector<vector<int>> cg(n + 1);
    vector<int> icgc(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j : g[i]) {
            if (bel[i] == bel[j]) {
                icg[i].push_back(j);
                ++icgc[bel[i]];
            } else {
                cg[bel[i]].push_back(bel[j]);
            }
        }
    }


    for (int i = 1; i <= cc; ++i) if (icgc[i] / 2 > (int)mem[i].size()) {
        cerr << "icgc mem size " << icgc[i] << ' ' << mem[i].size() << endl;
        vector<int> ends;
        for (int j : mem[i]) if ((int)icg[j].size() == 3) {
            for (int k : icg[j]) {
                g[j].erase(k);
                g[k].erase(j);
                if (Octopus(g)) {
                    Answer(j, k);
                }
                g[j].insert(k);
                g[k].insert(j);
            }
            ends.push_back(j);
        }

        assert((int)ends.size() == 2);

        auto Dfs = [&] (auto self, int now, int pa) -> void {
            // cerr << "dfs now pa " << now << ' ' << pa << endl;
            if (now == ends[1]) return;
            if ((int)g[now].size() == 3) {
                for (int i : icg[now]) {
                    // cerr << "try cut " << now << " - " << i << endl;
                    g[now].erase(i);
                    g[i].erase(now);
                    if (Octopus(g)) Answer(now, i);
                    g[now].insert(i);
                    g[i].insert(now);
                }
                return;
            }
            for (int i : icg[now]) if (i != pa) {
                self(self, i, now);
            }
        };

        for (int i : icg[ends[0]]) Dfs(Dfs, i, ends[0]);
    }

    // cerr << "cc = " << cc << endl;
    // for (int i = 1; i <= cc; ++i) cerr << "mem[" << i << "] size " << mem[i].size() << endl;
    // for (int i = 1; i <= cc; ++i) cerr << "cg[" << i << "] size " << cg[i].size() << endl;

    for (int i = 1; i <= cc; ++i) if ((int)mem[i].size() > 1) {
        if ((int)cg[i].size() <= 2) {
            for (int j : mem[i]) {
                bool yes = 0;
                for (int k : g[j]) if (bel[j] != bel[k]) yes = 1;
                if (yes) {
                    for (int k : icg[j]) {
                        g[j].erase(k);
                        g[k].erase(j);
                        if (Octopus(g)) {
                            Answer(j, k);
                        }
                        g[j].insert(k);
                        g[k].insert(j);
                    }
                }
            }
        }
    }

    assert(0);

}

