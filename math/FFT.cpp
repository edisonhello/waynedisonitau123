const int maxn = 131072;
using cplx = complex<double>;
const cplx I = cplx(0, 1);
const double pi = acos(-1);
cplx omega[maxn + 1];

void prefft() {
    for (int i = 0; i <= maxn; ++i) omega[i] = exp(i * 2 * pi / maxn * I);
}

void bin(vector<cplx> &a, int n) {
    int lg;
    for (lg = 0; (1 << lg) < n; ++lg); --lg;
    vector<cplx> tmp(n);
    for (int i = 0; i < n; ++i) {
        int to = 0;
        for (int j = 0; (1 << j) < n; ++j) to |= (((i >> j) & 1) << (lg - j));
        tmp[to] = a[i];
    }
    for (int i = 0; i < n; ++i) a[i] = tmp[i];
}

void fft(vector<cplx> &a, int n) {
    bin(a, n);
    for (int step = 2; step <= n; step <<= 1) {
        int to = step >> 1;
        for (int i = 0; i < n; i += step) {
            for (int k = 0; k < to; ++k) {
                cplx x = a[i + to + k] * omega[maxn / step * k];
                a[i + to + k] = a[i + k] - x;
                a[i + k] += x;
            }
        }
    }
}

void ifft(vector<cplx> &a, int n) {
    fft(a, n);
    reverse(a.begin() + 1, a.end());
    for (int i = 0; i < n; ++i) a[i] /= n;
}

vector<int> multiply(vector<int> &a, vector<int> &b, int n) {
    vector<cplx> ca(n << 1), cb(n << 1);
    for (int i = 0; i < n; ++i) ca[i] = cplx(a[i], 0);
    for (int i = 0; i < n; ++i) cb[i] = cplx(b[i], 0);
    fft(ca, n << 1); fft(cb, n << 1);
    vector<cplx> cc(n << 1);
    for (int i = 0; i < n << 1; ++i) cc[i] = ca[i] * cb[i];
    ifft(cc, n << 1);
    vector<int> c(n << 1);
    for (int i = 0; i < n << 1; ++i) c[i] = (int)(cc[i].real() + 0.5);
    return c;
}
