#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    int64_t S;
    cin >> S;

    int64_t sum = 1LL * N * (N - 1) / 2;
    int rem = ((sum - S) % N + N) % N;
    int64_t t = 0;
    int iter = 0;
    while (iter < 2 * N && 1LL * (K + 1) * t % N != rem) t++, iter++;

    if (1LL * (K + 1) * t % N != rem) {
        cout << "-1\n";
        return 0;
    }

    auto Do = [&](int64_t t) {
        assert((sum - (K + 1) * t - S) % N == 0);
        int64_t v = -((sum - (K + 1) * t - S) / N);
        if (v < 0) return;
        int64_t pref = 0;
        vector<int> diff;
        for (int i = N - 1; i > 0; --i) {
            diff.push_back(1);
            pref++;
            if (t >= i && pref - (K + 1) + v >= 0) {
                diff.back() = -K;
                pref -= (K + 1);
                t -= i;
            }
        }
        assert(t == 0);
        cout << v << " ";
        for (int i = 0; i < N - 1; ++i) {
            v += diff[i];
            cout << v << " ";
        }
        cout << endl;
        exit(0);
    };

    auto Try = [&](int64_t t) {
         assert((sum - (K + 1) * t - S) % N == 0);
         int64_t v = -((sum - (K + 1) * t - S) / N);
         if (v < 0) return;
         int64_t g = min(static_cast<int64_t>(N - 1), v / K);
         int64_t D = ((N - 1) + (N - g)) * g / 2;
         if (D >= t) Do(t);
         int64_t W = v - 1LL * g * K;
         int64_t y = K - W; // need y ones
         int64_t C = g + y; // used C numbers
         int64_t r = N - 1 - C; // r numbers remaining
         if (r <= 0) return;
         int64_t T = (r + (K + 1) - 1) / (K + 1); // number of K + 1
         D += ((N - 1 - C) + (N - 1 - C - (T - 1) * (K + 1))) * T / 2;
         if (D >= t) Do(t);
    };


    constexpr int kIter = 20'000'000;
    for (int i = 0; i < kIter && t <= 1LL * N * (N - 1) / 2; ++i) {
        Try(t);
        t += N / __gcd(N, K + 1);
    }

    t = 1LL * N * (N - 1) / 2;
    while (1LL * (K + 1) * t % N != rem) t--;

    for (int i = 0; i < kIter && t >= 0; ++i) {
        Try(t);
        t -= N / __gcd(N, K + 1);
    }

    cout << "-1\n";
    return 0;
}

