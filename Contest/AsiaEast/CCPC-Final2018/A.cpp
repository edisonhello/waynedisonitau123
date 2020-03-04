#include <bits/stdc++.h>
using namespace std;

pair<int, int> p[100005];

int main() {
    int t; scanf("%d", &t); for (int T = 1; T <= t; ++T) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) scanf("%d", &p[i].first);
        for (int i = 0; i < n; ++i) scanf("%d", &p[i].second);
        sort(p, p + n);
        int cnt = 0;
        for (int i = 0; i < n; ++i) if (p[i].second <= m) {
            m -= p[i].second;
            ++cnt;
        } else break;
        printf("Case %d: ", T);
        printf("%d\n", cnt);
    }
}
