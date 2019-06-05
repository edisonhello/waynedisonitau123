#include <bits/stdc++.h>
using namespace std;

namespace fft {
    struct cplx {
        double re, im;
        cplx(): re(0), im(0) {}
        cplx(double r, double i): re(r), im(i) {}
        cplx operator+(const cplx &rhs) const {
            return cplx(re + rhs.re, im + rhs.im);
        }
        cplx operator-(const cplx &rhs) const {
            return cplx(re - rhs.re, im - rhs.im);
        }
        cplx operator*(const cplx &rhs) const {
            return cplx(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re);
        }
        cplx conj() const {
            return cplx(re, -im);
        }
    };

    const int maxn = 131072;
    const double pi = acos(-1);
    cplx omega[maxn + 1];

    void prefft() {
        for (int i = 0; i <= maxn; ++i)
            omega[i] = cplx(cos(2 * pi * i / maxn), sin(2 * pi * i / maxn));
    }

    void bitrev(vector<cplx> &v, int n) {
        int z = __builtin_ctz(n) - 1;
        for (int i = 0; i < n; ++i) {
            int x = 0;
            for (int j = 0; (1 << j) < n; ++j)
                x ^= (i >> j & 1) << (z - j);
            if (x > i) swap(v[x], v[i]);
        }
    }

    void fft(vector<cplx> &v, int n) {
        bitrev(v, n);
        for (int s = 2; s <= n; s <<= 1) {
            int z = s >> 1;
            for (int i = 0; i < n; i += s) {
                for (int k = 0; k < z; ++k) {
                    cplx x = v[i + z + k] * omega[maxn / s * k];
                    v[i + z + k] = v[i + k] - x;
                    v[i + k] = v[i + k] + x;
                }
            }
        }
    }

    void ifft(vector<cplx> &v, int n) {
        fft(v, n);
        reverse(v.begin() + 1, v.end());
        for (int i = 0; i < n; ++i) 
            v[i] = v[i] * cplx(1. / n, 0);
    }

    vector<int> conv(const vector<int> &a, const vector<int> &b, int p) {
        int sz = 1;
        while (sz < (int)a.size() + (int)b.size() - 1) sz <<= 1;
        vector<cplx> fa(sz), fb(sz);
        for (int i = 0; i < (int)a.size(); ++i) {
            int x = (a[i] % p + p) % p;
            fa[i] = cplx(x & ((1 << 15) - 1), x >> 15);
        }
        for (int i = 0; i < (int)b.size(); ++i) {
            int x = (b[i] % p + p) % p;
            fb[i] = cplx(x & ((1 << 15) - 1), x >> 15);
        }

        fft(fa, sz);
        fft(fb, sz);
        double r = 0.25 / sz;
        cplx r2(0, -1), r3(r, 0), r4(0, -r), r5(0, 1);
        for (int i = 0; i <= (sz >> 1); ++i) {
            int j = (sz - i) & (sz - 1);
            cplx a1 = fa[i] + fa[j].conj();
            cplx a2 = (fa[i] - fa[j].conj()) * r2;
            cplx b1 = (fb[i] + fb[j].conj()) * r3;
            cplx b2 = (fb[i] - fb[j].conj()) * r4;
            if (i != j) {
                cplx c1 = fa[j] + fa[i].conj();
                cplx c2 = (fa[j] - fa[i].conj()) * r2;
                cplx d1 = (fb[j] + fb[i].conj()) * r3;
                cplx d2 = (fb[j] - fb[i].conj()) * r4;
                fa[i] = c1 * d1 + c2 * d2 * r5;
                fb[i] = c1 * d2 + c2 * d1;
            }
            fa[j] = a1 * b1 + a2 * b2 * r5;
            fb[j] = a1 * b2 + a2 * b1;
        }
        fft(fa, sz);
        fft(fb, sz);

        vector<int> res(sz);
        for (int i = 0; i < sz; ++i) {
            long long a = round(fa[i].re);
            long long b = round(fb[i].re);
            long long c = round(fa[i].im);
            res[i] = (a + ((b % p) << 15) + ((c % p) << 30)) % p;
        }
        return res;
    }
}

const int maxn = 131072;
int pw[maxn], fc[maxn], iv[maxn];

int fpow(int a, int n, int p) {
    int res = 1;
    while (n > 0) {
        if (n & 1)
            res = res * 1ll * a % p;
        a = a * 1ll * a % p;
        n >>= 1;
    }
    return res;
}

int main() {
    fft::prefft();
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n, m, p; scanf("%d%d%d", &n, &m, &p);
        for (int i = 1; i <= n; ++i) pw[i] = fpow(i + 1, m, p);
        fc[0] = iv[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fc[i] = fc[i - 1] * 1ll * i % p;
            iv[i] = fpow(fc[i], p - 2, p);
        }
        vector<int> a(n + 1), b(n + 1);
        for (int i = 0, c = 1; i <= n; ++i, c = p - c) {
            a[i] = c * 1ll * iv[i] % p;
            b[i] = iv[i] * 1ll * fpow(i, n, p) % p;
        }

        vector<int> d = fft::conv(a, b, p);
        int ans = 0;
        for (int i = n, c = 1; i >= 1; --i, c = p - c) {
            int add = c * 1ll * pw[i] % p * d[i] % p * fc[i] % p;
            (ans += add) %= p;
        }
        printf("Case #%d: %d\n", tc, ans);
    }
}
