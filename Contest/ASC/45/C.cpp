#include <bits/stdc++.h>
using namespace std;

using data = long long;
pair<int, int> push(int dq, int x) {
    int lp = -1;
    // cout << "push dq = " << dq << " x = " << x << endl;
    while (dq) {
        int last = __builtin_ctz(dq & -dq);
        // cout << "dq = " << dq << " last =  " << last << endl;
        if (last < x) {
           dq ^= 1 << last; 
           lp = last;
        } else {
            break;
        }
    }
    dq |= 1 << x;
    // cout << "result = " << dq << endl;
    // cout << "last = < " << lp << endl;
    return make_pair(dq, lp);
}

int n;

map<int, data> dp[40][40][40];

data dfs(int dq, int x, int a, int p) {
    if (x == n) return 1;
    if (dp[x][a][p].count(dq)) return dp[x][a][p][dq];
    int last = __builtin_ctz(dq & -dq);
    data ans = 0;
    for (int i = p; i <= a + 1; ++i) {
        if (i > last) {
            int d, l; tie(d, l) = push(dq, i);
            if (l == -1) l = p;
            ans += dfs(d, x + 1, a + 1, l);
        } else {
            int d, l; tie(d, l) = push(dq, i);
            if (l == -1) l = p;
            ans += dfs(d, x + 1, a, l);
        }
    }
    return dp[x][a][p][dq] = ans;
}

data ans[40];

void precalc() {
    for (int n = 1; n <= 32; ++n) {
        for (int i = 0; i < 40; ++i) {
            for (int j = 0; j < 40; ++j) {
                for (int k = 0; k < 40; ++k) 
                    dp[i][j][k].clear();
            }
        }
        ::n = n;
        ans[n] = dfs(1, 1, 0, 0);
    }
}

/* ostream &operator<<(ostream &s, __int128 x) {
    static int st[100], sz = 0;
    while (x > 0) {
        st[sz++] = x % 10;
        x /= 10;
    }
    while (sz) s << st[--sz];
    return s;
} */

int main() {
#ifdef ONLINE_JUDGE
    freopen("catalian.in", "r", stdin);
    freopen("catalian.out", "w", stdout);
#endif
    precalc();
    int n; 
    int tc = 1;
    while (cin >> n) {
        if (n == 0) break;
        cout << "Case #" << tc << ": " << ans[n] << endl;
        tc++;
    }
}
