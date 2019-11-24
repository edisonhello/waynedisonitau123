#include <bits/stdc++.h>
using namespace std;



int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        long long mx = 0;
        for (long long a = n + 1; a <= 2 * n; ++a) {
            long long x = 1ll * a * n;
            if (x % (a - n)) continue;
            long long b = x / (a - n);
            mx = max(mx, a ^ b);
        }
        cout << mx << '\n';
    }
}
