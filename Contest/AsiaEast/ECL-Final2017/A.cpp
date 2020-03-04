#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw(int b, int n, int m = mod, int a = 1) {
    while (n) {
        if (n & 1) a = 1ll * a * b % m;
        b = 1ll * b * b % m; n >>= 1;
    } return a;
}

int inv(int x) { return pw(x, mod - 2); } 

int main() {
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int n, k; cin >> n >> k;
        int mx = pw(2, n);
        int now = 1;
        for (int i = 0; i < k; ++i) {
            mx -= now;
            if (mx < 0) mx += mod;
            now = now * 1ll * inv(i + 1) % mod * (n - i) % mod;
        }
        cout << mx << endl;
    }
}
