#include <bits/stdc++.h>
using namespace std;

const long long inf = 100000000000000000;
int used[51];

bool check2(long long a) {
    long long sq = sqrt(a);
    while (sq * sq > a) --sq;
    while ((sq + 1) * (sq + 1) <= a) ++sq;
    return sq * sq != a;
}

bool check3(long long a) {
    long long cb = cbrt(a);
    while (cb * cb * cb > a) --cb;
    while ((cb + 1) * (cb + 1) * (cb + 1) <= a) ++cb;
    return cb * cb * cb != a;
}

long long count2(long long a) {
    long long sq = sqrt(a);
    while (sq * sq > a) --sq;
    while ((sq + 1) * (sq + 1) <= a) ++sq;
    return sq;
}

long long count3(long long a) {
    long long cb = cbrt(a);
    while (cb * cb * cb > a) --cb;
    while ((cb + 1) * (cb + 1) * (cb + 1) <= a) ++cb;
    return cb;
}

long long count6(long long a) {
    long long x = sqrt(cbrt(a));
    while (x * x * x * x * x * x > a) --x;
    while ((x + 1) * (x + 1) * (x + 1) * (x + 1) * (x + 1) * (x + 1) <= a) ++x;
    return x;
}

int main() {
    int q; scanf("%d", &q);
    while (q--) {
        long long n; scanf("%lld", &n);
        int m; scanf("%d", &m);
        memset(used, 0, sizeof(used));
        for (int i = 0; i < m; ++i) {
            int x; scanf("%d", &x);
            used[x] = 1;
        }

        if (used[1]) {
            printf("%lld\n", n);
            continue;
        }

        vector<long long> res; 
        if (!used[2] && !used[3]) res.push_back(1);
        for (long long i = 2; i * i * i * i <= inf; ++i) {
            long long x = i * i * i * i;
            if (used[4]) {
                if ((!used[2] || check2(x)) && (!used[3] || check3(x)))
                    res.push_back(x);
            }

            int z = 4;
            while (x <= inf / i) {
                z++;
                x *= i;
                if (used[z]) {
                    if ((!used[2] || check2(x)) && (!used[3] || check3(x)))
                        res.push_back(x);
                }
            }
        }

        sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());

        /* for (int i = 0; i < (int)res.size(); ++i)
            printf("%lld ", res[i]);
        puts(""); */

        long long ans = 0;
        for (int d = 60; d >= 0; --d) {
            if (ans + (1ll << d) <= inf) {
                long long tans = ans + (1ll << d);
                long long count = 0;
                if (used[2]) 
                    count += count2(tans);
                if (used[3])
                    count += count3(tans);
                if (used[2] && used[3])
                    count -= count6(tans);

                count += upper_bound(res.begin(), res.end(), tans) - res.begin();
                // printf("in list = %d\n", upper_bound(res.begin(), res.end(), tans) - res.begin());
                // printf("tans = %lld count = %lld\n", tans, count);
                if (count < n)
                    ans = tans;
            }
        }

        printf("%lld\n", ans + 1);
    }
}
