#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int a[3], b[3];
        for (int i = 0; i < 3; ++i) scanf("%d", &a[i]);
        for (int i = 0; i < 3; ++i) scanf("%d", &b[i]);
        for (long long x = 1; ; ++x) {
            long long x3 = x * x * x;
            bool ok = true;
            for (int i = 0; i < 3; ++i) ok &= x3 % a[i] == b[i];
            if (ok) {
                printf("%lld\n", x);
                break;
            }
        }
    }
}
