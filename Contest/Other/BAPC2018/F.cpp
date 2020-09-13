#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> p(N), c(N);
    for (int i = 0; i < N; ++i) {
        cin >> p[i] >> c[i];
    }

    int ans = INT_MAX;

    auto Check = [&](int D) {
        int64_t X = 0;
        for (int i = 0; X < M && i < N; ++i) {
            int64_t W = 1LL * p[i] * D;
            if (W > c[i]) X += W - c[i];
        }
        return X >= M;
    };

    for (int bit = 30; bit >= 0; --bit) {
        if (ans - (1 << bit) <= 0) continue;
        if (Check(ans - (1 << bit))) ans -= (1 << bit);
    }
    cout << ans << "\n";
}

