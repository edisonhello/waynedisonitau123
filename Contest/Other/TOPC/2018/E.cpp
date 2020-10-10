#include <bits/stdc++.h>
using namespace std;

const int maxn = 600;
const int inf = 1e9;
int dp[maxn][maxn], fr[maxn][maxn];
int n, bst, sz;
int a[maxn], b[maxn];

int calc(int x) {
    sz = 0;
    for (int i = 1; i <= n; ++i) {
        if (i == x) continue;
        b[++sz] = a[i];
    }
    for (int i = 0; i < maxn; ++i) for (int j = 0; j < maxn; ++j) dp[i][j] = -inf;
    dp[0][0] = 0;
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < maxn; ++j) {
            if (dp[i][j] == -inf) continue;
            if ((dp[i][j] | b[i + 1]) > dp[i + 1][j]) {
                dp[i + 1][j] = (dp[i][j] | b[i + 1]);
                fr[i + 1][j] = j;
            }
            if (dp[i][j] > dp[i + 1][j ^ b[i + 1]]) {
                dp[i + 1][j ^ b[i + 1]] = dp[i][j];
                fr[i + 1][j ^ b[i + 1]] = j;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < maxn; ++i) {
        if (i + dp[sz][i] > res) {
            res = i + dp[sz][i];
            bst = i;
        }
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int ans = calc(0), p = 0;
    for (int i = 1; i <= n; ++i) {
        int tans = calc(i) + a[i];
        if (tans > ans) {
            ans = tans;
            p = i;
        }
    }
    printf("%d\n", ans);
    calc(p);
    vector<int> xo, oo;
    int x = sz, y = bst;
    while (x) {
        int t = fr[x][y];
        if (t == y) oo.push_back(b[x]);
        else xo.push_back(b[x]);
        --x, y = t;
    }
    reverse(xo.begin(), xo.end());
    reverse(oo.begin(), oo.end());
    printf("%d", xo.size());
    for (int i : xo) printf(" %d", i); puts("");
    printf("%d", oo.size());
    for (int i : oo) printf(" %d", i); puts("");
    if (p == 0) puts("0");
    else printf("1 %d\n", a[p]);
    return 0;
}
