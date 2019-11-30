#include <bits/stdc++.h>
using namespace std;

const int kN = 500 + 5;
const int kInf = 1e9;
int dp[kN][kN], fr[kN][kN];
bool v[kN][kN];
char s[kN];

int Dfs(int l, int r) {
    if (v[l][r]) return dp[l][r];
    if (l == r) {
        if (s[l] == '*') return 0;
        return 1;
    }
    if (l > r) return 0;
    dp[l][r] = kInf;
    if (s[l] == '*') {
        int d = Dfs(l + 1, r);
        if (d < dp[l][r]) {
            dp[l][r] = d;
            fr[l][r] = 0;
        }
    }
    if (s[r] == '*') {
        int d = Dfs(l, r - 1);
        if (d < dp[l][r]) {
            dp[l][r] = d;
            fr[l][r] = 1;
        }
    }
    if (s[l] == '*') {
        if (s[r] == '?') {
            int d = Dfs(l, r - 1) + 2;
            if (d < dp[l][r]) {
                dp[l][r] = d;
                fr[l][r] = 2;
            }
        }
        if (s[r] >= 'a' && s[r] <= 'z') {
            int d = Dfs(l, r - 1) + 2;
            if (d < dp[l][r]) {
                dp[l][r] = d;
                fr[l][r] = 3;
            }
        }
    }
    if (s[l] == '?') {
        if (s[r] == '*') {
            int d = Dfs(l + 1, r) + 2;
            if (d < dp[l][r]) {
                dp[l][r] = d;
                fr[l][r] = 4;
            }
        }
        if (s[r] == '?') {
            int d = Dfs(l + 1, r - 1) + 2;
            if (d < dp[l][r]) {
                dp[l][r] = d;
                fr[l][r] = 5;
            }
        }
        if (s[r] >= 'a' && s[r] <= 'z') {
            int d = Dfs(l + 1, r - 1) + 2;
            if (d < dp[l][r]) {
                dp[l][r] = d;
                fr[l][r] = 6;
            }
        }
    }
    if (s[l] >= 'a' && s[l] <= 'z') {
        if (s[r] == '*') {
            int d = Dfs(l + 1, r) + 2;
            if (d < dp[l][r]) {
                dp[l][r] = d;
                fr[l][r] = 7;
            }
        }
        if (s[r] == '?') {
            int d = Dfs(l + 1, r - 1) + 2;
            if (d < dp[l][r]) {
                dp[l][r] = d;
                fr[l][r] = 8;
            }
        }
        if (s[r] == s[l]) {
            int d = Dfs(l + 1, r - 1) + 2;
            if (d < dp[l][r]) {
                dp[l][r] = d;
                fr[l][r] = 9;
            }
        }
    }
    v[l][r] = true;
    return dp[l][r];
}

int main() {
    scanf("%s", s);
    int n = strlen(s);
    int ans = Dfs(0, n - 1);
    if (ans == kInf) {
        puts("-1");
        return 0;
    }
    int l = 0, r = n - 1;
    string f = "", b = "";
    while (l <= r) {
        if (l == r) {
            if (s[l] != '*') {
                if (s[l] == '?') f += 'a';
                else f += s[l];
            }
            break;
        }
        if (fr[l][r] == 0) {
            l++;
        } else if (fr[l][r] == 1) {
            r--;
        } else if (fr[l][r] == 2) {
            f += 'a';
            b += 'a';
            r--;
        } else if (fr[l][r] == 3) {
            f += s[r];
            b += s[r];
            r--;
        } else if (fr[l][r] == 4) {
            f += 'a';
            b += 'a';
            l++;
        } else if (fr[l][r] == 5) {
            f += 'a';
            b += 'a';
            l++;
            r--;
        } else if (fr[l][r] == 6) {
            f += s[r];
            b += s[r];
            l++;
            r--;
        } else if (fr[l][r] == 7) {
            f += s[l];
            b += s[l];
            l++;
        } else if (fr[l][r] == 8) {
            f += s[l];
            b += s[l];
            l++;
            r--;
        } else {
            f += s[l];
            b += s[l];
            l++;
            r--;
        }
    }
    cout << f;
    reverse(b.begin(), b.end());
    cout << b << endl;
}
