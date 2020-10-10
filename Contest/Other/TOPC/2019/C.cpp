#include <bits/stdc++.h>
using namespace std;

const int maxn = 50 * 100000 + 5;
int dp[maxn];

int main() {
    int n; scanf("%d", &n);
    dp[0] = 0;
    for (int i = 1; i < maxn; ++i) dp[i] = 1e9;
    vector<int> v;
    for (int i = 1; i <= n; ++i) {
        int c; scanf("%d", &c);
        for (int j = c; j < maxn; ++j)
            dp[j] = min(dp[j], dp[j - c] + 1);
        v.push_back(c);
    }
    for (int i = 1; i <= 100000; ++i) {
        int z = -1;
        for (int j = 0; j < n; ++j) {
            if (v[j] <= i) z = v[j];
        }
        if (dp[i - z] + 1 != dp[i]) {
            printf("%d\n", i);
            return 0;
        }
    }
    puts("-1");
}
