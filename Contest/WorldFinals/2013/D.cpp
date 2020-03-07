#include <bits/stdc++.h>
using namespace std;

const vector<int> ps = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

long long downprod[100][100], fac[100];
long long C(long long n, long long m) {
    // cerr << "C " << n << ' ' << m << " = " << downprod[n][m] << '/' << fac[m] << endl;
    return downprod[n][m] / fac[m];
}

long long cur_ans;
void dfs(int now, long long taken, long long prod, long long lim, long long val) {
    if (now >= (int)ps.size()) return;
    // cerr << "dfs " << now << ' ' << taken << ' ' << prod << ' ' << lim << ' ' << val << endl;
    if (prod == lim) {
        cur_ans = min(cur_ans, val);
        return;
    }
    if (prod > lim) return;
    for (int a = 0; ; ++a) {
        if (prod > lim / C(taken + a, a)) break;
        dfs(now + 1, taken + a, prod * C(taken + a, a), lim, val);
        if (ps[now] >= cur_ans / val) break;
        val *= ps[now];
    }
}

long long solve(long long n) {
    if (n == 1) return 2;
    cur_ans = LLONG_MAX;
    dfs(0, 0, 1, n, 1);
    return cur_ans;
}

void init() {
    fac[0] = 1;
    downprod[0][0] = 1;
    for (int i = 1; i < 100; ++i) {
        fac[i] = fac[i - 1] * i;
        downprod[i][0] = 1;
        for (int j = 1; j <= i; ++j) downprod[i][j] = downprod[i][j - 1] * (i + 1 - j);
    }
}

int main() {
    init();

    long long n;
    while (cin >> n) {
        long long k = solve(n);
        cout << n << ' ' << k << '\n';
    }
}
