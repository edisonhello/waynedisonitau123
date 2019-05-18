#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef ONLINE_JUDGE
    freopen("drunkard.in", "r", stdin);
    freopen("drunkard.out", "w", stdout);
#endif
    int p, q; 
    while (scanf("%d%d", &p, &q) != EOF) {
        if (p == 0 && q == 0) break;
        printf("%d\n", q + 1);
        vector<int> ans(q + 1, -1);
        ans[0] = q, ans[q] = q - 1;
        ans[p] = 0;
        for (int i = 0, j = 1; i < q + 1; ++i) {
            if (ans[i] == -1) {
                ans[i] = j++;
            }
        }
        for (int i = 0; i < q - 1; ++i) {
            for (int j = 0; j < q + 1; ++j) {
                if (ans[j] == i) {
                    printf("%d %d\n", ans[j - 1] + 1, ans[j + 1] + 1);
                }
            }
        }
    }
}
