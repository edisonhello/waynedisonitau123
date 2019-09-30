#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 5;
const long long inf = 2e18;
char s[maxn], ans[maxn];
int dp[maxn][maxn];
long long dp2[maxn][maxn];
bool v[maxn][maxn], v2[maxn][maxn];

int dfs(int l, int r) {
    if (l > r) return 0;
    if (v[l][r]) return dp[l][r];
    if (s[l] == s[r]) {
        dp[l][r] = dfs(l + 1, r - 1);
    } else {
        dp[l][r] = min(dfs(l + 1, r), dfs(l, r - 1)) + 1;
    }
    v[l][r] = true; 
    return dp[l][r];
}

long long dfs2(int l, int r) {
    if (l > r) {
        dp2[l][r] = 1LL;
        return 1LL;
    }
    if (v2[l][r]) return dp2[l][r];

    if (s[l] == s[r]) {
        dp2[l][r] = dfs2(l + 1, r - 1);
    } else {
        if (dp[l + 1][r] + 1 == dp[l][r]) {
            dp2[l][r] += dfs2(l + 1, r);
            if (dp2[l][r] > inf) dp2[l][r] = inf;
        }

        if (dp[l][r - 1] + 1 == dp[l][r]) {
            dp2[l][r] += dfs2(l, r - 1);
            if (dp2[l][r] > inf) dp2[l][r] = inf;
        }
    }
    v2[l][r] = true;
    return dp2[l][r];
}

int main() {
    scanf("%s", s);
    long long k; scanf("%lld", &k);
    int n = strlen(s);
    int len = dfs(0, n - 1);
    dfs2(0, n - 1);
    // printf("len = %d\n", len);
    int l = 0, r = n - 1, p = 0;
    // printf("dp2 = %lld\n", dp2[0][n - 1]);
    while (l <= r) {
        // printf("l = %d r = %d\n", l, r);
        vector<long long> v(26, 0);
        if (s[l] == s[r]) {
            v[s[l] - 'a'] += dp2[l + 1][r - 1];
        } else {
            if (dp[l + 1][r] + 1 == dp[l][r]) {
                v[s[l] - 'a'] += dp2[l + 1][r];
                if (v[s[l] - 'a'] > inf) v[s[l] - 'a'] = inf;
            }
            if (dp[l][r - 1] + 1 == dp[l][r]) {
                v[s[r] - 'a'] += dp2[l][r - 1];
                if (v[s[r] - 'a'] > inf) v[s[r] - 'a'] = inf;
            }
        }
        for (int i = 1; i < 26; ++i) {
            v[i] += v[i - 1];
            if (v[i] > inf) v[i] = inf;
        }
        // if (s[l] == s[r]) assert(dp[l + 1][r - 1] < dp[l + 1][r] + 1 && dp[l + 1][r - 1] < dp[l][r - 1] + 1);
        bool ok = false;
        for (int i = 0; i < 26; ++i) {
            if (v[i] >= k) {
                if (i > 0) k -= v[i - 1];
                if (s[l] - 'a' == i && s[r] - 'a' == i) ++l, --r;
                else if (s[l] - 'a' == i) ++l;
                else if (s[r] - 'a' == i) --r;
                else assert(false);
                ans[p++] = i + 'a';
                ok = true;
                break;
            }
        }
        if (!ok) {
            puts("NONE");
            return 0;
        }
    }
    if (k > 1) {
        puts("NONE");
        return 0;
    }
    for (int i = 0; i < p; ++i) printf("%c", ans[i]);
    if (p * 2 == len + n) {
        for (int i = p - 1; i >= 0; --i) printf("%c", ans[i]);
    } else {
        assert(p * 2 - 1 == len + n);
        for (int i = p - 2; i >= 0; --i) printf("%c", ans[i]);
    }
    puts("");
    return 0;
}
