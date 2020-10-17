#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<string> S(N);
    unordered_map<string, int> CC;
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
        if (CC[S[i]] == 2) {
            cout << "NO\n";
            return 0;
        }
        CC[S[i]]++;
    }

    vector<array<int, 2>> trie(1, array<int, 2>{-1, -1});
    vector<vector<int>> nodes(1);

    auto PushTrie = [&](const string &S, int p, int b) {
        int X = 0;
        for (int i = 0; i < S.size(); ++i) {
            int bit = S[i] - '0';
            if (trie[X][bit] == -1) {
                int V = trie.size();
                trie[X][bit] = V;
                nodes.emplace_back();
                trie.push_back({-1, -1});
            }
            X = trie[X][bit];
        }
        if (b == 0) nodes[X].emplace_back(p);
        else nodes[X].emplace_back(~p);
    };

    for (int i = 0; i < N; ++i) {
        bool flag = false;
        for (int j = 0; j < S[i].size(); ++j) {
            if (S[i][j] == '?') {
                S[i][j] = '0';
                PushTrie(S[i], i, 0);
                S[i][j] = '1';
                PushTrie(S[i], i, 1);
                flag = true;
                S[i][j] = '?';
                break;
            }
        }
        if (!flag) {
            PushTrie(S[i], i, 0);
            PushTrie(S[i], i, 1);
        }
    }


    int K = N;
    vector<pair<int, int>> edges;
    int M = trie.size();
    vector<int> which(M, -1);
    for (int i = 0; i < M; ++i) {
        which[i] = K++;
        if (!nodes[i].empty()) {

            auto DfsT = [&](auto dfs, int l, int r) -> int {
                if (r - l == 1) {
                    int V = nodes[i][l];
                    edges.emplace_back(V, K);
                    edges.emplace_back(K, V);
                    edges.emplace_back(~V, ~K);
                    edges.emplace_back(~K, ~V);
                    return K++;
                }
                int m = (l + r) >> 1;
                int L = dfs(dfs, l, m);
                int R = dfs(dfs, m, r);
                edges.emplace_back(L, K);
                edges.emplace_back(R, K);
                edges.emplace_back(~K, ~L);
                edges.emplace_back(~K, ~R);
                edges.emplace_back(L, ~R);
                edges.emplace_back(R, ~L);
                return K++;
            };

            int root = DfsT(DfsT, 0, nodes[i].size());
            edges.emplace_back(root, which[i]);
            edges.emplace_back(~which[i], ~root);
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int bit = 0; bit < 2; ++bit) {
            if (trie[i][bit] != -1) {
                edges.emplace_back(~which[i], ~which[trie[i][bit]]);
                edges.emplace_back(which[trie[i][bit]], which[i]);
            }
        }
        for (int p : nodes[i]) {
            for (int bit = 0; bit < 2; ++bit) {
                if (trie[i][bit] != -1) {
                    edges.emplace_back(p, ~which[trie[i][bit]]);
                    edges.emplace_back(which[trie[i][bit]], ~p);
                }
            }
        }
    }
    vector<vector<int>> G(K + K), R(K + K);

    auto AddEdge = [&](int x, int y) {
        if (x < 0) x = (~x) + K;
        if (y < 0) y = (~y) + K;
        G[x].push_back(y);
        R[y].push_back(x);
    };
    for (auto e : edges) AddEdge(e.first, e.second);


    vector<int> order;
    vector<bool> used(K + K);
    vector<int> scc(K + K, -1);

    auto Dfs = [&](auto dfs, int x) -> void {
        used[x] = true;
        for (int u : G[x]) {
            if (!used[u]) dfs(dfs, u);
        }
        order.push_back(x);
    };

    auto RevDfs = [&](auto dfs, int x, int p) -> void {
        scc[x] = p;
        for (int u : R[x]) {
            if (scc[u] == -1) dfs(dfs, u, p);
        }
    };

    for (int i = 0; i < K + K; ++i) {
        if (!used[i]) {
            Dfs(Dfs, i);
        }
    }
    int cnt = 0;
    for (int i = K + K - 1; i >= 0; --i) {
        if (scc[order[i]] == -1) {
            RevDfs(RevDfs, order[i], cnt++);
        }
    }
    for (int i = 0; i < K; ++i) {
        if (scc[i] == scc[i + K]) {
            cout << "NO\n";
            return 0;
        }
    }
    vector<int> SAT(cnt, -1);
    for (int i = K + K - 1; i >= 0; --i) {
        int X = order[i];
        int Y = X < K ? X + K : X - K;
        assert(Y < K + K);
        if (SAT[scc[X]] == -1) {
            SAT[scc[X]] = 0;
            assert(scc[Y] != -1);
            SAT[scc[Y]] = 1;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < S[i].size(); ++j) {
            if (S[i][j] == '?') {
                assert(SAT[scc[i]] != -1);
                if (SAT[scc[i]]) S[i][j] = '0';
                else S[i][j] = '1';
            }
        }
        cout << S[i] << "\n";
    }
    return 0;
}

