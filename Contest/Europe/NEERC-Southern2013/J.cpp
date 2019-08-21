#include <bits/stdc++.h>
using namespace std;

const int maxn = 30 + 5;
const int maxk = 1e4 + 5;
int s[maxn], t[maxn];
int l[maxk], r[maxk];
int dp[maxn][maxn][maxk], ss[maxk];
int c[maxk], b[maxk], doo[maxn][maxk];
pair<int, int> pp[maxk];
tuple<int, int, int> fr[maxn][maxn][maxk];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &s[i], &t[i]), pp[i] = make_pair(t[i], s[i]);
    vector<int> vv(n);
    iota(vv.begin(), vv.end(), 1);
    sort(vv.begin(), vv.end(), [&](int i, int j) { return make_pair(t[i], s[i]) < make_pair(t[j], s[j]); });
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &l[i], &r[i]);
        for (int j = l[i]; j < r[i]; ++j)
            c[j] = 1;
    }

    sort(pp + 1, pp + n + 1);
    for (int i = 1; i <= n; ++i) s[i] = pp[i].second, t[i] = pp[i].first;

    int ans = 0, opt = 0;
    vector<int> select;
    for (int z = 1; z <= n; ++z) {
        int p = z;
        memset(b, 0, sizeof(b));
        vector<int> choose;
        for (int j = 10000; j >= 0; --j) {
            if (c[j] && p > 0) {
                p--;
                b[j] = 1;
                choose.push_back(j);
            }
        }
        reverse(choose.begin(), choose.end());
        if (p > 0) break;
        for (int i = 1; i <= 10000; ++i) ss[i] = ss[i - 1] + b[i];
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= 10000; ++j) {
                doo[i][j] = j + t[i] - 1;
                while (doo[i][j] <= 10000 && doo[i][j] + 1 - j - (ss[doo[i][j]] - (j ? ss[j - 1] : 0)) < t[i]) ++doo[i][j];
                if (doo[i][j] > 10000 || doo[i][j] + 1 - j - (ss[doo[i][j]] - (j ? ss[j - 1] : 0)) < t[i]) doo[i][j] = -1;
            }
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= 10000; ++k)
                    dp[i][j][k] = -1e9;
            }
        }
        dp[0][0][0] = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= z; ++j) {
                for (int k = 0; k <= 10000; ++k) {
                    if (dp[i][j][k] > dp[i][j][k + 1]) {
                        dp[i][j][k + 1] = dp[i][j][k];
                        fr[i][j][k + 1] = make_tuple(i, j, k);
                    }
                    if (i == n) continue;
                    if (dp[i][j][k] > dp[i + 1][j][k]) {
                        dp[i + 1][j][k] = dp[i][j][k];
                        fr[i + 1][j][k] = make_tuple(i, j, k);
                    }
                    dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);
                    int nxt = doo[i + 1][k];
                    if (b[k]) continue;
                    if (j < z && nxt != -1) {
                        if (nxt > choose[j]) continue;
                        ++nxt;
                        int td = dp[i][j][k] + s[i + 1];
                        if (td > dp[i + 1][j + 1][nxt]) {
                            dp[i + 1][j + 1][nxt] = td;
                            fr[i + 1][j + 1][nxt] = make_tuple(i, j, k);
                        }
                    }
                }
            }
        }
        if (dp[n][z][10000] > ans) {
            ans = dp[n][z][10000];
            opt = z;
            vector<int> kz;
            for (int i = n, j = z, k = 10000; i > 0; tie(i, j, k) = fr[i][j][k]) {
                // printf("i = %d j = %d k = %d\n", i, j, k);
                if (get<1>(fr[i][j][k]) < j) {
                    kz.push_back(vv[i - 1]);
                }
            }
            reverse(kz.begin(), kz.end());
            select = kz;
        }
    }

    vector<int> v;
    for (int i = 10000, j = opt; i >= 0 && j > 0; --i) {
        if (c[i] > 0)
            v.push_back(i), --j;
    }
    reverse(v.begin(), v.end());
    printf("%d %d\n", ans, opt);
    for (int i = 1; i <= opt; ++i) 
        printf("%d %d\n", select[i - 1], v[i - 1]);
    return 0;
}
