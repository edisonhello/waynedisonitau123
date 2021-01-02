#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> L(N), R(N), U(N), D(N);
        for (int i = 0; i < N; ++i) {
            cin >> L[i] >> D[i] >> R[i] >> U[i];
        }

        auto Solve = [&](vector<int> L, vector<int> R) {
            vector<int> event(L.begin(), L.end());
            event.insert(event.end(), R.begin(), R.end());
            sort(event.begin(), event.end());
            event.resize(unique(event.begin(), event.end()) - event.begin());
            sort(R.begin(), R.end());
            sort(L.begin(), L.end());
            int i = 0, j = 0, Rcnt = 0, Lcnt = N;
            int64_t Rsum = 0, Lsum = accumulate(L.begin(), L.end(), 0LL);
            int64_t res = 1'000'000'000'000'000'000;
            for (int e : event) {
                while (i < N && R[i] < e) {
                    Rsum += R[i++];
                    Rcnt++;
                }
                while (j < N && L[j] <= e) {
                    Lsum -= L[j++];
                    Lcnt--;
                }
                res = min(res, static_cast<int64_t>(1LL * e * Rcnt - Rsum + Lsum - 1LL * e * Lcnt));
            }
            return res;
        };

        cout << Solve(L, R) + Solve(D, U) << "\n";
    }
}

