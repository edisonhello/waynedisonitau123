#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int x[maxn];

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; ++i) 
        scanf("%d", &x[i]);

    if (x[n] % k != 0) {
        puts("0");
        return 0;
    }

    int d = x[n] / k;
    map<int, int> cnt;
    for (int i = 1; i <= n; ++i)
        ++cnt[x[i] % d];

    for (auto it : cnt) {
        if (it.second == k) {
            puts("1");
            return 0;
        }
    }
    puts("0");
}
