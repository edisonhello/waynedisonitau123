#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000 + 5;
double dp[maxn][maxn];
bool v[maxn][maxn], v2[maxn], v3[maxn];
double dp2[maxn], pb[maxn], dp3[maxn];
vector<int> p[maxn];
int d, b, eval[maxn], pc[maxn], pw[maxn][11];

double dfs3(int x) {
    if (!pc[x])
        return 1.0 - pb[x];

    if (v3[x])
        return dp3[x];

    dp3[x] = 0.0;
    for (int i = 0; i < b; ++i) {
        double pr = 1. / b;
        double g = -1.0;
        for (int j = 0; j < d; ++j) {
            if (p[x][j] >= 0) continue;
            double d = dfs3(x - pw[j][b] + pw[j][i]);
            g = max(g, d);
        }
        dp3[x] += pr * g;
    }
    
    v3[x] = true;
    // printf("dp3[%d] = %.5lf\n", x, dp3[x]);
    return dp3[x];
}

double dfs2(int x, int y) {
    if (!pc[x]) {
        return x >= y;
    }
    if (v2[x])
        return dp2[x];

    dp2[x] = 0.0;
    for (int i = 0; i < b; ++i) {
        double pr = 1. / b;
        double g = -1.0;
        for (int j = 0; j < d; ++j) {
            if (p[x][j] >= 0) continue;
            double d = dfs2(x - pw[j][b] + pw[j][i], y);
            g = max(g, d);
        }

        dp2[x] += pr * g;
    }

    v2[x] = true;
    return dp2[x];
}

double dfs(int x, int y) {
    if (!pc[x] && !pc[y]) {
        return x > y;
    }
    if (v[x][y]) 
        return dp[x][y];

    int z = (d - pc[x] + d - pc[y]) & 1;
    int s = z ? y : x;

    dp[x][y] = 0.0;
    for (int i = 0; i < b; ++i) {
        double pr = 1. / b;
        double g = z ? 1.0 : -1.0;
        int cnt = 0;

        for (int j = 0; j < d; ++j) {
            if (p[s][j] >= 0) continue;
            ++cnt;
            double d = z ? dfs(x, y - pw[j][b] + pw[j][i]) : dfs(x - pw[j][b] + pw[j][i], y);
            z ? assert(pc[y - pw[j][b] + pw[j][i]] == pc[y] - 1) : assert(pc[x - pw[j][b] + pw[j][i]] == pc[x] - 1);
            if (z) g = min(g, d);
            else g = max(g, d);
        }

        assert(cnt > 0);
        dp[x][y] += pr * g;
    }

    // printf("dp[%d][%d] = %.5lf\n", x, y, dp[x][y]);

    v[x][y] = true;
    return dp[x][y];
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("greater.in", "r", stdin);
    freopen("greater.out", "w", stdout);
#endif

    while (scanf("%d%d", &d, &b) != EOF) {
        if (d == 0 && b == 0) break;
        int pd = 1;
        for (int i = 0; i < d; ++i) pd *= (b + 1);
        // printf("pd = %d\n", pd);
        assert(pd <= 3000);

        for (int i = 0; i < pd; ++i) {
            for (int j = 0; j < pd; ++j) 
                v[i][j] = false;
                
            p[i].clear();
        }

        for (int i = 0; i <= b; ++i) {
            for (int j = 0; j < d; ++j) {
                pw[j][i] = i;
                for (int k = 0; k < j; ++k)
                    pw[j][i] *= (b + 1);
            }
        }

        for (int i = 0, j = 0; i < pd; ++i) {
            j = i;
            for (int k = 0; k < d; ++k) {
                int z = j % (b + 1);
                if (z == b) p[i].push_back(-1);
                else p[i].push_back(z);
                j /= (b + 1);
            }
            pc[i] = 0;
            for (int j = 0; j < (int)p[i].size(); ++j)
                pc[i] += p[i][j] == -1;

            /* for (int j = 0; j < (int)p[i].size(); ++j)
                printf("p[%d][%d] = %d ", i, j, p[i][j]);
            puts(""); */
        }

        int init = 0;
        for (int i = 0; i < d; ++i) 
            init = init * (b + 1) + b;

        double ans1 = dfs(init, init);

        int mxv = 0;
        for (int i = 0; i < d; ++i) mxv = mxv * (b + 1) + b - 1;
        for (int i = 0; i <= mxv; ++i) {
            for (int j = 0; j < pd; ++j) v2[j] = false;
            pb[i] = dfs2(init, i);
            // printf("pb[%d] = %.20lf\n", i, pb[i]);
        }

        for (int i = 0; i < pd; ++i) v3[i] = false;
        double ans2 = dfs3(init);

        printf("%.20lf %.20lf\n", ans1, ans2);
    }
    return 0;
}
