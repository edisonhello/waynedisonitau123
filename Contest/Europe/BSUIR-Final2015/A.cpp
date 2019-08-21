#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;



int main() {
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();
    if (m > n) {
        cout << 0 << endl;
        exit(0);
    }
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    while (t.size() < s.size()) t += "0";
    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < s[i]; ++j) if (j >= t[i]) {
            long long add = 1;
            for (int k = i - 1; k >= 0; --k) {
                add *= ('9' + 1 - t[k]);
                add %= mod;
            }
            ans += add;
        }
        if (s[i] < t[i]) break;
    }
    /* if (t[n - 1] == '0') {
        long long add = 1;
        for (int k = n - 2; k >= 0; --k) {
            add *= ('9' + 1 - t[k]);
            add %= mod;
        }
        ans += add;
    } */
    int add = 1;
    for (int i = 0; i < n; ++i) if (s[i] < t[i]) add = 0;
    if (add) ++ans;
    cout << ans % mod << endl;
}
