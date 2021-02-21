#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int64_t> f(N);
    for (int i = 0; i < N; ++i) cin >> f[i];
    vector<int> last(50, -1);
    vector<int64_t> dp(N);

    int64_t pref = 0;
    for (int i = 0; i < N; ++i) {
        for (int bit = 0; bit < 50; ++bit) {
            if (f[i] >> bit & 1) {
                if (last[bit] >= 0) {
                    dp[i] = max(dp[i], dp[last[bit]] + (f[i] & f[last[bit]]));
                }
                last[bit] = i;
            }
        }
        dp[i] = max(dp[i], pref);
        pref = dp[i];
    }
    cout << dp[N - 1] << "\n";
}

