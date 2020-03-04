#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
int c[kN], r[kN], sc[kN][2], sr[kN][2];

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", &r[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
    for (int i = 1; i <= n; ++i) {
        sr[i][0] = sr[i - 1][0];
        sr[i][1] = sr[i - 1][1];
        sr[i][r[i] & 1]++;
    }
    for (int i = 1; i <= n; ++i) {
        sc[i][0] = sc[i - 1][0];
        sc[i][1] = sc[i - 1][1];
        sc[i][c[i] & 1]++;
    }
    while (q--) {
        int x, y, z, w;
        scanf("%d%d%d%d", &x, &y, &z, &w);
        if ((r[x] + c[y]) % 2 == 0 && (r[z] + c[w]) % 2 == 0) {
            if (x > z) swap(x, z);
            if (y > w) swap(y, w);
            bool rw = (sr[z][0] == sr[x - 1][0] || sr[z][1] == sr[x - 1][1]);
            bool cl = (sc[w][0] == sc[y - 1][0] || sc[w][1] == sc[y - 1][1]);
            if (rw && cl) puts("YES");
            else puts("NO");
        } else {
            puts("NO");
        }
    }
    return 0;
}
