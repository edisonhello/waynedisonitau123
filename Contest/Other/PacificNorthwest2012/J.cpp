#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, B, T, X, Y, Z;
    while (cin >> H >> B >> T >> X >> Y >> Z) {
        vector<int64_t> dp(H + 1);
        for (int h = 0; h <= H; ++h) {
            for (int p : {X, Y, Z}) {
                if (h + p <= H) {
                    int64_t Add = (1LL * (H - h - p) * (B - T) + 1LL * T * H) / (1LL * H * p);
                    Add *= Add;
                    Add *= p;
                    Add *= p;
                    Add *= p;
                    dp[h + p] = max(dp[h + p], dp[h] + Add);
                }
            }
        }
        cout << *max_element(dp.begin(), dp.end()) << "\n";
    }
}
