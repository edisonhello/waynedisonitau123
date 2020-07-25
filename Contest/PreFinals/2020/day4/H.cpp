#include <bits/stdc++.h>
using namespace std;

namespace fft {

struct Complex {
    double re, im;
    Complex() : re(0), im(0) {}
    Complex(double r, double i) : re(r), im(i) {}

    Complex operator+(const Complex &rhs) const {
        return Complex(re + rhs.re, im + rhs.im);
    }
    Complex operator-(const Complex &rhs) const {
        return Complex(re - rhs.re, im - rhs.im);
    }
    Complex operator*(const Complex &rhs) const {
        return Complex(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re);
    }
    Complex Conj() const { return Complex(re, -im); }
};

constexpr double kPi = acos(-1);
constexpr int kN = 131072;
Complex omega[kN + 1];

void PreFFT() {
    for (int i = 0; i <= kN; ++i) {
        omega[i] = Complex(cos(2 * kPi * i / kN), sin(2 * kPi * i / kN));
    }
}

void BitRev(vector<Complex> &v, int n) {
    int z = __builtin_ctz(n) - 1;
    for (int i = 0; i < n; ++i) {
        int x = 0;
        for (int j = 0; j <= z; ++j) {
            x ^= (i >> j & 1) << (z - j);
        }
        if (x > i) swap(v[x], v[i]);
    }
}

void Trans(vector<Complex> &v, int n) {
    BitRev(v, n);
    for (int s = 2; s <= n; s <<= 1) {
        int z = s >> 1;
        for (int i = 0; i < n; i += s) {
            for (int k = 0; k < z; ++k) {
                Complex x = v[i + z + k] * omega[kN / s * k];
                v[i + z + k] = v[i + k] - x;
                v[i + k] = v[i + k] + x;
            }
        }
    }
}

void InvTrans(vector<Complex> &v, int n) {
    Trans(v, n);
    reverse(v.begin() + 1, v.end());
    for (int i = 0; i < n; ++i) v[i] = v[i] * Complex(1.0 / n, 0);
}

vector<double> Multiply(vector<double> a, vector<double> b) {
    int sz = 1, n = a.size(), m = b.size();
    while (sz < n + m - 1) sz <<= 1;
    vector<Complex> v(sz);
    for (int i = 0; i < n; ++i) {
        double re = i < a.size() ? a[i] : 0;
        double im = i < b.size() ? b[i] : 0;
        v[i] = Complex(re, im);
    }
    Trans(v, sz);
    const Complex kR(0, -0.25);
    for (int i = 0; i <= sz / 2; ++i) {
        int j = (sz - i) & (sz - 1);
        Complex x = (v[i] + v[j].Conj()) * (v[i] - v[j].Conj()) * kR;
        if (j != i) {
            v[j] = (v[j] + v[i].Conj()) * (v[j] - v[i].Conj()) * kR;
        }
        v[i] = x;
    }
    InvTrans(v, sz);
    vector<double> res(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) res[i] = v[i].re;
    return res;
}

}  // namespace fft

int main() {
    fft::PreFFT();
    int n;
    cin >> n;
    vector<double> dp(n + 1);
    dp[0] = dp[1] = 1.0;
    constexpr int kIter = 200;
    cout << fixed << setprecision(20);
    if (n == 1) {
        cout << 1.0 << "\n";
        return 0;
    }
    double last = 0.0;
    cout << 0.0 << "\n";
    for (int it = 0; it < min(n - 1, kIter); ++it) {
        vector<double> ndp = fft::Multiply(dp, dp); 
        vector<double> inter(ndp.size() + 1, 1.0);
        for (int i = 0; i < ndp.size(); ++i) {
            inter[i + 1] = ndp[i] / (i + 1);
        }
        inter.resize(n + 1);
        dp = inter;
        cout << max((double)0, dp[n] - last) << "\n";
        last = dp[n];
    }
    for (int i = min(n - 1, kIter); i < n - 1; ++i) {
        cout << 0.0 << "\n";
    }
}

