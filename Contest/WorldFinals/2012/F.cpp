#include <bits/stdc++.h>
using namespace std;

const int kN = 26;
const int kInf = 1'000'000'000;
vector<int> g[kN];
int a[kN], b[kN], dp[kN][2], aa[kN], bb[kN], dg[kN];
bool v[kN], used[kN], ccc[kN];

void Dfs(int x, int p) {
    v[x] = true;
    dp[x][0] = dp[x][1] = 0;
    aa[x] = a[x], bb[x] = b[x];
    ccc[x] = a[x] == b[x];
    for (int u : g[x]) {
        if (u == p) continue;
        Dfs(u, x);
        dp[x][0] += min(dp[u][0], 1 + dp[u][1]);
        dp[x][1] += min(dp[u][1], 1 + dp[u][0]);
        aa[x] += aa[u];
        bb[x] += bb[u];
        ccc[x] &= ccc[u];
    }
    if (a[x] > b[x]) dp[x][1] = kInf;
    else if (b[x] > a[x]) dp[x][0] = kInf;
}

int main() {
    char s[3];
    int tc = 0;
    while (scanf("%s", s) != EOF) {
        for (int i = 0; i < kN; ++i) g[i].clear();
        for (int i = 0; i < kN; ++i) a[i] = b[i] = aa[i] = dg[i] = bb[i] = 0;
        for (int i = 0; i < kN; ++i) used[i] = false;
        int c = 0, d = 0;
        while (strlen(s) == 2) {
            if (s[0] >= 'A' && s[0] <= 'Z') swap(s[0], s[1]);
            assert(s[0] >= 'a' && s[0] <= 'z');
            if (s[1] >= 'A' && s[1] <= 'Z') {
                int x = s[0] - 'a';
                if (s[1] <= 'M') ++a[x], ++c;
                else ++b[x], ++d;
                used[x] = true;
            } else {
                int x = s[0] - 'a';
                int y = s[1] - 'a';
                g[x].push_back(y);
                g[y].push_back(x);
                used[x] = used[y] = true;
                ++dg[x], ++dg[y];
            }
            scanf("%s", s);
        }
        for (int i = 0; i < kN; ++i) v[i] = false;
        int ans = 0;
        int ac = 0, bc = 0;
        printf("Case %d: ", ++tc);
        int kv = 0;
        for (int i = 0; i < kN; ++i) {
            if (!used[i]) continue;
            if (a[i] > b[i]) ac++;
            else if (b[i] > a[i]) bc++;
        }
        for (int i = 0; i < kN; ++i) {
            if (!used[i]) continue;
            kv += min(a[i], b[i]);
        }
        int cc = 0, gcc = 0, D = 0, cccc = 0;
        for (int i = 0; i < kN; ++i) {
            if (v[i] || !used[i]) continue;
            Dfs(i, -1);
            cc++;
            if (aa[i] > 0 || bb[i] > 0) gcc++;
            int res = min(dp[i][0], dp[i][1]);
            cccc += ccc[i];
            D += res;
            // ans += res + (res + 1) - 2;
            // printf("dp[%d][0] = %d dp[%d][1] = %d\n", i, dp[i][0], i, dp[i][1]);
        }
        int nu = 0;
        for (int i = 0; i < kN; ++i) nu += used[i];
        if (c == 0 && d == 0) {
            printf("0 0\n");
        } else if (c == 0 || d == 0) {
            assert(ans == 0);
            printf("%d %d\n", 0, gcc - 1);
        } else if (nu == 1) {
            puts("impossible");
        } else if (ac == 0) {
            int r = kInf, dd = -1, w = -1;
            for (int i = 0; i < kN; ++i) {
                if (!used[i]) continue;
                if (b[i] - a[i] < r) {
                    r = b[i] - a[i];
                    dd = dg[i];
                    w = i;
                } else if (b[i] - a[i] == r) {
                    if (dg[i] < dd) {
                        dd = dg[i];
                        w = i;
                    }
                }
            }
            int res = 0;
            for (int i = 0; i < kN; ++i) {
                if (!used[i]) continue;
                if (i == w) res += b[i];
                else res += a[i];
            }
            if (cc > gcc)
                printf("%d %d\n", 2 * res, gcc - 1);
            else if (cccc > 0 && gcc > 1) 
                printf("%d %d\n", 2 * res, gcc - 2);
            else if (dd == 0) 
                printf("%d %d\n", 2 * res, gcc - 2);
            else 
                printf("%d %d\n", 2 * res, gcc - 2 + 2 * dd);
        } else if (bc == 0) {
            int r = kInf, dd = -1, w = -1;
            for (int i = 0; i < kN; ++i) {
                if (!used[i]) continue;
                if (a[i] - b[i] < r) {
                    r = a[i] - b[i];
                    dd = dg[i];
                    w = i;
                } else if (a[i] - b[i] == r) {
                    if (dg[i] < dd) {
                        dd = dg[i];
                        w = i;
                    }
                }
            }
            int res = 0;
            for (int i = 0; i < kN; ++i) {
                if (!used[i]) continue;
                if (i == w) res += a[i];
                else res += b[i];
            }
            if (cc > gcc)
                printf("%d %d\n", 2 * res, gcc - 1);
            else if (cccc > 0 && gcc > 1) 
                printf("%d %d\n", 2 * res, gcc - 2);
            else if (dd == 0) 
                printf("%d %d\n", 2 * res, gcc - 1);
            else
                printf("%d %d\n", 2 * res, gcc - 2 + 2 * dd);
        } else {
            printf("%d %d\n", 2 * kv, D + gcc + D - 2);
        }
    }
    return 0;
}

