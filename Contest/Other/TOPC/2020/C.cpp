#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> x(N), y(N);
    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
    }
    vector<tuple<int64_t, int, int>> event;
    vector<double> md(N, 1E100);
    vector<vector<double>> D(N, vector<double>(N));
    vector<multiset<double>> s(N);
    for (int i = 0; i < N; ++i) {
        double R = 1e100;
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            int64_t dist = 1LL * (x[i] - x[j]) * (x[i] - x[j]) + 1LL * (y[i] - y[j]) * (y[i] - y[j]);
            D[i][j] = sqrt(dist) / 2;
            md[i] = min(md[i], D[i][j]);
            s[i].insert(D[i][j]);
        }
    }
    vector<bool> used(N);
    double ans = 0;
    constexpr double P = acos(-1);
    vector<double> rad(N);
    for (int i = 0; i < N; ++i) {
        int k = -1;
        for (int j = 0; j < N; ++j) {
            if (used[j]) continue;
            if (k == -1 || md[j] < md[k]) k = j;
        }
        ans += md[k] * md[k] * P;
        used[k] = true;
        rad[k] = md[k];
        for (int j = 0; j < N; ++j) {
            if (used[j]) continue;
            auto it = s[j].lower_bound(D[k][j] - 1E-9);
            assert(it != s[j].end());
            s[j].erase(it);
            int64_t dist = 1LL * (x[k] - x[j]) * (x[k] - x[j]) + 1LL * (y[k] - y[j]) * (y[k] - y[j]);
            double E = sqrt(dist) - rad[k];
            s[j].insert(E);
            md[j] = *s[j].begin();
        }
    }
    cout << fixed << setprecision(20) << ans << "\n";
}
