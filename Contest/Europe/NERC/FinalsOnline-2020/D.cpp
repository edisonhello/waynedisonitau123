#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<uint32_t> Mask(N);
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        assert(s.size() == 8);
        for (int j = 0; j < 8; ++j) {
            if (s[j] == 'W') Mask[i] |= (1 << j);
        }
    }
    int Init = 0, M = 0;
    for (int i = 0; i < min(8, N); ++i) {
        vector<bool> dp(i + 1);
        dp[i] = 0;
        for (int j = i - 1; j >= 0; --j) {
            for (int k = 1; k <= 8; ++k) {
                if (j + k <= i) {
                    if (8 - __builtin_popcount(Mask[j] ^ Mask[j + k]) >= k && !dp[j + k]) {
                        dp[j] = 1;
                        break;
                    }
                }
            }
        }
        if (dp[0]) Init |= (1 << i);
        if (i == 7) {
            for (int j = 0; j < 8; ++j) {
                if (dp[j]) M |= (1 << j);
            }
        }
    }
    if (N <= 8) {
        for (int i = 0; i < N; ++i) {
            if (Init >> i & 1) cout << 1;
            else cout << 2;
        }
        cout << "\n";
        return 0;
    }
    vector<vector<int>> dp(N, vector<int>(256));
    for (int i = 0; i < 256; ++i) dp[7][i] = i & 1;
    for (int i = 8; i < N; ++i) {
        for (int j = 0; j < 256; ++j) {
            int k = 0;
            int g = i - 8;
            for (int s = 0; s < 8; ++s) {
                int cnt = 8 - __builtin_popcount(Mask[g] ^ Mask[g + s + 1]);
                if (cnt >= s + 1 && !(j >> s & 1)) k = 1;
            }
            int p = (j << 1 & 255) | k;
            dp[i][j] = dp[i - 1][p];
        }
    }
    for (int i = 0; i < 8; ++i) {
        if (Init >> i & 1) cout << 1;
        else cout << 2;
    }
    for (int i = 8; i < N; ++i) {
        vector<bool> D(8);
        D[7] = 0;
        for (int j = 6; j >= 0; --j) {
            for (int k = 1; k <= 8; ++k) {
                if (j + k <= 7 && 8 - __builtin_popcount(Mask[i - 7 + j] ^ Mask[i - 7 + j + k]) >= k) {
                    if (!D[j + k]) {
                        D[j] = true;
                        break; 
                    }
                }
            }
        }
        int M = 0;
        for (int j = 0; j < 8; ++j) {
            if (D[j]) M |= (1 << j);
        }
        if (dp[i][M]) cout << 1;
        else cout << 2;
    }
    cout << '\n';
}

