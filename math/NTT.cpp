const long long p = 2013265921, root = 31;
long long omega[maxn + 1];

long long fpow(long long a, long long n) {
    long long ret = 1ll;
    for (; n; n >>= 1) {
        if (n & 1) ret = ret * a % p;
        a = a * a % p;
    }
    return ret;
}

void prentt() {
    omega[0] = 1;
    long long r = fpow(root, (p - 1) / maxn);
    for (int i = 1; i <= maxn; ++i) omega[i] = omega[i - 1] * r % p;
}

void ntt(vector<long long>& a, int n, bool inv = false) {
    int basic = maxn / n;
    int theta = basic;
    for (int m = n; m >= 2; m >>= 1) {
        int mh = m >> 1;
        for (int i = 0; i < mh; ++i) {
            long long w = omega[i * theta % maxn];
            for (int j = i; j < n; j += m) {
                int k = j + mh;
                long long x = a[j] - a[k];
                if (x < 0) x += p;
                a[j] += a[k];
                if (a[j] > p) a[j] -= p;
                a[k] = w * x % p;
            }
        }
        theta = theta * 2 % maxn;
    }
    int i = 0;
    for (int j = 1; j < n - 1; ++j) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(a[i], a[j]);
    }
    if (!inv) return;
    long long ni = fpow(n, p - 2);
    reverse(a.begin() + 1, a.end());
    for (int i = 0; i < n; ++i) a[i] = a[i] * ni % p;
}
