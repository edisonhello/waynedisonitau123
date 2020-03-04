#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
int a[5005], pv[5005];
int dp1[5005][5005], dp2[5005][5005];
int fw1[5005][5005], fw2[5005][5005];

void Modify(int p, int v, int *fw) {
    for (int i = p + 1; i < 5005; i += i & -i)
        (fw[i] += v) %= mod;
}

int Query(int p, int *fw) {
    int res = 0;
    for (int i = p + 1; i > 0; i -= i & -i)
        (res += fw[i]) %= mod;
    return res;
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    a[n + 1] = n + 1;

    for (int i = 1; i <= n; ++i) {
        int j = i - 1;
        while (j >= 1 && a[j + 1] > a[j]) --j;
        pv[i] = j + 1;
    }

    dp1[0][1] = 1;
    // dp2[0][1] = 1;
    // dp1[i][k] = sum j from pv[i] - 1 to i - 1 and a[j] < a[i + 1]: dp2[j][j - k + 3]
    // dp2[i][k] = sum j from pv[i] - 1 to i - 1 and a[j] < a[i + 1]: dp1[j][j - k + 3]

    Modify(a[0], dp1[0][1], fw1[2]);
    int p = 0;
    for (int i = 1; i <= n; ++i) {
        /* while (p < pv[i] - 1) {
            for (int k = 1; k <= m + 2; ++k) {
                if (p - k + 3 >= 0) Modify(a[k], mod - dp1[p][k], fw1[p - k + 3]);
                if (p - k + 3 >= 0) Modify(a[k], mod - dp2[p][k], fw2[p - k + 3]);
            }
            p += 1;
        } */
        for (int k = 1; k <= m + 2; ++k) {
            // dp1[i][k] = Query(a[i] - 1, fw1[k]);
            // dp2[i][k] = Query(a[i] - 1, fw2[k]);
            for (int j = pv[i] - 1; j <= i - 1; ++j) if (a[j] < a[i + 1]) {
                (dp1[i][k] += dp2[j][j - k + 3]) %= mod;
                (dp2[i][k] += dp1[j][j - k + 3]) %= mod;
            }
        }
        for (int k = 1; k <= m + 2; ++k) {
            // if (i - k + 3 >= 0) Modify(a[i], dp1[i][k], fw1[i - k + 3]);
            // if (i - k + 3 >= 0) Modify(a[i], dp2[i][k], fw2[i - k + 3]);
            printf("dp1[%d][%d] = %d\n", i, k, dp1[i][k]);
            printf("dp2[%d][%d] = %d\n", i, k, dp2[i][k]);
        }
    }

    int ans = 0;
    for (int j = n - m + 1; j <= m + 1; ++j) (ans += dp1[n][j]) %= mod;
    for (int j = n - m + 2; j <= m + 2; ++j) (ans += dp2[n][j]) %= mod;
    
    cout << (ans + ans) % mod << endl;
}
