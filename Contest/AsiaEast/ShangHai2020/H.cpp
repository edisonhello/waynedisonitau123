#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<int> A(K), B(K);
        for (int i = 0; i < K; ++i) cin >> A[i];
        for (int i = 0; i < K; ++i) cin >> B[i];

        vector<int> C(K), D(K);
        auto Solve = [&](int p) {
            for (int i = 0; i < K; ++i) C[i] = (A[i] - p + N) % N;
            for (int i = 0; i < K; ++i) D[i] = (B[i] - p + N) % N;
            sort(C.begin(), C.end());
            sort(D.begin(), D.end());
            int X = 0, Y = 0;
            for (int i = 0; i < K; ++i) {
                if (C[i] <= D[i]) X = max(X, D[i] - C[i]);
                else Y = max(Y, C[i] - D[i]);
            }
            return X + Y + min(X, Y);
        };

        int ans = 2'000'000'000;
        for (int u : A) ans = min(ans, Solve(u));
        for (int u : B) ans = min(ans, Solve(u));
        cout << ans << "\n";
    }
}

