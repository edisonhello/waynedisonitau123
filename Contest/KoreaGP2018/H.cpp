#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c, d; scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    long long ans = 0;
    for (int i = 1; i < 1000; ++i) {
        for (int j = 1; j < 1000; ++j) {
            if (i + j >= 1000) continue;
            if (__gcd(i, j) != 1) continue;
            // printf("i = %d j = %d\n", i, j);
            long long fi = a / i;
            if (i * fi < a) ++fi;
            if (i * fi > b) continue;
            long long fj = c / j;
            if (j * fj < c) ++fj;
            if (j * fj > d) continue;
            // printf("fi = %lld fj = %lld\n", fi, fj);
            long long si = (b + i - 1) / i;
            if (i * si > b) --si;
            assert(i * si <= b && i * si >= a);
            long long sj = (d + j - 1) / j;
            if (j * sj > d) --sj;
            assert(j * sj <= d && j * sj >= c);
            long long l = max(fi, fj), r = min(si, sj);
            if (l > r) continue;
            ans += r - l + 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
