#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int d[maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        memset(d, -1, sizeof(d));
        int k, r; scanf("%d%d", &k, &r);
        d[k] = 0;
        queue<int> q;
        q.push(k);
        while (q.size()) {
            int x = q.front(); q.pop();
            int y = x + 3;
            if (y % 4 == 0) y >>= 1;
            if (d[y] == -1) {
                d[y] = d[x] + 1;
                q.push(y);
            }
            if (x > 2) {
                int y = x - 2;
                if (y % 4 == 0) y >>= 1;
                if (d[y] == -1) {
                    d[y] = d[x] + 1;
                    q.push(y);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < maxn; ++i) {
            if (d[i] != -1 && d[i] <= r) ans = i;
        }
        printf("%d\n", ans);
    }
}
