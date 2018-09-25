#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int x[maxn], y[maxn];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    x[n] = x[0], y[n] = y[0];
    long long a = 0, b = 0;
    for (int i = 0; i < n; ++i) {
        int x1 = x[i] - x[0], y1 = y[i] - y[0];
        int x2 = x[i + 1] - x[0], y2 = y[i + 1] - y[0];
        a += x1 * 1ll * y2 - y1 * 1ll * x2;
        b += __gcd(abs(x[i + 1] - x[i]), abs(y[i + 1] - y[i]));
    }
    a = abs(a);
    // printf("a = %lld\n", a);
    // printf("b = %lld\n", b);
    long long i = a - b + 2;
    assert(i % 2 == 0);
    printf("%lld\n", i / 2);
}
