#include <bits/stdc++.h>
using namespace std;

vector<int> ans[1025];

int main() {
#ifdef ONLINE_JUDGE
    freopen("analogous.in", "r", stdin);
    freopen("analogous.out", "w", stdout);
#endif
    ans[2] = {1, 4, 2, 3};
    for (int i = 4; i <= 1024; i <<= 1) {
        int k = i >> 1;
        for (int j = 0; j < k; ++j) ans[i].push_back(ans[k][j]);
        for (int j = k; j < i; ++j) ans[i].push_back(ans[k][j] + i);
        for (int j = k; j < i; ++j) ans[i].push_back(ans[k][j]);
        for (int j = 0; j < k; ++j) ans[i].push_back(ans[k][j] + i);
    }
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        if (__builtin_popcount(n) == 1) {
            puts("Yes");
            for (int i = 0; i < n; ++i) printf("%d ", ans[n][i]); puts("");
            for (int i = n; i < 2 * n; ++i) printf("%d ", ans[n][i]); puts("");
        } else {
            puts("No");
        }
    }
}
