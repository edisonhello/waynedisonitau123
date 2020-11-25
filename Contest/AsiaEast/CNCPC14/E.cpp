#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        if (N == 1 && K == 1) {
            cout << "1\n";
            continue;
        }
        if (K == N) {
            cout << "-1\n";
            continue;
        }
        if (K % 2 == 0) {
            cout << "-1\n";
            continue;
        }
        uint64_t X = ((1ULL << (K + 1)) - 1);
        vector<uint64_t> V;
        for (int i = 0; i < K + 1; ++i) {
            V.push_back(X ^ (1ULL << i));
        }
        X = ((1ULL << (K - 1)) - 1);
        for (int i = K + 1; i < N; ++i) {
            V.push_back((1ULL << i) ^ X);
        }
        sort(V.begin(), V.end());
        for (int i = 0; i < N; ++i) cout << V[i] << " \n"[i + 1 == N];
    }
}

