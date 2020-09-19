#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    int res = 1;
    constexpr int kMod = 1'000'000'000 + 7;
    for (int i = 1; i <= N - 2; ++i) {
        res = 1LL * res * i % kMod;
    }
    const int M = (kMod + 1) / 2;
    int sum = 0;
    vector<int> D;
    for (int i = 0; i < N; ++i) {
        int X;
        cin >> X;
        sum += X;
        if (X == 3) {
            res = 1LL * res * M % kMod; 
        }
        D.push_back(X);
    }
    if (sum != 2 * (N - 1)) res = 0;
    cout << res << "\n";
}

