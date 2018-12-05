#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
const int mod1 = 1e9 + 87;
const int pr1 = 131;
const int mod2 = 998244353;
const int pr2 = 87;

char s[maxn], t[maxn];
long long dp[maxn][20][20];
tuple<int, int, int> fr[maxn][20][20];
int sen[100][100], hs1[maxn], hs2[maxn], pw1[maxn], pw2[maxn], c[maxn];
map<pair<int, int>, int> mask;

long long add(long long x, long long y) {
    long long res = x + y;
    if (res > 2e18) res = 2e18;
    return res;
}

pair<int, int> query(int l, int r) {
    return make_pair((hs1[r] - pw1[r - l + 1] * 1ll * hs1[l - 1] % mod1 + mod1) % mod1,
                     (hs2[r] - pw2[r - l + 1] * 1ll * hs2[l - 1] % mod2 + mod2) % mod2);
}


int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i) {
        int h = 0;
        scanf("%s", t);
        int z = strlen(t);
        int h1 = 0, h2 = 0;
        for (int j = 0; j < z; ++j) h1 = (h1 * 1ll * pr1 + t[j]) % mod1;
        for (int j = 0; j < z; ++j) h2 = (h2 * 1ll * pr2 + t[j]) % mod2;
        int c, p = 0, x; scanf("%d", &c);
        while (c--) scanf("%d", &x), p |= (1 << (x - 1));
        mask[make_pair(h1, h2)] = p;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &c[i]);
        for (int j = 1; j <= c[i]; ++j) scanf("%d", &sen[i][j]), --sen[i][j];
    }
    dp[0][0][0] = 1;
    scanf("%s", s + 1);
    int l = strlen(s + 1);
    for (int i = 1; i <= l; ++i) hs1[i] = (hs1[i - 1] * 1ll * pr1 + s[i]) % mod1;
    for (int i = 1; i <= l; ++i) hs2[i] = (hs2[i - 1] * 1ll * pr2 + s[i]) % mod2;
    pw1[0] = 1;
    for (int i = 1; i < maxn; ++i) pw1[i] = pw1[i - 1] * 1ll * pr1 % mod1;
    pw2[0] = 1;
    for (int i = 1; i < maxn; ++i) pw2[i] = pw2[i - 1] * 1ll * pr2 % mod2;
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= c[j]; ++k) {
                if (dp[i][j][k] == 0) continue;
                // printf("dp[%d][%d][%d] = %lld\n", i, j, k, dp[i][j][k]);
                if (j == 0) {
                    for (int t = 1; t <= m; ++t) {
                        for (int f = 1; f <= 20; ++f) {
                            if (i + f > l) continue;
                            auto h = query(i + 1, i + f);
                            if (mask.find(h) != mask.end() && (mask[h] >> (sen[t][1]) & 1)) {
                                if (1 == c[t]) {
                                    dp[i + f][0][0] = add(dp[i + f][0][0], dp[i][j][k]);
                                    fr[i + f][0][0] = make_tuple(i, j, k);
                                } else {
                                    dp[i + f][t][1] = add(dp[i + f][t][1], dp[i][j][k]);
                                    fr[i + f][t][1] = make_tuple(i, j, k);
                                }
                            }
                        }
                    }
                } else {
                    for (int f = 1; f <= 20; ++f) {
                        if (i + f > l) continue;
                        auto h = query(i + 1, i + f);
                        if (mask.find(h) != mask.end() && (mask[h] >> (sen[j][k + 1]) & 1)) {
                            if (k + 1 == c[j]) {
                                dp[i + f][0][0] = add(dp[i + f][0][0], dp[i][j][k]);
                                fr[i + f][0][0] = make_tuple(i, j, k);
                            } else {
                                dp[i + f][j][k + 1] = add(dp[i + f][j][k + 1], dp[i][j][k]);
                                fr[i + f][j][k + 1] = make_tuple(i, j, k);
                            }
                        }
                    }
                }
            }
        }
    }
    if (dp[l][0][0] > 1000000000000000000ll) puts("TOO MANY");
    else printf("%lld\n", dp[l][0][0]);
    if (dp[l][0][0]) {
        int a = l, b = 0, c = 0;
        vector<string> v;
        while (a) {
            int x, y, z; tie(x, y, z) = fr[a][b][c];
            string p = "";
            for (int i = x + 1; i <= a; ++i) p += s[i];
            if (b == 0) p += '.';
            v.push_back(p);
            a = x;
            b = y;
            c = z;
        }
        reverse(v.begin(), v.end());
        for (string t : v) cout << t << ' ';
        cout << endl;
    }
}
