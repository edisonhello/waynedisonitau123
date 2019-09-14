#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
int a[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    sort(a, a + n);
    unordered_set<int> v;
    for (int i = 0; i < n; ++i) v.insert(a[i]);
    int ans = 2;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int d = a[j] - a[i], base = a[j];
            int z = 2;
            while (true) {
                if (v.count(base + d) == 0) break;
                ++z;
                base += d;
            }
            ans = max(ans, z);
        }
    }
    printf("%d\n", ans);
    return 0;
}
