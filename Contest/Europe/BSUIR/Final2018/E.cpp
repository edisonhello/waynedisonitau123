#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 512;
const int kM = 100'000 + 5;
const int kMod = 998244353;
const int kRoot = 3;
int A[kN][kN], B[kN][kN], C[kN], cb[kN][kN], fc[kN], iv[kN];
int a[kM], b[kM];

int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % kMod;
        a = 1LL * a * a % kMod;
        n >>= 1;
    }
    return res;
}

namespace fft {

const int kN = ::kN * 2;
int omega[kN + 1];
using Poly = array<int, kN>;

void Init() {
    int x = fpow(kRoot, (kMod - 1) / kN);
    omega[0] = 1;
    for (int i = 1; i <= kN; ++i) omega[i] = 1LL * omega[i - 1] * x % kMod;
}

void Bitrev(Poly &v) {
    int z = __builtin_ctz(kN) - 1;
    for (int i = 0; i < kN; ++i) {
        int x = 0;
        for (int j = 0; j <= z; ++j) x ^= (i >> j & 1) << (z - j);
        if (x > i) swap(v[x], v[i]);
    }
}

void NTT(Poly &v) {
    Bitrev(v);
    for (int s = 2; s <= kN; s <<= 1) {
        int z = s >> 1;
        for (int i = 0; i < kN; i += s) {
            for (int k = 0; k < z; ++k) {
                int x = 1LL * v[i + k + z] * omega[kN / s * k] % kMod;
                v[i + k + z] = (v[i + k] + kMod - x) % kMod;
                (v[i + k] += x) >= kMod ? v[i + k] -= kMod : 0;
            }
        }
    }
}

void InvNTT(Poly &v) {
    NTT(v);
    for (int i = 1; i < kN / 2; ++i) swap(v[i], v[kN - i]);
    int iv = fpow(kN, kMod - 2);
    for (int i = 0; i < kN; ++i) v[i] = 1LL * v[i] * iv % kMod;
}

}

fft::Poly Ai[kN], Bi[kN];
int pw[kN][kN];

int Getchar() {
    const int kBuf = 4096;
    static char buf[kBuf];
    static char *p = buf, *end = buf;
    if (p == end) {
        if ((end = buf + fread(buf, 1, kBuf, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}

void Read(int &v) {
    static char c;
    while ((c = Getchar()) && !isdigit(c));
    v = c & 15;
    while ((c = Getchar()) && isdigit(c)) v = v * 10 + (c & 15);
}

int main() {
    int n; Read(n);
    fft::Init();
    cb[0][0] = 1;
    for (int i = 1; i < kN; ++i) {
        cb[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            cb[i][j] = (cb[i - 1][j] + cb[i - 1][j - 1]) % kMod;
    }
    for (int i = 0; i < n; ++i) Read(a[i]);
    for (int i = 0; i < n; ++i) Read(b[i]);
    for (int i = 1; i < kN; ++i) {
        pw[i][0] = 1;
        for (int j = 1; j < kN; ++j)
            pw[i][j] = 1LL * pw[i][j - 1] * i % kMod;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < kN; ++j) {
            (A[b[i]][j] += pw[a[i]][j]) >= kMod ? A[b[i]][j] -= kMod : 0;
        }
    }
    fc[0] = iv[0] = 1;
    for (int i = 1; i < kN; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % kMod;
        iv[i] = fpow(fc[i], kMod - 2);
    }
    for (int i = 0; i < kN; ++i) {
        Ai[i] = fft::Poly{};
        for (int j = 0; j < kN; ++j)
            Ai[i][j] = 1LL * A[i][j] * iv[j] % kMod;
        fft::NTT(Ai[i]);
        Bi[i] = fft::Poly{};
    }
    for (int i = 0; i < kN; ++i) {
        for (int j = 0; j < kN; ++j) {
            for (int k = 0; k < kN + kN; ++k) {
                Bi[i ^ j][k] += 1LL * Ai[i][k] * Ai[j][k] % kMod;
                (Bi[i ^ j][k] >= kMod) ? Bi[i ^ j][k] -= kMod : 0;
            }
        }
    }
    for (int i = 0; i < kN; ++i) {
        fft::InvNTT(Bi[i]);
        for (int j = 0; j < kN; ++j) 
            B[i][j] = 1LL * Bi[i][j] * fc[j] % kMod;
    }
    // for (int i = 0; i < kN; ++i) {
    //     for (int j = 0; j < kN; ++j)
    //         printf("%d ", B[i][j]);
    //     puts("");
    // }
    // for (int i = 0; i < kN; ++i) {
    //     for (int j = 0; j < kN; ++j) {
    //         for (int k = 0; k < kN; ++k) {
    //             Ai[k] = 1LL * A[i][k] * iv[k] % kMod;
    //             Aj[k] = 1LL * A[j][k] * iv[k] % kMod;
    //         }
    //         for (int k = kN; k < kN + kN; ++k) Ai[k] = Aj[k] = 0;
    //         Ak = fft::Multiply(Ai, Aj);
    //         for (int k = 0; k < kN; ++k) {
    //             B[i ^ j][k] += 1LL * Ak[k] * fc[k] % kMod;
    //             B[i ^ j][k] %= kMod;
    //         }
    //         /* for (int t = 0; t < kN; ++t) {
    //             for (int v = 0; v <= t; ++v) {
    //                 B[i ^ j][t] += 1LL * A[i][v] * A[j][t - v] % kMod * cb[t][v] % kMod;
    //                 B[i ^ j][t] %= kMod;
    //             }
    //         } */
    //     }
    // }
    // for (int i = 0; i < kN; ++i) {
    //     Ai[i] = fft::Poly{};
    //     for (int j = 0; j < kN; ++j)
    //         Ai[i][j] = 1LL * B[i][j] * iv[j] % kMod;
    //     fft::NTT(Ai[i]);
    //     Bi[i] = fft::Poly{};
    // }
    // for (int i = 0; i < kN; ++i) {
    //     for (int j = 0; j < kN; ++j) {
    //         for (int k = 0; k < kN + kN; ++k) {
    //             Bi[i ^ j][k] += 1LL * Ai[i][k] * Ai[j][k] % kMod;
    //             Bi[i ^ j][k] %= kMod;
    //         }
    //     }
    // }
    // for (int i = 0; i < kN; ++i) {
    //     fft::InvNTT(Bi[i]);
    //     for (int j = 0; j < kN; ++j) 
    //         C[i][j] = 1LL * Bi[i][j] * fc[j] % kMod;
    // }
    for (int i = 0; i < kN; ++i) {
        for (int j = 0; j < kN; ++j) {
            // for (int k = 0; k < kN; ++k) {
            //     Ai[k] = 1LL * B[i][k] * iv[k] % kMod;
            //     Aj[k] = 1LL * B[j][k] * iv[k] % kMod;
            // }
            // for (int k = kN; k < kN + kN; ++k) Ai[k] = Aj[k] = 0;
            // Ak = fft::Multiply(Ai, Aj);
            // for (int k = 0; k < kN; ++k) {
            //     C[i ^ j][k] += 1LL * Ak[k] * fc[k] % kMod;
            //     C[i ^ j][k] %= kMod;
            // }
            int t = i ^ j;
            for (int v = 0; v <= t; ++v) {
                C[t] += 1LL * B[i][v] * B[j][t - v] % kMod * cb[t][v] % kMod;
                (C[t] >= kMod) ? C[t] -= kMod : 0;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < kN; ++i) (ans += C[i]) %= kMod;
    printf("%d\n", ans);
    return 0;
}
