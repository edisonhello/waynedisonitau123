#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
char s[maxn];
long long dp[maxn][maxn * 10];
long long fc[maxn];
int d[maxn], cnt[maxn];

long long dfs(int p, int z, int n, int s, long long pr, long long pd) {
    // printf("dfs p = %d z = %d n = %d s = %d pr = %lld pd = %lld\n", p, z, n, s, pr, pd);
    if (pd > pr) return 0LL;
    if (p == n) {
        if (s != 0) return 0LL;
        if (pd < pr) {
            long long res = fc[n];
            for (int i = 0; i < 10; ++i) res /= fc[cnt[i]];
            return res;
        }
        vector<int> cc(cnt, cnt + 10);
        long long res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < d[i]; ++j) {
                if (cc[j] > 0) {
                    --cc[j];
                    long long add = fc[n - i - 1];
                    for (int k = 0; k < 10; ++k) add /= fc[cc[k]];
                    res += add;
                    ++cc[j];
                }
            }
            if (cc[d[i]] == 0) break;
            --cc[d[i]];
        }
        return res;
    }
    long long res = 0;
    for (int i = z; i < 10; ++i) {
        if (s - (n - p) * i < 0) break;
        ++cnt[i];
        res += dfs(p + 1, i, n, s - i, pr, pd * (i + 1));
        --cnt[i];
    }
    return res;
}

int main() {
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 0; i < n; ++i) d[i] = s[i] - '0';
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < maxn * 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                if (j + k < maxn * 10) {
                    dp[i + 1][j + k] += dp[i][j];
                }
            }
        }
    }
    int sum = accumulate(d, d + n, 0);
    long long ans = 0;
    for (int i = 0; i < sum; ++i) ans += dp[n][i];
    
    long long pr = 1LL;
    for (int i = 0; i < n; ++i) pr *= (d[i] + 1);

    fc[0] = 1;
    for (int i = 1; i < maxn; ++i) fc[i] = fc[i - 1] * i;
    printf("%lld\n", ans + dfs(0, 0, n, sum, pr, 1LL));
    return 0;
}

