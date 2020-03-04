#include <bits/stdc++.h>
using namespace std;


int main() {
    int l, r; while (scanf("%d%d", &l, &r) != EOF) {
        if (l == 0 && r == 0) break;
        double ans = 0;
        for (int i = l; i <= r; ++i) {
            ans += pow(i, -2.0 / 3);
        }
        ans /= 3;
        int xp = -15;
        while (ans >= 10) {
            ans /= 10, ++xp;
        }
        while (ans < 1) {
            ans *= 10, --xp;
        }
        xp *= -1;
        printf("%.5lfE-%03d\n", ans, xp);
    }
}
