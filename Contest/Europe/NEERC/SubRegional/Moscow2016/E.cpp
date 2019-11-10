#include <bits/stdc++.h>
using namespace std;

const int kN = 1e6 + 5;
const int kInf = 1e9 + 5;
int v[kN], ln[kN], dp[kN][2][2][2];
int fr[kN][2][2][2], cs[kN][2][2][2];

string ToString(int x) {
    stringstream ss;
    ss << x;
    string res; ss >> res;
    return res;
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &v[i]);
    sort(v + 1, v + n + 1);
    for (int i = 1; i <= n; ++i) {
        int x = v[i];
        while (x > 0) x /= 10, ln[i] += 1;
    }
    for (int i = 0; i < kN; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int l = 0; l < 2; ++l)
                    dp[i][j][k][l] = kInf;
            }
        }
    }
    dp[0][0][0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int a = 0; a < 2; ++a) {
            for (int b = 0; b < 2; ++b) {
                for (int c = 0; c < 2; ++c) {
                    if (dp[i][a][b][c] == kInf) continue;
                    // printf("dp[%d][%d][%d][%d] = %d\n", i, a, b, c, dp[i][a][b][c]);
                    if (a && (b || c)) continue;
                    // keep continuous
                    if (a && binary_search(v + 1, v + n + 1, v[i + 1] - 1)) {
                        if (b || c) continue;
                        if (b && v[i + 1] % 2 == 1 && binary_search(v + 1, v + n + 1, v[i + 1] - 2) ||
                            c && v[i + 2] % 2 == 0 && binary_search(v + 1, v + n + 1, v[i + 1] - 2)) continue;
                        if (dp[i + 1][a][b][c] > dp[i][a][b][c]) {
                            dp[i + 1][a][b][c] = dp[i][a][b][c];
                            fr[i + 1][a][b][c] = a | (b << 1) | (c << 2);
                            cs[i + 1][a][b][c] = 0;
                        }
                    }
                    // end continuous
                    if (a && binary_search(v + 1, v + n + 1, v[i + 1] - 1)) {
                        if (b || c) continue;
                        if (b && v[i + 1] % 2 == 1 && binary_search(v + 1, v + n + 1, v[i + 1] - 2) ||
                            c && v[i + 2] % 2 == 0 && binary_search(v + 1, v + n + 1, v[i + 1] - 2)) continue;
                        if (dp[i + 1][0][b][c] > dp[i][a][b][c] + ln[i + 1]) {
                            dp[i + 1][0][b][c] = dp[i][a][b][c] + ln[i + 1];
                            fr[i + 1][0][b][c] = a | (b << 1) | (c << 2);
                            cs[i + 1][0][b][c] = 1;
                        }
                    }
                    // keep odd
                    if (b && binary_search(v + 1, v + n + 1, v[i + 1] - 2) && v[i + 1] % 2 == 1) {
                        if (a && binary_search(v + 1, v + n + 1, v[i + 1] - 1)) continue;
                        if (dp[i + 1][a][b][c] > dp[i][a][b][c]) {
                            dp[i + 1][a][b][c] = dp[i][a][b][c];
                            fr[i + 1][a][b][c] = a | (b << 1) | (c << 2);
                            cs[i + 1][a][b][c] = 2;
                        }
                    }
                    // end odd
                    if (b && binary_search(v + 1, v + n + 1, v[i + 1] - 2) && v[i + 1] % 2 == 1) {
                        if (a && binary_search(v + 1, v + n + 1, v[i + 1] - 1)) continue;
                        if (dp[i + 1][a][0][c] > dp[i][a][b][c] + ln[i + 1]) {
                            dp[i + 1][a][0][c] = dp[i][a][b][c] + ln[i + 1];
                            fr[i + 1][a][0][c] = a | (b << 1) | (c << 2);
                            cs[i + 1][a][0][c] = 3;
                        }
                    }
                    // keep even
                    if (c && binary_search(v + 1, v + n + 1, v[i + 1] - 2) && v[i + 1] % 2 == 0) {
                        if (a && binary_search(v + 1, v + n + 1, v[i + 1] - 1)) continue;
                        if (dp[i + 1][a][b][c] > dp[i][a][b][c]) {
                            dp[i + 1][a][b][c] = dp[i][a][b][c];
                            fr[i + 1][a][b][c] = a | (b << 1) | (c << 2);
                            cs[i + 1][a][b][c] = 4;
                        }
                    }
                    // end even
                    if (c && binary_search(v + 1, v + n + 1, v[i + 1] - 2) && v[i + 1] % 2 == 0) {
                        if (a && binary_search(v + 1, v + n + 1, v[i + 1] - 1)) continue;
                        if (dp[i + 1][a][b][0] > dp[i][a][b][c] + ln[i + 1]) {
                            dp[i + 1][a][b][0] = dp[i][a][b][c] + ln[i + 1];
                            fr[i + 1][a][b][0] = a | (b << 1) | (c << 2);
                            cs[i + 1][a][b][0] = 5;
                        }
                    }
                    {
                        // start continous
                        bool bad = a ||
                            b && (v[i + 1] % 2 == 1) ||
                            c && (v[i + 1] % 2 == 0);
                        if (!bad) {
                            if (dp[i][a][b][c] + ln[i + 1] + 2 < dp[i + 1][1][b][c]) {
                                dp[i + 1][1][b][c] = dp[i][a][b][c] + ln[i + 1] + 2;
                                fr[i + 1][1][b][c] = a | (b << 1) | (c << 2);
                                cs[i + 1][1][b][c] = 6;
                            }
                        }
                    }
                    {
                        // start odd
                        bool bad = a ||
                            b && (v[i + 1] % 2 == 1) ||
                            c && (v[i + 1] % 2 == 0);
                        if (!bad && v[i + 1] % 2 == 1) {
                            if (dp[i][a][b][c] + ln[i + 1] + 2 < dp[i + 1][a][1][c]) {
                                dp[i + 1][a][1][c] = dp[i][a][b][c] + ln[i + 1] + 2;
                                fr[i + 1][a][1][c] = a | (b << 1) | (c << 2);
                                cs[i + 1][a][1][c] = 7;
                            }
                        }
                    }
                    {
                        // start even
                        bool bad = a ||
                            b && (v[i + 1] % 2 == 1) ||
                            c && (v[i + 1] % 2 == 0);
                        if (!bad && v[i + 1] % 2 == 0) {
                            if (dp[i][a][b][c] + ln[i + 1] + 2 < dp[i + 1][a][b][1]) {
                                dp[i + 1][a][b][1] = dp[i][a][b][c] + ln[i + 1] + 2;
                                fr[i + 1][a][b][1] = a | (b << 1) | (c << 2);
                                cs[i + 1][a][b][1] = 8;
                            }
                        }
                    }
                    {
                        // start one
                        bool bad = a ||
                            b && (v[i + 1] % 2 == 1) ||
                            c && (v[i + 1] % 2 == 0);
                        if (!bad) {
                            if (dp[i + 1][a][b][c] > dp[i][a][b][c] + ln[i + 1] + 1) {
                                dp[i + 1][a][b][c] = dp[i][a][b][c] + ln[i + 1] + 1;
                                fr[i + 1][a][b][c] = a | (b << 1) | (c << 2);
                                cs[i + 1][a][b][c] = 9;
                            }
                        }
                    }
                }
            }
        }
    }
    int a = 0, b = 0, c = 0;
    string ans = "";
    int x = 0, y = 0, z = 0;
    for (int i = n; i > 0; --i) {
        // printf("a = %d b = %d c = %d\n", a, b, c);
        // printf("case = %d\n", cs[i][a][b][c]);
        switch (cs[i][a][b][c]) {
            case 0:
            case 2:
            case 4:
                break;
            case 1:
                x = v[i];
                break;
            case 3:
                y = v[i];
                break;
            case 5:
                z = v[i];
                break;
            case 6:
                ans += "," + ToString(v[i]) + '-' + ToString(x);
                break;
            case 7:
                ans += "," + ToString(v[i]) + '#' + ToString(y);
                break;
            case 8:
                ans += "," + ToString(v[i]) + '%' + ToString(z);
                break;
            case 9:
                ans += "," + ToString(v[i]);
                break;
            default:
                assert(false);
        }
        int mask = fr[i][a][b][c];
        a = mask & 1;
        b = mask >> 1 & 1;
        c = mask >> 2 & 1;
    }
    cout << ans.substr(1) << endl;
    return 0;
}
