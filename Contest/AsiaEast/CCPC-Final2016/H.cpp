#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int Solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> A(N);
    vector<int> ds;
    for (int i = 0; i < N; ++i) {
        int C;
        cin >> C;
        A[i].resize(C);
        for (int j = 0; j < C; ++j) {
            cin >> A[i][j];
            ds.push_back(A[i][j]);
        }
    }
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    vector<int> AM(N);
    for (int i = 0; i < N; ++i) {
        for (int &u : A[i]) {
            u = lower_bound(ds.begin(), ds.end(), u) - ds.begin();
            AM[i] |= (1 << u);
        }
    }

    vector<vector<int>> B(M);
    int K = ds.size();
    vector<int> mask(M);
    for (int i = 0; i < M; ++i) {
        int D;
        cin >> D;
        for (int j = 0; j < D; ++j) {
            int x;
            cin >> x;
            if (!binary_search(ds.begin(), ds.end(), x)) continue;
            x = lower_bound(ds.begin(), ds.end(), x) - ds.begin();
            mask[i] |= (1 << x);
        }
    }

    vector<int> dp(1 << M);
    for (int i = 0; i < N; ++i) {
        vector<int> ndp(dp.begin(), dp.end());
        for (int s = 0; s < (1 << M); ++s) {
            for (int a = 0; a < M; ++a) {
                if (!(s >> a & 1)) continue;
                if ((mask[a] & AM[i]) == 0) continue;
                if ((mask[a] & AM[i]) == AM[i]) {
                    ndp[s ^ (1 << a)] = max(dp[s] + 1, ndp[s ^ (1 << a)]);
                }
                for (int b = a + 1; b < M; ++b) {
                    if (!(s >> b & 1)) continue;
                    if ((mask[b] & (AM[i] & ~mask[a])) == 0) continue;
                    if (((mask[a] | mask[b])  & AM[i]) == AM[i]) {
                        ndp[s ^ (1 << a) ^ (1 << b)] = max(dp[s] + 1, ndp[s ^ (1 << a) ^ (1 << b)]);
                    }
                    for (int c = b + 1; c < M; ++c) {
                        if (!(s >> c & 1)) continue;
                        if ((mask[c] & (AM[i] & ~(mask[a] | mask[b]))) == 0) continue;
                        if (((mask[a] | mask[b] | mask[c])  & AM[i]) == AM[i]) {
                            ndp[s ^ (1 << a) ^ (1 << b) ^ (1 << c)] = max(dp[s] + 1, ndp[s ^ (1 << a) ^ (1 << b) ^ (1 << c)]);
                        }
                    }
                }
            }
        }
        dp = ndp;
    }
    return *max_element(dp.begin(), dp.end());
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": " << Solve() << "\n";
    }
}

