#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

cc_hash_table<uint64_t, double> dp[40];

double Dfs(int n, uint64_t mask) {
    if (n == 0) return 1.0;
    if (dp[n].find(mask) != dp[n].end()) return dp[n][mask];
    if (__builtin_popcountll(mask) != n / 2) return 0.0;
    if (mask & 1) return 0.0;
    if ((mask >> (n - 1)) == 0) return 0.0;
    double res = 0.0;
    int pairs = 0;
    for (int i = 0; i < n; ++i) {
        if (!(mask >> i & 1)) {
            for (int j = i + 1; j < n; ++j) {
                if (mask >> j & 1) {
                    uint64_t nmask = 0;
                    int shift = 0;
                    if (i > 0) {
                        nmask |= mask & ((1ULL << i) - 1);
                        shift += i;
                    }
                    if (j - i > 1) {
                        uint64_t mid = (mask & ((1ULL << j) - 1)) >> (i + 1);
                        nmask |= mid << i;
                        shift += j - i - 1;
                    }
                    if (j + 1 < n) {
                        uint64_t last = mask >> (j + 1);
                        nmask |= last << shift;
                    }
                    res += Dfs(n - 2, nmask);
                    pairs++;
                }
            }
        }
    }
    if (pairs == 0) {
        dp[n][mask] = 0.0;
        return 0.0;
    }
    return dp[n][mask] = res / pairs;
}

int main() {
    string s;
    cin >> s;
    uint64_t mask = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ')') mask |= (1ULL << i);
    }
    cout << fixed << setprecision(20) << Dfs(s.size(), mask) << "\n";
    return 0;
}

