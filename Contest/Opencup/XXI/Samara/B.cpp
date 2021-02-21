#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N), B(N), C(N), D(N);
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i] >> D[i];
    double l = 0, r = 1e18;
    for (int iter = 0; iter < 100; ++iter) {
        double mid = 0.5 * (l + r);
        double sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += max(B[i] - mid * A[i], D[i] - mid * C[i]);
        }
        if (sum >= 0) l = mid;
        else r = mid;
    }
    cout << fixed << setprecision(20) << l << "\n";
}

