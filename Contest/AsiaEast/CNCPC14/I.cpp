#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    while (cin >> N) {
        vector<int> D(N * N);
        int X = 1'000'000'000;
        for (int i = 0; i < N * N; ++i) {
            cin >> D[i];
            if (D[i] > 0) X = min(X, D[i]);
        }
        cout << count(D.begin(), D.end(), X) / 2 << "\n";
    }
}

