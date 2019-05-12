#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
int d[maxn];

int main() {
    int n; scanf("%d", &n);
    set<int> s;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &d[i]);
        for (int j = 1; j * j <= d[i]; ++j) {
            if (d[i] % j == 0) {
                s.insert(j);
                s.insert(d[i] / j);
            }
        }
    }

    int ans = 1;
    while (s.count(ans)) ans++;
    printf("%d\n", ans);
}
