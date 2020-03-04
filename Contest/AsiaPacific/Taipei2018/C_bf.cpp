#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const int inf = 1e9;
int s[maxn], x[maxn], n;

bool check(int a, int b) {
    for (int i = 0; i < n; ++i) x[i] = s[i];
    x[0] += a, x[n - 1] += b;
    for (int i = 0; i < n; ++i) {
        int w = 0, l = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (x[i] > x[j]) ++w;
            if (x[i] < x[j]) ++l;
        }
        x[i] += w - l;
    }
    for (int i = 1; i < n - 1; ++i) if (x[0] <= x[i]) return false;
    for (int i = 1; i < n - 1; ++i) if (x[n - 1] <= x[i]) return false;
    return true;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int ans = inf;
        for (int i = 0; i < n; ++i) scanf("%d", &s[i]);
        for (int a = 0; a <= 100; ++a) {
            for (int b = 0; b <= 100; ++b) {
                if (check(a, b)) ans = min(ans, a);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
