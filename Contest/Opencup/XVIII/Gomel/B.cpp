#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t; while (t--) {
        long long n; cin >> n;
        long long L = 1, R = 1000000007;
        long long sum = 0;
        auto ok = [&] (long long k) {
            long long z = 1;
            sum = 0;
            while (z <= k) {
                sum += z * (1 + (k / z)) * (k / z) / 2;
                if (sum > n) return false;
                z <<= 1;
            }
            return true;
        };
        while (L < R) {
            long long M = (L + R + 1) >> 1;
            if (ok(M)) L = M;
            else R = M - 1;
        }
        long long k = L;
        ok(k);
        assert(ok(k));
        long long tt = 0;
        for (long long kk = k; kk; kk >>= 1) tt += kk;
        cout << (n - sum) / (k + 1) + tt << '\n';
    }
}

