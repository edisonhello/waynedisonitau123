#include <bits/stdc++.h>
using namespace std;

const long long mod = 100000007;

int main() {
    int t; cin >> t; while (t--) {
        long long x; cin >> x; x %= mod;
        long long ans = (155136880301 % mod) * x % mod * x % mod - (998244353 % mod) * x % mod + 71227122 % mod;
        cout << (ans % mod + mod) % mod << '\n';
    }
}
