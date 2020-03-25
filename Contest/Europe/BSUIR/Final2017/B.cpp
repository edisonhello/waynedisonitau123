#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long sum = 0;
    for (int i : a) sum += i;
    long long ans = LLONG_MAX;
    if ((sum & 1) == 0 && sum >= 0) ans = sum;
    for (long long i : a) {
        if (i == 0) continue;
        long long tsum = sum - i;
        long long k = -tsum / i;
        for (long long kk = k - 5; kk <= k + 5; ++kk) {
            long long tmp = tsum + i * kk;
            if (tmp & 1);
            else if (tmp < 0);
            else ans = min(ans, tmp);
        }
    }

    if (ans == LLONG_MAX) cout << "-1" << endl;
    else cout << ans << endl;
}

