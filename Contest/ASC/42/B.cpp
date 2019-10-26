#include <bits/stdc++.h>
using namespace std;

double dfs(int now, int dist, double wp, int left) {
    if (now >= dist) return 1;
    if (now <= 0) return 0;
    if (left <= 0) return 0;
    int bet = min(now, dist - now);
    return wp * dfs(now + bet, dist, wp, left - 1) + (1 - wp) * dfs(now - bet, dist, wp, left - 1);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("betting.in", "r", stdin);
    freopen("betting.out", "w", stdout);
#endif
    int n, s, p, t; while (cin >> n >> s >> p >> t) {
        if ((n|s|p|t) == 0) break;
        cout << fixed << setprecision(12) << dfs(s, n, (double)p / 100, t) << '\n';
    }
}
