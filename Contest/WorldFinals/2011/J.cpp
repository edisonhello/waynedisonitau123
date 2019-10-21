#include <bits/stdc++.h>
using namespace std;
 
const int kN = 1'000'000 + 1;
string cname[kN];
 
string High(int n) {
    stringstream ss;
    ss << n;
    string res = "";
    ss >> res;
    res += 'H';
    return res;
}
 
string Low(int n) {
    stringstream ss;
    ss << n;
    string res = "";
    ss >> res;
    res += 'L';
    return res;
}
 
vector<int> Generate() {
    vector<int> res;
    for (int n = 2; ; ++n) {
        int k = n * (n + 1) * (2 * n + 1) / 6;
        if (k >= kN) break;
        res.push_back(k);
        cname[k] = High(n);
    }
    for (int n = 1; ; ++n) {
        int k = 2 * (n + 1) * (n + 2) * (2 * n + 3) / 3;
        if (k >= kN) break;
        res.push_back(k);
        cname[k] = Low(2 * (n + 1));
    }
    for (int n = 1; ; ++n) {
        int k = (n + 1) * (2 * n + 1) * (2 * n + 3) / 3;
        if (k >= kN) break;
        res.push_back(k);
        cname[k] = Low(2 * n + 1);
    }
    sort(res.begin(), res.end(), greater<int>());
    return res;
}
 
int dp[kN];
vector<int> zp[kN];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    auto v = Generate();
    fill(dp, dp + kN, 1e9);
    dp[0] = 0;
    for (int u : v) {
        for (int j = kN - 1; j >= u; --j) {
            if (dp[j - u] + 1 < dp[j]) {
                dp[j] = dp[j - u] + 1;
                zp[j] = zp[j - u];
                zp[j].push_back(u);
            } else if (dp[j - u] + 1 == dp[j]) {
                vector<int> tmp(zp[j - u].begin(), zp[j - u].end());
                tmp.push_back(u);
                if (tmp > zp[j]) zp[j] = tmp;
            }
        }
    }
    int c, tc = 0;
    while (cin >> c) {
        if (!c) break;
        cout << "Case " << (++tc) << ": ";
        if (dp[c] > kN) {
            cout << "impossible\n";
            continue;
        }
        for (auto k : zp[c]) cout << cname[k] << ' ';
        cout << "\n";
    }
}
