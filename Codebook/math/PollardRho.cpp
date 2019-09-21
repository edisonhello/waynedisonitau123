map<long long, int> cnt;

long long f(long long x, long long n, int p) { return (fmul(x, x, n) + p) % n; }
void pollard_rho(long long n) {
    if (n == 1) return;
    if (prime(n)) return ++cnt[n], void();        
    if (n % 2 == 0) return pollard_rho(n / 2), ++cnt[2], void();
    long long x = 2, y = 2, d = 1, p = 1;
    while (true) {
        if (d != n && d != 1) {
            pollard_rho(n / d);
            pollard_rho(d);
            return;
        }
        if (d == n) ++p;
        x = f(x, n, p); y = f(f(y, n, p), n, p);
        d = __gcd(abs(x - y), n);
    }
}
