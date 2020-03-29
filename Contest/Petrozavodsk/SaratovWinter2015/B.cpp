#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, e, v;
    cin >> n >> m >> e >> v;
    vector<uint64_t> g1(n), g2(m);
    vector<vector<int>> adj(n, vector<int>(m));
    vector<int> d1(n), d2(m);
    v--;
    for (int i = 0; i < e; ++i) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        g1[x] ^= (1ULL << y);
        g2[y] ^= (1ULL << x);
        adj[x][y]++;
        d1[x]++;
        d2[y]++;
    }

    auto Grundy = [&](int v, int w) {
        if (w == 0) {
            vector<uint64_t> b;
            for (int i = 0; i < n; ++i) {
                if (i != v) {
                    uint64_t k = g1[i];
                    for (auto u : b) k = min(k, u ^ k);
                    if (k > 0) b.push_back(k);
                }
            }
            uint64_t k = g1[v];
            for (auto u : b) k = min(k, u ^ k);
            return k > 0;
        } else {
            vector<uint64_t> b;
            for (int i = 0; i < m; ++i) {
                if (i != v) {
                    uint64_t k = g2[i];
                    for (auto u : b) k = min(k, u ^ k);
                    if (k > 0) b.push_back(k);
                }
            }
            uint64_t k = g2[v];
            for (auto u : b) k = min(k, u ^ k);
            return k > 0;
        }
    };

    auto Move = [&](int v, int w) {
        cout << w + 1 << endl;
        g1[v] ^= (1ULL << w);
        g2[w] ^= (1ULL << v);
        adj[v][w]--;
        d1[v]--;
        d2[w]--;
        if (d2[w] == 0) {
            cout << "Player 1 wins" << endl;
            exit(0);
        }
        int b;
        cin >> b;
        b--;
        g1[b] ^= (1ULL << w);
        g2[w] ^= (1ULL << b);
        adj[b][w]--;
        d1[b]--;
        d2[w]--;
        return b;
    };

    while (true) {
        bool mv = false;
        if (d1[v] == 0) {
            cout << "Player 2 wins" << endl;
            exit(0);
        }
        for (int i = 0; i < m; ++i) {
            if (adj[v][i] > 0) {
                g2[i] ^= (1ULL << v);
                bool gr = Grundy(i, 1);
                g2[i] ^= (1ULL << v);
                if (!gr) {
                    mv = true;
                    v = Move(v, i);
                    break;
                }
            }
        }
        if (!mv) {
            for (int i = 0; i < m; ++i) {
                if (adj[v][i] > 0) {
                    v = Move(v, i);
                    break;
                }
            }
        }
    }
    
    return 0;
}

