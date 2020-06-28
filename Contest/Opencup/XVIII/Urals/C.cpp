#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k, q;
    cin >> n >> k >> q;
    constexpr int kB = 500;
    vector<int> c(n);
    vector<vector<int>> group(k);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        c[i]--;
        group[c[i]].push_back(i);
    }
    vector<int> id(k, -1);
    constexpr int kN = 200'000;
    vector<int> big;
    for (int i = 0; i < k; ++i) {
        if (group[i].size() < kB) continue;
        id[i] = big.size();
        big.push_back(i);
    }
    vector<vector<int>> edge(k, vector<int>(big.size()));
    for (int i = 0; i < big.size(); ++i) {
        for (int j = 0; j < k; ++j) {
            if (j == big[i]) continue;
            for (int u : group[j]) {
                if (u > 0 && c[u - 1] == big[i]) edge[j][i]++;
                if (u + 1 < n && c[u + 1] == big[i]) edge[j][i]++;
            }
        }
    }
    vector<int> on(k);
    vector<int> stat(n);
    vector<int> son(big.size());
    vector<int> soff(big.size());
    vector<int> bon(big.size());
    vector<int> boff(big.size());
    int res = 0;
    for (int i = 0; i < big.size(); ++i) {
        for (int j = 0; j < k; ++j) {
            if (group[j].size() < kB) {
                soff[i] += edge[j][i];
            } else {
                boff[i] += edge[j][i];
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        int d;
        cin >> d;
        d--;
        if (group[d].size() < kB) {
            if (on[d]) {
                for (int u : group[d]) {
                    if (u > 0 && group[c[u - 1]].size() < kB && c[u - 1] != d) {
                        if (stat[u - 1]) res++;
                        else res--;
                    }
                    if (u + 1 < n && group[c[u + 1]].size() < kB && c[u + 1] != d) {
                        if (stat[u + 1]) res++;
                        else res--;
                    }
                    stat[u] ^= 1;
                }    
                for (int j = 0; j < big.size(); ++j) {
                    son[j] -= edge[d][j];
                    soff[j] += edge[d][j];
                }
            } else {
                for (int u : group[d]) {
                    if (u > 0 && group[c[u - 1]].size() < kB && c[u - 1] != d) {
                        if (stat[u - 1]) res--;
                        else res++;
                    }
                    if (u + 1 < n && group[c[u + 1]].size() < kB && c[u + 1] != d) {
                        if (stat[u + 1]) res--;
                        else res++;
                    }
                    stat[u] ^= 1;
                }    
                for (int j = 0; j < big.size(); ++j) {
                    son[j] += edge[d][j];
                    soff[j] -= edge[d][j];
                }
            }
        } else {
            if (on[d]) {
                for (int j = 0; j < big.size(); ++j) {
                    bon[j] -= edge[d][j];
                    boff[j] += edge[d][j];
                }
            } else {
                for (int j = 0; j < big.size(); ++j) {
                    bon[j] += edge[d][j];
                    boff[j] -= edge[d][j];
                }
            }
        }
        on[d] ^= 1;
        int tres = res;
        for (int j = 0; j < big.size(); ++j) {
            if (on[big[j]]) {
                tres += soff[j];
                tres += boff[j];
            } else {
                tres += son[j];
            }
        }
        if (!on[c[0]]) cout << (tres + 1) / 2 << "\n";
        else cout << tres / 2 + 1 << "\n";
    }
}

