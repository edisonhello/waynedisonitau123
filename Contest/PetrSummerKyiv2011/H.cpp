#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int f, dp[maxn], vis[maxn];

int mex(const vector<int> &v) {
    for (int i = 0; i < (int)v.size(); ++i) vis[v[i]] = 1;
    int res = 0;
    while (vis[res]) ++res;
    for (int i = 0; i < (int)v.size(); ++i) vis[v[i]] = 0;
    return res;
}

int check(int x, int t, int i, int j) {
    for (int a = 0; t * a <= x; ++a) {
        int y = x - (t * a);
        if (y % (t + 1) == 0) {
            if (a % 2 == i && (y / (t + 1)) % 2 == j) 
                return true;
        }
    }
    return false;
}

int dfs(int);

int calc(int x, int t, int a, int b) {
    int c = 0;
    if (a % 2 == 1) c ^= dfs(t);
    if (b % 2 == 1) c ^= dfs(t + 1);
    return c;
}

int dfs(int x) {
    if (x < f) return 0;
    if (~dp[x]) return dp[x];
    vector<int> sub;
    if (x == 2) return dp[x] = 1;
    for (int t = 1; t < x; t = (x / (x / (t + 1)))) {
        sub.push_back(calc(x, t, x / t - (x % t), x % t));
        if (x / t  - (x % t) + t + 1 >= 0 && x % t - t >= 0)
            sub.push_back(calc(x, t, x / t  - (x % t) + t + 1, x % t - t));
        if (x / t  - (x % t) - t - 1 >= 0 && x % t + t >= 0)
            sub.push_back(calc(x, t, x / t  - (x % t) - t - 1, x % t + t));
    }
    return dp[x] = mex(sub);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("nimg.in", "r", stdin);
    freopen("nimg.out", "w", stdout);
#endif
    int r; scanf("%d%d", &r, &f);
    memset(dp, -1, sizeof(dp));
    while (r--) {
        int g; scanf("%d", &g);
        int ans = 0;
        while (g--) {
            int x; scanf("%d", &x);
            ans ^= dfs(x);
        }
        printf("%d ", ans > 0);
    }
    return 0;
}
