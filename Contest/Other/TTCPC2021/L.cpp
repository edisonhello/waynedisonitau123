#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;

    constexpr int kP = 998244353;

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kP;
            a = 1LL * a * a % kP;
            n >>= 1;
        }
        return res;
    };

    vector<int> fc(N + 1, 1);
    for (int i = 1; i <= N; ++i) fc[i] = 1LL * fc[i - 1] * i % kP;

    int ans = 0;
    for (int m = 3; m <= N; ++m) {
        int t = 1LL * fc[N] * fpow(fc[N - m], kP - 2) % kP;
        ans += 1LL * t * fpow(2 * m, kP - 2) % kP;
        ans %= kP;
    }
    cout << ans << "\n";
}
