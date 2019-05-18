#include <bits/stdc++.h>
using namespace std;

long long a[50];

int main() {
    int r; long long p;
    while (scanf("%d %lld", &r, &p) == 2) {
        if (r == 0 && p == 0) break;
        for (int i = 0; i < r; ++i) scanf("%lld", &a[i]);
        vector<long long> v;
        int x = r / 2, y = r - x;
        for (int i = 0; i < (1 << x); ++i) {
            long long c = 0;
            for (int j = 0; j < x; ++j) if (i >> j & 1) c += a[j];
            v.push_back(c);
        }
        sort(v.begin(), v.end());
        long long ans = 0;
        for (int i = 0; i < (1 << y); ++i) {
            long long c = 0;
            for (int j = 0; j < y; ++j) if (i >> j & 1 ) c += a[j + x];
            ans += upper_bound(v.begin(), v.end(), p - c) - v.begin();
        }
        printf("%lld\n", ans);
    }
}

