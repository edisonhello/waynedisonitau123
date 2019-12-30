#include <bits/stdc++.h>
using namespace std;

const int kN = 1 << 24;
const long long kMask = (1LL << 30) - 1;
const int kM = 531441;
int a[kN];
long long c[kN], d[kM];

void Trans(int *a, int n, int m, int k) {
    for (int i = 0; i < n; ++i) c[i] &= ~kMask;
    for (int i = 0; i < m; ++i) {
        int g = 0, v = i;
        for (int j = 0; j < k; ++j) {
            int b = v % 3;
            b = (b == 0 ? 1 : b == 1 ? 2 : 0);
            g |= b << (j + j);
            v /= 3;
        }
        c[g] += a[i];
    }
    for (int i = 0; i < n; ++i) a[i] = c[i] & kMask;
}

void InvTrans(long long *a, int n, int m, int k) {
    for (int i = 0; i < n; ++i) {
        int g = 0, v = i;
        for (int j = 0, r = 1; j < k; ++j, r *= 3) {
            int b = v % 4;
            if (b == 0 || b == 2) b = 0;
            else if (b == 3) b = 2;
            else b = 1;
            v /= 4;
            g += r * b;
        }
        d[g] += a[i];
    }
    for (int i = 0; i < m; ++i) c[i] = d[i];
}

void FWT(int *a, int n) {
    if (n == 1) return;
    int m = n >> 1;
    FWT(a, m), FWT(a + m, m);
    for (int i = m; i < n; ++i) a[i] += a[i - m];
}

void IFWT(long long *a, int n) {
    if (n == 1) return;
    int m = n >> 1;
    IFWT(a, m), IFWT(a + m, m);
    for (int i = m; i < n; ++i) a[i] -= a[i - m];
}

int main() {
    int k; scanf("%d", &k);
    // k = 12;
    int m = 1, n = 1;
    for (int i = 0; i < k; ++i) m *= 3, n *= 4;
    for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
    Trans(a, n, m, k);
    // for (int i = 0; i < n; ++i) printf("%d ", a[i]); puts("");
    FWT(a, n);
    for (int i = 0; i < n; ++i) c[i] = (1LL * a[i]) << 30;
    for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
    Trans(a, n, m, k);
    // for (int i = 0; i < n; ++i) printf("%d ", a[i]); puts("");
    FWT(a, n);
    // for (int i = 0; i < m; ++i) a[i] = rand() % 1000;
    // for (int i = 0; i < m; ++i) b[i] = rand() % 1000;
    // Trans(a, n, m, k);
    // Trans(b, n, m, k);
    // printf("n = %d\n", n);
    // FWT(a, n); FWT(b, n);
    for (int i = 0; i < n; ++i) c[i] = c[i] >> 30;
    // for (int i = 0; i < n; ++i) printf("%lld ", c[i]); puts("");
    for (int i = 0; i < n; ++i) c[i] = c[i] * a[i];
    // for (int i = 0; i < n; ++i) printf("%lld ", c[i]); puts("");
    IFWT(c, n);
    // for (int i = 0; i < n; ++i) c[i] = 0;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) c[i | j] += a[i] * b[j];
    // }
    InvTrans(c, n, m, k);
    for (int i = 0; i < m; ++i) printf("%lld ", c[i]);
    puts("");
}
