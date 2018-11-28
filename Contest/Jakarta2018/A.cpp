#include <bits/stdc++.h>
using namespace std;

int dp[100][100];

int check(string s, string t) {
    int n = s.size();
    s = "." + s, t = "." + t;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) dp[i][j] = 1e9;
    }
    dp[0][0] = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i + 1 <= n) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
            if (j + 1 <= n) dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
            if (i + 1 <= n && j + 1 <= n) {
                if (s[i + 1] == t[j + 1]) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 0);
                if (s[i + 1] != t[j + 1]) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 1);
            }
        }
    }
    cout << dp[n][n] << endl;
    return dp[n][n];
}

int cnt[2];

int main() {
    string s; cin >> s;
    string t = "";
    for (int i = 0; i < s.size(); ++i) ++cnt[s[i] - '0'];
    if (cnt[0] != cnt[1]) {
        if (cnt[0] < cnt[1]) {
            for (int i = 0; i < s.size(); ++i) t += '0';
        } else {
            for (int i = 0; i < s.size(); ++i) t += '1';
        }
    } else {
        if (s[0] == '1') {
            t += '0';
            for (int i = 0; i + 1 < s.size(); ++i) t += '1';
        } else {
            t += '1';
            for (int i = 0; i + 1 < s.size(); ++i) t += '0';
        }
    }
    cout << t << endl;
}
