#include <bits/stdc++.h>
using namespace std;

namespace fft {

constexpr int kN = 131072;
constexpr int64_t kP = 2885681153;
constexpr int64_t kR = 3;
array<int64_t, kN + 1> Omega;

int64_t fpow(int64_t a, int64_t n) {
    int64_t res = 1;
    while (n > 0) {
        if (n & 1) res = __int128(res) * a % kP;
        a = __int128(a) * a % kP;
        n >>= 1;
    }
    return res;
}

void Init() {
    assert((kP - 1) % kN == 0);
    const int64_t x = fpow(kR, (kP - 1) / kN);
    Omega[0] = 1;
    for (int i = 1; i <= kN; ++i) {
        Omega[i] = __int128(Omega[i - 1]) * x % kP;
    }
}

void BitReverse(vector<int64_t> &v, int N) {
    int z = __builtin_ctz(N) - 1;
    for (int i = 0; i < N; ++i) {
        int x = 0;
        for (int j = 0; (1 << j) < N; ++j) x ^= (i >> j & 1) << (z - j);
        if (x > i) swap(v[x], v[i]);
    }
}

void Transform(vector<int64_t> &v, int N) {
    BitReverse(v, N);
    for (int s = 2; s <= N; s <<= 1) {
        int z = s >> 1;
        for (int i = 0; i < N; i += s) {
            for (int k = 0; k < z; ++k) {
                int64_t x = __int128(v[i + k + z]) * Omega[kN / s * k] % kP;
                v[i + k + z] = (v[i + k] + kP - x) % kP;
                (v[i + k] += x) %= kP;
            }
        }
    }
}

void InvTransform(vector<int64_t> &v, int N) {
    Transform(v, N);
    for (int i = 1; i < N / 2; ++i) swap(v[i], v[N - i]);
    const int64_t kInv = fpow(N, kP - 2);
    for (int i = 0; i < N; ++i) v[i] = __int128(v[i]) * kInv % kP;
}

}

int main() {
    vector<vector<int>> A(3);
    for (int i = 0; i < 3; ++i) {
        int N;
        cin >> N;
        A[i].resize(N);
        for (int j = 0; j < N; ++j) cin >> A[i][j];
    }
    fft::Init();
    vector<int64_t> B(131072), C(131072);
    for (int u : A[0]) B[u + 30000]++;
    for (int u : A[2]) C[u + 30000]++;
    fft::Transform(B, 131072);
    fft::Transform(C, 131072);
    for (int64_t i = 0; i < 131072; ++i) B[i] = __int128(B[i]) * C[i] % fft::kP;
    fft::InvTransform(B, 131072);
    int64_t res = 0;
    for (int u : A[1]) res += B[2 * u + 60000];
    cout << res << "\n";
}

