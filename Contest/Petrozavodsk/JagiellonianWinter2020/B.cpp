#include <bits/stdc++.h>
using namespace std;

int64_t Solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int64_t> dp(1 << 20);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        dp[a[i]]++;
    }
    for (int i = 0; i < 20; ++i) {
        for (int j = (1 << 20) - 1; j >= 0; --j) {
            if (j >> i & 1) {
                dp[j] += dp[j ^ (1 << i)];
            }
        }
    }
    int64_t res = 0;
    for (int i = 0; i < n; ++i) {
        res += dp[a[i]];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) cout << Solve() << "\n";
}

