#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int k; scanf("%d", &k);
        vector<int> a(7);
        for (int i = 0; i < 7; ++i) scanf("%d", &a[i]);
        int s = accumulate(a.begin(), a.end(), 0);
        int ans = 1e9;
        vector<int> b(21);
        for (int i = 0; i < 21; ++i) b[i] = a[i % 7];
        for (int i = 0; i < 21; ++i) {
            int z = 0;
            for (int j = i; j < 21; ++j) {
                z += b[j];
                if (z == k) {
                    ans = min(ans, j - i + 1);
                    break;
                }
            }
        }
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                int c = k;
                for (int p = i; p < 7; ++p) c -= a[p];
                for (int p = 0; p <= j; ++p) c -= a[p];
                if (c < 0) continue;
                int need = (c + s - 1) / s;
                ans = min(ans, 7 - i + j + 1 + need * 7);
            }
        }
        printf("%d\n", ans);
    }
}
