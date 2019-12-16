#include <bits/stdc++.h>
using namespace std;

long long pw[100];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int k; scanf("%d", &k);
        long long x; scanf("%lld", &x);
        pw[0] = 1;
        for (int i = 1; i < 100; ++i) pw[i] = pw[i - 1] * k;
        long long sum = 0;
        int z = -1;
        for (int i = 1; ; ++i) {
            sum += pw[i];
            if (sum >= x) {
                z = i;
                break;
            }
        }
        for (int i = 1; i < z; ++i) x -= pw[i];
        for (int i = 0; i < z; ++i) {
            for (int j = 0; j < k; ++j) {
                if (x <= pw[z - i - 1]) {
                    printf("%d", 10 - k + j);
                    break;
                }
                x -= pw[z - i - 1];
            }
        }
        puts("");
    }
}
