#include <bits/stdc++.h>
using namespace std;

bool Solve() {
    int N, M;
    cin >> N >> M;
    string s;
    cin >> s;
    vector<vector<int>> g(N);
    vector<int> st(M), ed(M), E;
    for (int i = 0; i < M; ++i) {
        cin >> st[i] >> ed[i];
        if (s[st[i]] != s[ed[i]]) {
            g[st[i]].push_back(i);
            g[ed[i]].push_back(i);
        } else {
            E.push_back(i);
        }
    }

    if (g[0].empty()) return false;

    vector<int> dfn(N, -1), low(N), fa(N);
    vector<bool> instk(M), is_cut(N);
    vector<int> stk;
    vector<int> where(M, -1);
    int stamp = 0, B = 0;

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        dfn[x] = low[x] = stamp++;
        int child = 0;
        for (int e : g[x]) {
            if (e == p) continue;
            if (!instk[e]) {
                instk[e] = true;
                stk.push_back(e);
            }
            int u = st[e] ^ ed[e] ^ x;
            if (dfn[u] != -1) {
                low[x] = min(low[x], dfn[u]);
            } else {
                child++;
                dfs(dfs, u, e);
                low[x] = min(low[x], low[u]);
                if (low[u] >= dfn[x]) {
                    is_cut[x] = true;
                    while (!stk.empty()) {
                        int f = stk.back();
                        stk.pop_back();
                        where[f] = B;
                        if (e == f) break;
                    }
                    B++;
                }
            }
        }
        if (child == 1 && p == -1) is_cut[x] = false;
    };

    Dfs(Dfs, 0);
    vector<vector<int>> T(N + B);
    vector<vector<int>> C(B);
    for (int i = 0; i < M; ++i) {
        if (where[i] != -1) C[where[i]].push_back(i);
    }
    for (int i = 0; i < B; ++i) {
        for (int e : C[i]) {
            if (is_cut[st[e]]) {
                T[st[e]].push_back(N + i);
                T[N + i].push_back(st[e]);
            }
            if (is_cut[ed[e]]) {
                T[ed[e]].push_back(N + i);
                T[N + i].push_back(ed[e]);
            }
        }
    }
    for (int i = 0; i < N + B; ++i) {
        sort(T[i].begin(), T[i].end());
        T[i].resize(unique(T[i].begin(), T[i].end()) - T[i].begin());
    }
    vector<vector<int>> X(N);
    for (int i = 0; i < N; ++i) {
        for (int e : g[i]) {
            if (where[e] != -1) X[i].push_back(where[e]);
        }
        sort(X[i].begin(), X[i].end());
        X[i].resize(unique(X[i].begin(), X[i].end()) - X[i].begin());
    }

    auto Get = [&](int x) {
        if (x >= N) return x;
        if (is_cut[x]) return x;
        assert(X[x].size() == 1);
        return N + X[x][0];
    };

    vector<int> tin(N + B, -1), tout(N + B, -1), par(N + B, -1);
    stamp = 0;

    auto Dfs2 = [&](auto dfs, int x, int p = -1) -> void {
        tin[x] = stamp++;
        par[x] = p;
        for (int u : T[x]) {
            if (u == p) continue;
            dfs(dfs, u, x);
        }
        tout[x] = stamp;
    };

    Dfs2(Dfs2, Get(0));

    auto IsAnc = [&](int x, int y) {
        return tin[x] <= tin[y] && tout[y] <= tout[x];
    };

    auto Check = [&](int x, int y) {
        if (IsAnc(Get(x), Get(y))) return true;
        if (is_cut[x]) x = par[x];
        if (IsAnc(Get(x), Get(y))) return true;
        return false;
    };

    for (int e : E) {
        // cout << dfn[st[e]] << " " << dfn[ed[e]] << endl;
        if (dfn[st[e]] == -1) continue;
        if (dfn[ed[e]] == -1) continue;
        if (Check(st[e], ed[e])) return true;
        if (Check(ed[e], st[e])) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cout << (Solve() ? "yes" : "no") << "\n";
    }
}

