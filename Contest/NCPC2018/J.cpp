#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        int d, e, f; scanf("%d%d%d", &d, &e, &f);
        int ans = -1;
        for (int i = 0; i <= 3000000; ++i) {
            if (i % d == a && i % e == b && i % f == c) {
                ans = i;
                break;
            }
        }
        printf("%d\n", ans);
    }
}
