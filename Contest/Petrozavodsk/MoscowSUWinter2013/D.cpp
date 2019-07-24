#include <bits/stdc++.h>
using namespace std;
 
double pw(double b, long long n, double a = 1) {
    while (n) {
        if (n & 1) a *= b;
        b *= b; n >>= 1;
    } return a;
}
 
int main() {
    long long n, k; cin >> n >> k;
    if (k == 1) {
        cout << n * (n + 1) / 2 << endl;
        exit(0);
    }
    double ans = 0;
    double p = 1;
    int nowpw = 0;
    for (int len = 1; len <= 100000; ++len) {
        if (len > n) break;
        long long cnt = n + 1 - len;
        if (len / 2 > nowpw) ++nowpw, p /= k;
        ans += p * cnt;
    }
    cout << fixed << setprecision(10) << ans << endl;
}
