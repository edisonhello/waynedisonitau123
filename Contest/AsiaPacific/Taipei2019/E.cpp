#include <bits/stdc++.h>
using namespace std;

const int kN = 2000 + 5;
const long long kInf = 1'000'000'000'000'000'000;
long long a[kN];

long long Check(int n) {
    long long res = -kInf;
    for (int l = 1; l <= n; ++l) {
        long long sum = 0;
        for (int r = l; r <= n; ++r) {
            sum += a[r];
            if (sum * (r - l + 1) > res) res = sum * (r - l + 1);
        }
    }
    return res;
}

long long Stupid(int n) {
    long long result = 0;
    long long curmax = 0;
    int left = 0;
    for (int i = 1; i <= n; ++i) {
        curmax += a[i];
        if (curmax < 0) {
            curmax = 0;
            left = i;
        }
        result = max(result, (i - left) * curmax);
    }
    return result;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int k, l; scanf("%d%d", &k, &l);
        if (l >= 2000) {
            puts("-1");
            continue;
        }
        for (int i = 1; i <= 1997; ++i) a[i] = 0;
        int aa = 1998 - k % 1998;
        a[1998] = -aa;
        assert((aa + k) % 1998 == 0);
        int bb = (aa + k) / 1998 + aa;
        a[1999] = bb;
        // for (int i = 3; i < 2000; ++i) a[i] = -(k + 3);
        printf("1999\n");
        for (int i = 1; i <= 1999; ++i) printf("%lld ", a[i]);
        puts("");
        // printf("Check = %lld\n", Check(1999));
        // printf("Stupid = %lld\n", Stupid(1999));
        assert(Check(1999) - Stupid(1999) == k);
    }
}
