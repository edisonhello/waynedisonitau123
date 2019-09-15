#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int ans[5][20][20];

void solve() {
    int n, m, k; cin >> n >> m >> k;
    if (n > m) swap(n, m);
    if (k == 2) {
        if (n == 1) printf("%d\n", m);
        else printf("1\n");
    }
    if (k == 3) {
        if (n == 1 && m == 1) printf("1\n");
        else if (n == 1) printf("%d\n", m * (m - 1) / 2);
        else if (n == 2) printf("%lld\n", 1LL * m * (m - 1) % mod *  m * (m - 1) / 4 % mod);
        else if (n == 3) {
            if (m >= 6) printf("1\n");
            else printf("%d\n", ans[3][3][m]);
        }
        else printf("1\n");
    }
    if (k == 4) {
        if (n == 1) {
            if (m == 1 || m == 2) printf("1\n");
            else printf("%lld\n", 1LL * m * (m - 1) * (m - 2) / 6 % mod);
        } else if (n == 2) {
            if (m == 2) printf("1\n");
            else {
                int k = 1LL * m * (m - 1) * (m - 2) / 6 % mod;
                printf("%lld\n", 1LL * k * k % mod);
            }
        } else if (n == 3) {
            int k = 1LL * m * (m - 1) * (m - 2) / 6 % mod;
            printf("%lld\n", 1LL * k * k % mod * k % mod);
        } else if (n == 4) {
            if (m >= 12) printf("1\n");
            else printf("%d\n", ans[4][4][m]);
        } else if (n == 5) {
            if (m >= 8) printf("1\n");
            else printf("%d\n", ans[4][5][m]);
        } else {
            printf("1\n");
        }
    }
}

void init() {
    ans[3][3][3] = 78;
    ans[3][3][4] = 66;
    ans[3][3][5] = 15;
    ans[4][4][4] = 8442;
    ans[4][4][5] = 64320;
    ans[4][4][6] = 123600;
    ans[4][4][7] = 95088;
    ans[4][4][8] = 35672;
    ans[4][4][9] = 7140;
    ans[4][4][10] = 780;
    ans[4][4][11] = 44;
    ans[4][5][5] = 52120;
    ans[4][5][6] = 4060;
    ans[4][5][7] = 35;
}

int main() {
    init();
    int t; cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cout << "Case " << tc << ": ";
        solve();
    }
}
