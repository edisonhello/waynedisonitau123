#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int K, N, M;
    cin >> K >> N >> M;

    auto Parse = [&](string s) {
        int V = 0;
        for (int i = 0; i < s.size(); ++i) {
            V = V * 10 + (s[i] - '0');
        }
        return V;
    };

    auto Convert = [&](const string &s) {
        if (s[1] == 'S') return Parse(s.substr(2)) - 1;
        return K + Parse(s.substr(2)) - 1;
    };

    vector<vector<int>> g1(N + K), g2(M + K);

    for (int i = 0; i < N + K - 1; ++i) {
        string s, t;
        cin >> s >> t;
        int x = Convert(s);
        int y = Convert(t);
        g1[x].push_back(y);
        g1[y].push_back(x);
    }
    for (int i = 0; i < M + K - 1; ++i) {
        string s, t;
        cin >> s >> t;
        int x = Convert(s);
        int y = Convert(t);
        g2[x].push_back(y);
        g2[y].push_back(x);
    }
    vector<int> L(K, -1), R(K, -1);
    for (int i = 0; i < K; ++i) {
        string s, t;
        cin >> s >> t;
        assert(s[0] != t[0]);
        if (s[0] == 'B') swap(s, t);
        int x = Convert(s);
        int y = Convert(t);
        L[x] = y;
        R[y] = x;
    }
    vector<vector<int>> chain1, chain2;

    auto Decompose = [&](auto &g, auto &chain) {
        bool flag = true;
        int N = g.size();
        vector<vector<int>> cg(N);

        auto Dfs = [&](auto dfs, int x, int p = -1) -> int {
            int cnt = 0, ch = 0;
            for (int u : g[x]) {
                if (u == p) continue;
                cnt += dfs(dfs, u, x);
                ch += 1;
            }
            if (cnt > 2) flag = false;
            if (ch == 0) {
                cg[x].push_back(p);
                cg[p].push_back(x);
                return 1;
            }
            if (cnt == 1 && p != -1) {
                cg[x].push_back(p);
                cg[p].push_back(x);
            }
            return cnt % 2;
        };

        assert(!g[0].empty());
        if (Dfs(Dfs, N - 1) != 0) flag = false;
        if (!flag) return false;

        vector<bool> mark(N);
        for (int i = 0; i < N; ++i) {
            if (mark[i]) continue;
            if (cg[i].empty()) return false;
            if (cg[i].size() == 1) {
                vector<int> v;
                int x = i, prv = -1;
                while (true) {
                    mark[x] = true;
                    v.push_back(x);
                    int nxt = -1;
                    for (int u : cg[x]) {
                        if (u != prv) {
                            nxt = u;
                            break;
                        }
                    }
                    if (nxt == -1) break;
                    prv = x;
                    x = nxt;
                }
                assert(g[v[0]].size() == 1);
                assert(g[v.back()].size() == 1);
                chain.push_back(v);
            }
        }
        for (int i = 0; i < N; ++i) {
            if (!mark[i]) return false;
        }
        return true;
    };

    if (!Decompose(g1, chain1) || !Decompose(g2, chain2)) {
        cout << "NO\n";
        return;
    }

    vector<int> A(K), B(K);
    vector<int> P(K), Q(K);
    for (int i = 0; i < chain1.size(); ++i) {
        assert(!chain1[i].empty());
        assert(chain1[i][0] < K);
        assert(chain1[i].back() < K);
        A[chain1[i][0]] = i;
        A[chain1[i].back()] = i;
        P[chain1[i][0]] = chain1[i].back();
        P[chain1[i].back()] = chain1[i][0];
    }
    for (int i = 0; i < chain2.size(); ++i) {
        assert(!chain2[i].empty());
        assert(chain2[i][0] < K);
        assert(chain2[i].back() < K);
        B[chain2[i][0]] = i;
        B[chain2[i].back()] = i;
        Q[chain2[i][0]] = chain2[i].back();
        Q[chain2[i].back()] = chain2[i][0];
    }
    assert(K % 2 == 0);
    int X = 0;
    vector<int> route;
    vector<bool> U(K);
    vector<bool> V(K);
    for (int i = 0; i < K / 2; ++i) {
        route.push_back(X);
        if (U[X]) {
            cout << "NO\n";
            return;
        }
        U[X] = true;
        X = P[X];
        if (U[X]) {
            cout << "NO\n";
            return;
        }
        U[X] = true;
        X = L[X];
        route.push_back(X);
        if (V[X]) {
            cout << "NO\n";
            return;
        }
        V[X] = true;
        X = Q[X];
        if (V[X]) {
            cout << "NO\n";
            return;
        }
        V[X] = true;
        X = R[X];
    }
    cout << "YES";

    auto Print = [&](int x) {
        if (x < K) return string("S") + to_string(x + 1);
        return string("P") + to_string(x - K + 1);
    };

    for (int i = 0; i < K; i += 2) {
        if (chain1[A[route[i]]][0] != route[i]) {
            reverse(chain1[A[route[i]]].begin(), chain1[A[route[i]]].end());
        }
        for (int u : chain1[A[route[i]]]) {
            cout << " A" << Print(u);
        }
        if (chain2[B[route[i + 1]]][0] != route[i + 1]) {
            reverse(chain2[B[route[i + 1]]].begin(), chain2[B[route[i + 1]]].end());
        }
        for (int u : chain2[B[route[i + 1]]]) {
            cout << " B" << Print(u);
        }
    }
    cout << "\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        Solve();
    }
}

