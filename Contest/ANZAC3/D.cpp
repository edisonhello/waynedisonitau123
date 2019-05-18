#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int n, c[maxn];

bool check(int h) {
    int res = 0;
    for (int i = 0; i < n; ++i)
        res += c[i] >= h;
    return res >= h;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &c[i]);

    int ans = 0;
    for (int d = 30; d >= 0; --d) {
        if (ans + (1 << d) <= 1000000000) {
            if (check(ans + (1 << d)))
                ans += (1 << d);
        }
    }
    printf("%d\n", ans);
    return 0;
}
