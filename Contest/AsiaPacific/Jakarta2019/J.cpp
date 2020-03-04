#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
const int kM = 50 + 5;
int dist[kM], pos[kM];
bool dp[kM][kM][kM][kM][2];
char s[kN];

int main() {
    int n, K, g1, g2, g3;
    scanf("%d%d%d%d%d", &n, &K, &g1, &g2, &g3);
    scanf("%s", s);
    int pv = 0, z = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '#') {
            dist[++z] = i - pv; 
            pos[z] = i;
            pv = i + 1;
        }
    }
    bool ok = true;
    if (s[n - 1] == '#') ok = false;
    dp[0][0][0][0][0] = true;
    pos[0] = -1;
    pos[z + 1] = n;
    for (int p = 1; p <= z; ++p) {
        for (int i = 0; i <= z; ++i) {
            for (int j = 0; j <= z; ++j) {
                for (int k = 0; k <= z; ++k) {
                    for (int x = 0; x < 2; ++x) {
                        for (int y = 0; y < 2; ++y) {
                            if (y == 0 || pos[p] - pos[p - 1] >= 2 && pos[p + 1] - pos[p] >= 2) {
                                if (dist[p] - x - y < 0) continue;
                                int parity = (dist[p] - x - y) & 1;
                                if (y == 1 && k == 0) continue;
                                if (parity) {
                                    if (i == 0) continue;
                                    if (y == 1)
                                        dp[p][i][j][k][y] |= dp[p - 1][i - 1][j][k - 1][x];
                                    else
                                        dp[p][i][j][k][y] |= dp[p - 1][i - 1][j][k][x];
                                } else {
                                    if (j == 0) continue;
                                    if (y == 1)
                                        dp[p][i][j][k][y] |= dp[p - 1][i][j - 1][k - 1][x];
                                    else
                                        dp[p][i][j][k][y] |= dp[p - 1][i][j - 1][k][x];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i <= z; ++i) {
        for (int j = 0; j <= z; ++j) {
            for (int k = 0; k <= z; ++k) {
                if (dp[z][i][j][k][0]) {
                    int L = n - 2 * k - z;
                    int a = i, b = j;
                    if ((n - pv) & 1) ++a;
                    else ++b;
                    // printf("i = %d j = %d k = %d 0\n", i, j, k);
                    // printf("a = %d b = %d L = %d\n", a, b, L);
                    assert((L - a) % 2 == 0);
                    int tk = min(K, a);
                    long long add = k * g3 + 1LL * g2 * (L - a) / 2 + 1LL * tk * g1;
                    int lm = K - tk, bb = (L - a) / 2;
                    if (2 * g1 > g2) {
                        int rem = min(bb, lm / 2);
                        add += 1LL * (2 * g1 - g2) * rem;
                        lm -= 2 * rem;
                        bb -= rem;
                        if (g1 > g2) {
                            int rem = min(lm, 2 * bb);
                            add += 1LL * (g1 - g2) * rem;
                        }
                    }
                    ans = max(ans, add);
                }
                if (dp[z][i][j][k][1]) {
                    int L = n - 2 * k - z;
                    int a = i, b = j;
                    if ((n - pv - 1) & 1) ++a;
                    else ++b;
                    // printf("i = %d j = %d k = %d 1\n", i, j, k);
                    // printf("a = %d b = %d L = %d\n", a, b, L);
                    assert((L - a) % 2 == 0);
                    int tk = min(K, a);
                    long long add = k * g3 + 1LL * g2 * (L - a) / 2 + 1LL * tk * g1;
                    int lm = K - tk, bb = (L - a) / 2;
                    if (2 * g1 > g2) {
                        int rem = min(bb, lm / 2);
                        add += 1LL * (2 * g1 - g2) * rem;
                        lm -= 2 * rem;
                        bb -= rem;
                        if (g1 > g2) {
                            int rem = min(lm, 2 * bb);
                            add += 1LL * (g1 - g2) * rem;
                        }
                    }
                    ans = max(ans, add);
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
