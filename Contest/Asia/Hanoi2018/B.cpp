#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % mod;
        a = 1LL * a * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int n; scanf("%d", &n);
    long long sum = 0;
    int pw = mod - 2;
    while (n--) {
        int a, b; scanf("%d%d", &a, &b);
        sum += a + b;
        pw += 1LL * a * b % (mod - 1);
        pw %= (mod - 1);
    }
    if (sum % 2 == 1) {
        puts("0");
        return 0;
    }
    printf("%d\n", fpow(2, pw));
}
