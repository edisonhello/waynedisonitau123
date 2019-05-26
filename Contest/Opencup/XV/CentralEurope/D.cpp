#include <bits/stdc++.h>
using namespace std;

int cnt[2000005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    while (n--) {
        int t; cin >> t; ++cnt[t];
    }
    long long ans = 0;
    for (int i = 1; i <= 2000000; ++i) {
        for (int j = i * 2; j <= 2000000; j += i) {
            ans += 1ll * cnt[i] * cnt[j];
        }
        ans += 1ll * cnt[i] * (cnt[i] - 1);
    }
    cout << ans << endl;
}
