vector<int> omega;
void Init() {
    omega.resize(kN + 1);
    long long x = fpow(kRoot, (Mod - 1) / kN);
    omega[0] = 1;
    for (int i = 1; i <= kN; ++i) {
        omega[i] = 1LL * omega[i - 1] * x % kMod;
    }
}
void Transform(vector<int> &v, int n) {
    BitReverse(v, n);
    for (int s = 2; s <= n; s <<= 1) {
        int z = s >> 1;
        for (int i = 0; i < n; i += s) {
            for (int k = 0; k < z; ++k) {
                int x = 1LL * v[i + k + z] * omega[kN / s * k] % kMod;
                v[i + k + z] = (v[i + k] + kMod - x) % kMod;
                (v[i + k] += x) %= kMod;
            }
        }
    }
}
void InverseTransform(vector<int> &v, int n) {
    Transform(v, n);
    for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]);
    const int kInv = fpow(n, kMod - 2);
    for (int i = 0; i < n; ++i) v[i] = 1LL * v[i] * inv % kMod;
}
