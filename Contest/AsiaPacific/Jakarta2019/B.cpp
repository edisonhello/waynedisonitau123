#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
const int kMod = 1e9 + 7;
vector<int> g[kN];
int dp[kN][3];

void Dfs(int x, int p) {
    array<int, 3> tmp{};
    array<int, 2> tmp2{};
    array<array<int, 2>, 2> tmp3{};
    int ch = 0, mult = 1;
    tmp[0] = 1;
    tmp2[0] = 1;
    tmp3[0][0] = 1;
    for (int u : g[x]) {
        if (u == p) continue;
        Dfs(u, x);
        array<int, 3> nxt{};
        array<int, 2> nxt2{};
        array<array<int, 2>, 2> nxt3{};

        nxt2[0] += 1LL * tmp2[0] * dp[u][0] % kMod;
        nxt2[0] %= kMod;
        nxt2[1] += 1LL * tmp2[1] * dp[u][0] % kMod;
        nxt2[1] %= kMod;
        nxt2[1] += 1LL * tmp2[0] * (dp[u][1] + dp[u][2]) % kMod;
        nxt2[1] %= kMod;

        tmp2 = nxt2;

        for (int i = 0; i < 3; ++i) {
            nxt[i] += 1LL * tmp[i] * (dp[u][0] + dp[u][1]) % kMod;
            nxt[i] %= kMod;
            if (i + 1 < 3) {
                nxt[i + 1] += 1LL * tmp[i] * dp[u][1] % kMod;
                nxt[i + 1] %= kMod;
                nxt[i + 1] += 1LL * tmp[i] * dp[u][2] % kMod;
                nxt[i + 1] %= kMod;
            }
        }
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                nxt3[i][j] += 1LL * tmp3[i][j] * dp[u][0] % kMod;
                nxt3[i][j] %= kMod;
                nxt3[min(1, i + 1)][j] += 1LL * tmp3[i][j] * dp[u][1] % kMod;
                nxt3[min(1, i + 1)][j] %= kMod;
                if (j == 0) {
                    nxt3[i][min(1, j + 1)] += 1LL * tmp3[i][j] * (dp[u][1] + dp[u][2]) % kMod;
                    nxt3[i][min(1, j + 1)] %= kMod;
                }
            }
        }
        mult = 1LL * mult * dp[u][0] % kMod;
        ch += 1;
        tmp = nxt;
        tmp3 = nxt3;
    }
    if (ch == 0) {
        dp[x][1] = 1;
    } else {
        dp[x][0] = tmp[2];
        dp[x][1] = (tmp2[1] + mult) % kMod;
        dp[x][2] = tmp3[1][1];
    }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    Dfs(0, -1);
    printf("%lld\n", (0LL + dp[0][0] + dp[0][1]) % kMod);
    return 0;
}
