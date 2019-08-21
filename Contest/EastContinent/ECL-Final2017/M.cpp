#include <bits/stdc++.h>
using namespace std;

int a[5];

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        for (int i = 0; i < 5; ++i) scanf("%d", &a[i]);
        int n; scanf("%d", &n);
        long long sum = 0;
        while (n--) {
            int x; scanf("%d", &x);
            if (x <= 48) sum += a[0];
            else if (x <= 56) sum += a[1];
            else if (x <= 60) sum += a[2];
            else if (x <= 62) sum += a[3];
            else sum += a[4];
        }
        printf("Case #%d: %lld\n", tc, sum * 10000);
    }
}
