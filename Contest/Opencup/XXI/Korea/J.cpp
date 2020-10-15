#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    string S;
    cin >> S;
    int Q;
    cin >> Q;
    vector<int> x(Q), y(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> x[i] >> y[i];
    }
    vector<vector<pair<int, int>>> dp(N, vector<pair<int, int>>(4));
    const int px[4] = {1, 0, -1, 0};
    const int py[4] = {0, 1, 0, -1};
    char C[5] = "LDRU";
    vector<int> D(256);
    for (int i = 0; i < 4; ++i) D[C[i]] = i;
    vector<int> sx(N + 1), sy(N + 1);
    for (int i = 0; i < N; ++i) {
        sx[i + 1] = sx[i];
        sy[i + 1] = sy[i];
        if (S[i] == 'L') sx[i + 1]--;
        if (S[i] == 'R') sx[i + 1]++;
        if (S[i] == 'U') sy[i + 1]++;
        if (S[i] == 'D') sy[i + 1]--;
    }
    map<pair<int, int>, int> prv;
    for (int i = N - 1; i >= 0; --i) {
        for (int j = 0; j < 4; ++j) {
            if (D[S[i]] == j) {
                if (i == N - 1) {
                    dp[i][j].first = px[j];
                    dp[i][j].second = py[j];
                } else {
                    dp[i][j].first = dp[i + 1][j].first;
                    dp[i][j].second = dp[i + 1][j].second;
                }
                continue;
            }
            int g = N + 1, v = -1;
            for (int k = 0; k < 4; ++k) {
                int dx = px[k] - px[j];
                int dy = py[k] - py[j];
                int X = sx[i] + dx;
                int Y = sy[i] + dy;
                auto it = prv.find(make_pair(X, Y));
                if (it != prv.end()) {
                    if (it->second < g) {
                        g = it->second;
                        v = k;
                    }
                }
            }
            if (g == N + 1) {
                dp[i][j].first = px[j] + sx[N] - sx[i];
                dp[i][j].second = py[j] + sy[N] - sy[i];
            } else {
                dp[i][j].first = dp[g][v].first;
                dp[i][j].second = dp[g][v].second;
            }
        }
        prv[make_pair(sx[i], sy[i])] = i;
    }
    vector<int> Ax(Q), Ay(Q);
    for (int i = 0; i < Q; ++i) {
        bool ok = false;
        for (int j = 0; j < 4; ++j) {
            if (x[i] == px[j] && y[i] == py[j]) {
                if (D[S[0]] == j) {
                    if (N == 1) {
                        Ax[i] = px[j];
                        Ay[i] = py[j];
                    } else {
                        Ax[i] = dp[1][j].first;
                        Ay[i] = dp[1][j].second;
                    }
                    ok = true;
                }
            }
        }
        if (ok) continue;
        int g = N + 1, v = -1;
        for (int j = 0; j < 4; ++j) {
            int dx = px[j] - x[i];
            int dy = py[j] - y[i];
            auto it = prv.find(make_pair(dx, dy));
            if (it != prv.end()) {
                if (it->second < g) {
                    g = it->second;
                    v = j;
                }
            }
        }
        if (g < N) {
            Ax[i] = dp[g][v].first; 
            Ay[i] = dp[g][v].second; 
        } else {
            Ax[i] = x[i] + sx[N];
            Ay[i] = y[i] + sy[N];
        }
    }
    for (int i = 0; i < Q; ++i) cout << Ax[i] << " " << Ay[i] << "\n";
    return 0;
}

