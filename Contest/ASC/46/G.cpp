#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
const int mod = 242121643;
int a[maxn], cnk[maxn][maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#endif
    cnk[0][0] = 1;
    for (int i = 1; i < maxn; ++i) {
        cnk[i][0] = 1;
        for (int j = 1; j < maxn; ++j) {
            cnk[i][j] = (cnk[i - 1][j] + cnk[i - 1][j - 1]);
            if (cnk[i][j] >= mod) cnk[i][j] -= mod;
        }
    }
    int n, k; 
    while (scanf("%d%d", &n, &k) != EOF) {
        if (n == 0 && k == 0) break;
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        int one = 0;
        for (int i = 0; i < n; ++i) one += a[i] == 1;
        int ans = 0;
        for (int i = 1; i <= one && i <= k; i += 2) {
            int way = cnk[one][i] * 1ll * cnk[n - one][k - i] % mod;
            ans += way;
            if (ans >= mod) ans -= mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}
