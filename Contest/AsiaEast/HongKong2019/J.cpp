#include <bits/stdc++.h>
using namespace std;

const int kMod = 1'000'000'000 + 7;
const int kN = 5000 + 5;
const int kM = 60;
int pw[kN], dp[kN][kM][kM];
bool used[kN][kM][kM];

int Dfs(int i, int s, int v, int m) {
    // length i, sum s, differene v
    if (i == 0) {
        if (v == 0) return 1;
        return 0;
    }
    if (used[i][s][v]) return dp[i][s][v];
    dp[i][s][v] = 0;
    for (int d = 0; d < 10; ++d) {
        int ks = (s + d) % m;
        int kv = (v + (((d * pw[i - 1] - d * s) % m) + m) % m) % m;
        (dp[i][s][v] += Dfs(i - 1, ks, kv, m)) %= kMod;
    }
    used[i][s][v] = true;
    // printf("dp[%d][%d][%d] = %d\n", i, s, v, dp[i][s][v]);
    return dp[i][s][v];
}

int Solve(const string &s, int m) {
    int sum = 0, v = 0, f = 0, ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < s[i] - '0'; ++j) {
            int tsum = (sum + j) % m;
            int tv = (v + j * pw[s.size() - i - 1] % m) % m;
            int tf = (f + j * sum) % m;
            (ans += Dfs(s.size() - i - 1, tsum, (tv + m - tf) % m, m)) %= kMod;
        } 
        int d = s[i] - '0';
        (f += d * sum) %= m;
        (sum += d) %= m;
        (v += d * pw[s.size() - i - 1]) %= m;
    }
    return ans;
}

int Parse(string s) {
    stringstream ss; ss << s;
    int res; ss >> res;
    return res;
}

int Brute(string s, int m) {
    int n = Parse(s);
    int res = 0;
    for (int i = 1; i < n; ++i) {
        vector<int> d;
        for (int v = i; v > 0; v /= 10) d.push_back(v % 10);
        int f = 0;
        for (int j = 0; j < d.size(); ++j) {
            for (int k = j + 1; k < d.size(); ++k)
                f += d[j] * d[k];
        }
        if (f % m == i % m) ++res;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        string l, r; cin >> l >> r;
        bool ok = false;
        for (int i = r.size() - 1; i >= 0; --i) {
            if (r[i] == '9') {
                r[i] = '0';
            } else {
                r[i]++;
                ok = true;
                break;
            }
        }
        if (!ok) {
            // r = 99999
            int m = r.size();
            r = "1";
            for (int i = 0; i < m; ++i) r += '0';
        }
        int m; cin >> m;
        // cout << "l = " << l << " r = " << r << endl;
        pw[0] = 1;
        for (int i = 1; i <= r.size(); ++i) pw[i] = pw[i - 1] * 10 % m;
        for (int i = 0; i <= r.size(); ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < m; ++k) used[i][j][k] = false;
            }
        }
        // cout << "Solve(r) = " << Solve(r, m) << endl;
        // cout << "Brute(r) = " << Brute(r, m) << endl;
        cout << (Solve(r, m) + kMod - Solve(l, m)) % kMod << '\n';
        // cout << (Brute(r, m) + kMod - Brute(l, m)) % kMod << endl;
    }
    return 0;
}
