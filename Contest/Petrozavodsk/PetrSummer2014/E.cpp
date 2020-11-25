#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("jumping.in", "r", stdin);
    freopen("jumping.out", "w", stdout);
    int A, B;
    cin >> A >> B;
    vector<int> D(B - A + 1, -1);
    for (int i = 2; i * i <= B; ++i) {
        int x = ((A - 1) / i + 1) * i;
        while (x <= B) {
            if (D[x - A] == -1) D[x - A] = i;
            x += i;
        }
    }
    for (int i = A; i <= B; ++i) {
        if (D[i - A] == -1) D[i - A] = i;
    }
    constexpr int kP = 1'000'000'000 + 7;
    vector<vector<int>> dp(B - A + 1, vector<int>(2));
    vector<int> tag(B - A + 1);
    vector<int> sum(B - A + 1);
    dp[0][0] = 1; // 0: Rita, 1: Pasha
    int G = 0;
    for (int i = A; i <= B; ++i) {
        (G += tag[i - A]) >= kP ? G -= kP : 0;
        dp[i - A][1] += G;
        dp[i - A][1] >= kP ? dp[i - A][1] -= kP : 0;
        {
            int L = i - i / D[i - A];
            int R = i - D[i - A];
            if (L <= R) {
                if (R >= A) {
                    dp[i - A][0] += sum[R - A];
                    dp[i - A][0] >= kP ? dp[i - A][0] -= kP : 0;
                }
                if (L - 1 >= A) {
                    dp[i - A][0] += kP - sum[L - 1 - A];
                    dp[i - A][0] >= kP ? dp[i - A][0] -= kP : 0;
                }
            }
        }
        {
            int L = i + D[i - A];
            int R = i + i / D[i - A];
            if (L <= R) {
                if (L <= B) {
                    tag[L - A] += dp[i - A][0];
                    tag[L - A] >= kP ? tag[L - A] -= kP : 0;
                }
                if (R + 1 <= B) {
                    tag[R + 1 - A] += kP - dp[i - A][0];
                    tag[R + 1 - A] >= kP ? tag[R + 1 - A] -= kP : 0;
                }
            }
        }
        sum[i - A] = dp[i - A][1];
        if (i > A) {
            sum[i - A] += sum[i - A - 1];
            sum[i - A] >= kP ? sum[i - A] -= kP : 0;
        }
    }
    cout << (dp[B - A][0] + dp[B - A][1]) % kP << "\n";
}

