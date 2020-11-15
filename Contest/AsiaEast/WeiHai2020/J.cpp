#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int64_t> A(N);
    int64_t Xor = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        Xor ^= A[i]; 
    }
    sort(A.begin(), A.end(), greater<int64_t>());

    constexpr int kP = 1'000'000'000 + 7;
    int res = 0;

    vector<int> pw(N + 1, 1);
    for (int i = 1; i <= N; ++i) pw[i] = (pw[i - 1] + pw[i - 1]) % kP;

    int Vec = 0;
    vector<int64_t> Basis;
    int64_t LXor = Xor;

    auto Span = [&](int64_t V) {
        for (int64_t u : Basis) V = min(V, u ^ V);
        return V == 0;
    };

    for (int i = 0, j = 0; i < N; i = j) {
        while (j < N && A[i] == A[j]) LXor ^= A[j++];
        int X = j - i;
        int64_t Cur = X % 2 == 1 ? A[i] : 0;
        if (((A[i] - 1) ^ Xor) == 0 && X > 1) (res += (pw[X - 1] + kP - 1) % kP) %= kP;
        if (Xor == 0) (res += pw[X - 1]) %= kP;

        if (Span(A[i] ^ LXor ^ Cur) && X > 1) {
            (res += 1ll * (pw[X - 1] + kP - 1) * pw[Vec - Basis.size()] % kP) %= kP;
            if (((Xor ^ LXor ^ Cur) ^ Cur ^ LXor ^ A[i]) == 0) (res += kP - (pw[X - 1] + kP - 1) % kP) %= kP;
        }
        if (Span((A[i] - 1) ^ LXor ^ Cur ^ A[i])) {
            (res += 1ll * pw[X - 1] * pw[Vec - Basis.size()] % kP) %= kP;
            if (((Xor ^ LXor ^ Cur) ^ Cur ^ A[i] ^ LXor ^ (A[i] - 1)) == 0) (res += kP - pw[X - 1]) %= kP;
        }

        int64_t V = A[i];
        for (int64_t u : Basis) V = min(V, u ^ V);
        if (V > 0) Basis.push_back(V);
        Vec += X;
    }
    if (Xor == 0) (res += 1) %= kP;
    cout << res << "\n";
}

