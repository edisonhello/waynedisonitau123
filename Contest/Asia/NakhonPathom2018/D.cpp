#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 5;
int a[maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        int ans = 0;
        for (int i = 0, j = 0; i < n; i = j) {
            for (j = i; j < n && a[j] - a[i] <= 20; ++j);
            ++ans;
        }
        printf("%d\n", ans);
    }
}
