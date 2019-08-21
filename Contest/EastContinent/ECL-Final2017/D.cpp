#include <bits/stdc++.h>
using namespace std;

long long concate(long long x, long long y) {
    long long mult = 1;
    long long z = y;
    while (y > 0) mult *= 10, y /= 10;
    if (1.0 * x * mult > 1000000000000000000) return 1000000000000000000;
    return x * mult + z;
}

vector<long long> goods;

void precalc() {
    for (int p = 1; p <= 1000000; ++p) {
        for (int q = p + 1; 1LL * p * q <= 1000000; ++q) {
            if (__gcd(p, q) > 1) continue;
            // printf("p = %d q = %d\n", p, q);
            long long s = p * 1LL * p;
            for (int i = 1; s * i <= 1000000000000000; ++i) {
                long long z = s * i;
                long long x = concate(concate(z, z / p * q), z / p / p * q * q);
                if (x > 1000000000000000) break;
                goods.push_back(x);
                z = z / p / p * q * q;
                while (z % p == 0) {
                    x = concate(x, z / p * q);
                    if (x > 1000000000000000) break;
                    goods.push_back(x); 
                    z /= p;
                    z *= q;
                }
            }
        }
    }
    sort(goods.begin(), goods.end());
    goods.resize(unique(goods.begin(), goods.end()) - goods.begin());
}

int main() {
    precalc();
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        long long l, r; scanf("%lld%lld", &l, &r);
        printf("Case #%d: %d\n", tc, (int)(upper_bound(goods.begin(), goods.end(), r) - lower_bound(goods.begin(), goods.end(), l)));
    }
}
