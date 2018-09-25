#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        vector<int> v(3);
        int n; scanf("%d", &n);
        for (int i = 0; i < 3; ++i) scanf("%d", &v[i]);
        sort(v.begin(), v.end());
        int diff = v[1] - v[0];
        int use = min(diff, n);
        v[0] += use;
        n -= use;
        diff = v[2] - v[1];
        use = min(diff, n / 2);
        v[0] += use, v[1] += use;
        n -= use; n -= use;
        use = n / 3;
        v[0] += use, v[1] += use, v[2] += use;
        n -= use, n -= use, n -= use;
        while (n) {
            int i = 0;
            for (int j = 1; j < 3; ++j) if (v[j] < v[i]) i = j;
            --n;
            ++v[i];
        }
        long long ans = v[0] * 1ll * v[1] * v[2];
        printf("%lld\n", ans);
    }
}
