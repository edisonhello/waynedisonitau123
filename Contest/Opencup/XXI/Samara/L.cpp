#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<int> dp(K + 1, N + 1);
    dp[0] = 0;
    vector<bool> From(N);
    vector<int> Value(N);
    for (int i = 0; i < N; ++i) {
        int x = dp[A[i]], y = dp[A[i] - 1];
        From[i] = x > y;
        Value[i] = x;
        dp[A[i]] = min(x, y);
        dp[A[i] - 1]++;
    }
    int t = min_element(dp.begin(), dp.begin() + K) - dp.begin();
    vector<int> ans;
    vector<int> E(N);
    for (int i = N - 1; i >= 0; --i) {
        E[i] = t;
        if (From[i] && A[i] == t) t--;
        dp[A[i]] = Value[i];
        dp[A[i] - 1]--;
    }
    // for (int i = 0; i < N; ++i) cerr << E[i] << " "; cerr << endl;
    int D = 0;
    for (int i = 0; i < N; ++i) {
        if (D == A[i] - 1) {
            D++;
            if (D > E[i]) {
                ans.push_back(i);
                D--;
            }
        }
        assert(D == E[i]);
    }
    cout << ans.size() << "\n";
    for (int u : ans) cout << u + 1 << " ";
    cout << "\n";
}

