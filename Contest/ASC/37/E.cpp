#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(const string &s) {
    vector<int> f(s.size(), 0);
    int k = 0;
    for (int i = 1; i < (int)s.size(); ++i) {
        while (k > 0 && s[i] != s[k]) k = f[k - 1];
        if (s[i] == s[k]) ++k;
        f[i] = k;
    }
    return f;
}

const int maxn = 1e6 + 5;
vector<int> vf[maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s; cin >> s;
    vector<int> f = kmp(s);
    vector<int> dp(s.size(), 0);
    for (int i = 0; i < (int)s.size(); ++i) {
        if (f[i] == 0) {
            dp[i] = i + 1;
        } else {
            if (f[i] + f[i] >= (i + 1)) {
                dp[i] = dp[f[i] - 1];
            } else {
                int l = i - f[i], r = i;
                int d = dp[f[i] - 1];
                if (lower_bound(vf[d].begin(), vf[d].end(), l) != vf[d].end()) dp[i] = d;
                else dp[i] = i + 1;
            }
        }
        vf[dp[i]].push_back(i);
        cout << dp[i] << ' ';
    }
    cout << endl;
}
