#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int main() {
    int n; cin >> n;
    int ans = 1;
    if (n & 1) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 2; i <= n; i += 2) {
        ans = (1ll * ans * (i - 1)) % mod;
    }

    int nn = n / 2;
    int mul = 1;
    for (int i = 0; i < nn - 2; ++i) mul = (1ll * mul * nn) % mod;

    for (int i = 0; i < nn - 1; ++i) mul = (1ll * mul * 4) % mod;

    cout << 1ll * mul * ans % mod << '\n';

}

