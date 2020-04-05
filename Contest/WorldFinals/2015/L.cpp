#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long double> p(4);
    vector<vector<long double>> pw(4, vector<long double>(n + 1, 1));
    for (int i = 0; i < 4; ++i) {
        cin >> p[i];
        for (int j = 1; j <= n; ++j) {
            pw[i][j] = pw[i][j - 1] * p[i];
        }
    }

    vector<vector<int64_t>> cnk(n + 1, vector<int64_t>(n + 1));
    for (int i = 0; i <= n; ++i) {
        cnk[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            cnk[i][j] = cnk[i - 1][j] + cnk[i - 1][j - 1];
        }
    }

    priority_queue<pair<long double, int64_t>, vector<pair<long double, int64_t>>, greater<pair<long double, int64_t>>> pq;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; i + j <= n; ++j) {
            for (int k = 0; i + j + k <= n; ++k) {
                int l = n - i - j - k;
                long double p = pw[0][i] * pw[1][j] * pw[2][k] * pw[3][l];
                int64_t ways = cnk[n][i] * cnk[n - i][j] * cnk[n - i - j][k];
                pq.emplace(p, ways);
            }
        }
    }

    long double ans = 0.0;

    while (!pq.empty()) {
        long double p = pq.top().first;
        int64_t ways = pq.top().second;
        pq.pop();
        if (ways > 1) {
            ans += (ways / 2) * (2 * p);
            pq.emplace(p + p, ways / 2);
            ways %= 2;
        }
        if (pq.empty()) break;
        if (ways == 0) continue;
        long double q = pq.top().first;
        int64_t nways = pq.top().second;
        pq.pop();
        ans += p + q;
        pq.emplace(p + q, 1);
        if (nways - 1 > 0) {
            pq.emplace(q, nways - 1);
        }
    }
    cout << fixed << setprecision(12) << ans << "\n";
}

