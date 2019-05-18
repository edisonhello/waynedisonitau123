#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
char s[maxn];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    scanf("%s", s);
    int c = 0;
    for (int i = 0; i < n; ) {
        int j = i, k = 0;
        while (j < n) {
            k = (k * 10 + (s[j] - '0')) % m;
            ++j;
            if (k == 0) break;
        }
        if (k != 0) {
            puts("0");
            return 0;
        }
        i = j;
        ++c;
    }
    int ans = 1;
    for (int i = 0; i < c - 1; ++i) ans = ans * 2 % mod;
    printf("%d\n", ans);
    return 0;
}
