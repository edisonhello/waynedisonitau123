#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define double float
#define int int_fast32_t

const int maxn = 524288;

struct cplx {
    double re, im;
    cplx(): re(0), im(0) {}
    cplx(double r, double i): re(r), im(i) {}
    cplx operator+(const cplx &rhs) const { return cplx(re + rhs.re, im + rhs.im); }
    cplx operator-(const cplx &rhs) const { return cplx(re - rhs.re, im - rhs.im); }
    cplx operator*(const cplx &rhs) const { return cplx(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re); }
    cplx conj() const { return cplx(re, -im); }
};

const double pi = acos(-1);
cplx omega[maxn + 1];

void bitrev(vector<cplx> &v, int n) {
    register int z = __builtin_ctz(n) - 1, x = 0;
    for (register int i = 0; i < n; ++i) {
        x = 0;
        for (register int j = 0; j <= z; ++j) x ^= (i >> j & 1) << (z - j);
        if (x > i) swap(v[x], v[i]);
    }
}

void fft(vector<cplx> &v, int n) {
    bitrev(v, n);
    for (register int s = 2; s <= n; s <<= 1) {
        register int z = s >> 1;
        for (register int i = 0; i < n; i += s) {
            for (register int k = 0; k < z; ++k) {
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
    cplx inv = cplx(1. / n, 0);
    for (register int i = 0; i < n; ++i) v[i] = v[i] * inv;
}

void prefft() {
    double z = 2 * pi / maxn;
    for (register int i = 0; i <= maxn; ++i) {
        omega[i] = cplx(cos(z * i), sin(z * i));
    }
}

int sz = 1;
vector<cplx> v;
vector<int> c, a, b;

void conv() {
    // for (int i = 0; i < (int)a.size(); ++i) cout << a[i] << ' '; cout << endl;
    // for (int i = 0; i < (int)b.size(); ++i) cout << b[i] << ' '; cout << endl;
    double re, im;
    for (register int i = 0; i < sz; ++i) {
        re = i < (int)a.size() ? a[i] : 0;
        im = i < (int)b.size() ? b[i] : 0;
        v[i] = cplx(re, im);
    }
    fft(v, sz);
    cplx r = cplx(0, -0.25);
    for (register int i = 0, j; i <= sz / 2; ++i) {
        j = (sz - i) & (sz - 1);
        cplx x = (v[i] + v[j].conj()) * (v[i] - v[j].conj()) * r;
        if (j != i) v[j] = (v[j] + v[i].conj()) * (v[j] - v[i].conj()) * r;
        v[i] = x;
    }
    ifft(v, sz);
    for (register int i = 0; i < sz; ++i) c[i] = round(v[i].re);
}

int cnt[maxn];

inline bool equal(char a, char b) {
    return abs(a - b) <= 1;
}

char buf[524288];
char s[262144], t[262144];
int ans[maxn];

int32_t main() {
    char *p = buf;
    char *e = p + fread_unlocked(buf, 1, 524288, stdin);
    int n = 0, m = 0;
    while (*p != '\n') s[n++] = *p++; ++p;
    while (p != e) t[m++] = *p++; 
    prefft();
    a.resize(n + 1), b.resize(m);
    while (sz < n + m - 1) sz <<= 1;
    v.resize(sz);
    c.resize(sz);
    for (register int j = 0; j < 26; ++j) {
        for (register int i = 0; i < n; ++i) {
            if (s[i] - 'a' == j) a[n - i] = 1;
            else a[n - i] = 0;
        }
        for (register int i = 0; i < m; ++i) {
            if (equal(t[i], j + 'a')) b[i] = 1;
            else b[i] = 0;
        }
        conv();
        for (register int i = 0; i < sz; ++i) cnt[i] += c[i];
        // for (int i = 0; i < (int)c.size(); ++i) cout << c[i] << ' '; cout << endl;
    }
    // for (int i = 0; i < 20; ++i) cout << cnt[i] << ' '; cout << endl;
    int z = 0;
    for (register int i = n; i < maxn; ++i) {
        if (cnt[i] == n) ans[z++] = i;
    }
    cout << z << "\n";
    if (z == 0) return 0;
    for (register int i = 0; i < z; ++i) {
        cout << ans[i] - n + 1 << " \n"[i + 1 == z];
    }
}
