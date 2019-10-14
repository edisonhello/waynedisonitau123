#include <bits/stdc++.h>
using namespace std;



int main() {
    long long n; cin >> n;
    long long ans = 0;

    // r = 1 case
    for (long long r = 2; r <= n; ++r) {
        long long rk = 1;
        for (long long k = 1; ; ++k) {
            rk *= r;
            if ((rk - 1) % (r - 1) == 0 && k > 1 && n % ((rk - 1) / (r - 1)) == 0) {
                // cout << "r = " << r << ", k = " << k << ", a = " << (rk - 1) / (r - 1) << endl;
                ++ans;
            }
            if (rk > n) break;
        }
    }
    for (int i = 2; i <= n; ++i) if (n % i == 0) {
        // cout << "r = 1, k = " << i << endl;
        ++ans;
    }
    cout << ans << endl;
}
