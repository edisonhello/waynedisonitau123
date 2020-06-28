#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw(int b, int n) {
    int a = 1;
    while (n) {
        if (n & 1) a = 1ll * a * b % mod;
        b = 1ll * b * b % mod; n >>= 1;
    }
    return a;
}

int inv(int x) {
    return pw(x, mod - 2);
}

int fac[6000006];

int C(int n, int m) {
    // cerr << "n m " << n << ' ' << m << endl;
    return 1ll * fac[n] * inv(fac[m]) % mod * inv(fac[n - m]) % mod;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= 6000002; ++i) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
    }

    int n; cin >> n;
    if (n & 1) {
        int sum = 0;
        for (int i = 0; i <= 4; ++i) {
            int j = 9 * (n / 4) + i;
            int m = n / 2;

            if (m == 0 && j == 0){
                ++sum;
                continue;
            }

            for (int i = 0; i <= j / 10; ++i) {
                int ii = j - 10 * i;
                assert(ii >= 0);


                sum += 1ll * pw(mod - 1, i) * C(m, i) % mod * C(m + ii - 1, ii) % mod;
                if (sum >= mod) sum -= mod;
            }
        }

        cout << sum << '\n';
    } else {
        cout << pw(10, n / 2) << '\n';
    }
}
 
