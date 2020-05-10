#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<uint64_t>> adj(n, vector<uint64_t>(2));
    vector<int> fr;
    vector<vector<int>> ed(n, vector<int>(n, -1));
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        ed[u][v] = t;
        ed[v][u] = t;
        adj[u][t] |= (1ULL << v);
        adj[v][t] |= (1ULL << u);
        if (u == 0 || v == 0) fr.push_back(u ^ v);
    }
    constexpr int kF = 23;
    if (fr.size() < kF) {
        sort(fr.begin(), fr.end());
        int k = fr.size();
        uint64_t forb = 1;
        int gf = 0;
        for (int i = 0; i < k; ++i) {
            forb |= (1ULL << fr[i]);
            if (ed[0][fr[i]] == 0) gf++;
        }
        vector<int> dp(1 << k, -1E9);
        dp[0] = 0;
        vector<uint64_t> uni(1 << k);
        for (int i = 0; i < n; ++i) {
            adj[i][0] &= (~forb);
            adj[i][1] &= (~forb);
        }
        for (int s = 0; s < (1 << k); ++s) {
            for (int i = 0; i < k; ++i) {
                if (s >> i & 1) {
                    uni[s] |= adj[fr[i]][0];
                    uni[s] |= adj[fr[i]][1];
                }
            }
        }
        vector<int> wh(1 << k, -1);
        for (int s = 0; s < (1 << k); ++s) {
            for (int i = 0; i < k; ++i) {
                if (s >> i & 1) continue;
                int r = ed[0][fr[i]];
                assert(r != -1);
                uint64_t good = adj[fr[i]][r] & (~uni[s]);
                int v = dp[s] + __builtin_popcountll(good);
                if (v > dp[s ^ (1 << i)]) {
                    dp[s ^ (1 << i)] = v;
                    wh[s ^ (1 << i)] = i;
                }
            }
        }
        int res = dp[(1 << k) - 1] + gf;
        cout << fixed << setprecision(20) << 1.0 * res / (n - 1) << "\n";
        vector<int> ord;
        int s = (1 << k) - 1;
        while (s > 0) {
            int b = wh[s];
            ord.push_back(b);
            s ^= (1 << b);
        }
        reverse(ord.begin(), ord.end());
        for (int u : ord) cout << fr[u] + 1 << " ";
        cout << "\n";
        return 0;
    }
    vector<int> nfr;
    for (int i = 1; i < n; ++i) {
        if (ed[0][i] == -1) {
            bool mut = false;
            for (int j = 0; j < n; ++j) {
                mut |= ed[0][j] != -1 && ed[j][i] != -1;
            }
            if (mut) nfr.push_back(i);
        }
    }
    assert(nfr.size() <= 18);
    int k = nfr.size(), gf = 0;
    uint64_t forb = 0;
    for (int i = 0; i < fr.size(); ++i) {
        forb |= (1ULL << fr[i]);
        if (ed[0][fr[i]] == 0) gf++;
    }
    for (int i = 0; i < n; ++i) {
        adj[i][0] &= (~forb);
        adj[i][1] &= (~forb);
    }
    vector<bool> used(fr.size());
    int res = -1;
    vector<int> bord = fr;
    for (int s = 0; s < (1 << k); ++s) {
        vector<int> ord;
        uint64_t s0 = 0, s1 = 0;
        for (int i = 0; i < k; ++i) {
            if (s >> i & 1) s1 |= (1ULL << nfr[i]);
            else s0 |= (1ULL << nfr[i]);
        }
        uint64_t mask = 0;
        fill(used.begin(), used.end(), false);
        bool ok = true;
        for (int i = 0; i < fr.size(); ++i) {
            bool found = false;
            for (int j = 0; j < fr.size(); ++j) {
                if (used[j]) continue;
                uint64_t g0 = adj[fr[j]][ed[0][fr[j]]] & (~mask);
                uint64_t g1 = adj[fr[j]][ed[0][fr[j]] ^ 1] & (~mask);
                if (g0 & s1) continue;
                if (g1 & s0) continue;
                used[j] = true;
                mask |= adj[fr[j]][0];
                mask |= adj[fr[j]][1];
                found = true;
                ord.push_back(fr[j]);
                break;
            }
            if (!found) {
                ok = false;
                break;
            }
        }
        if (ok) {
            int pc = k - __builtin_popcount(s);
            if (pc > res) {
                res = pc;
                bord = ord;
            }
        }
    }
    res += gf;
    cout << fixed << setprecision(20) << 1.0 * res / (n - 1) << "\n";
    for (int u : bord) cout << u + 1 << " ";
    cout << endl;
}

