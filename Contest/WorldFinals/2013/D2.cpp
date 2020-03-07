#include <bits/stdc++.h>
using namespace std;

const vector<int> ps = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

long long c[100][100];
long double dc[100][100];
long long C(long long n, long long m) {
    // cerr << "C " << n << ' ' << m << " = " << downprod[n][m] << '/' << fac[m] << endl;
    // return downprod[n][m] / fac[m];
    if (dc[n][m] >= LLONG_MAX) return LLONG_MAX;
    return c[n][m];
}

long long cur_ans;
void dfs(int now, int prev, int taken, long long prod, long long want, long long val) {
    // cerr << "dfs " << now << ' ' << taken << ' ' << prod << ' ' << want << ' ' << val << endl;
    if (prod == want) {
        cur_ans = min(cur_ans, val);
        return;
    }
    if (now >= (int)ps.size()) return;
    if (prod > want) return;
    if (prev == 0) return;
    for (int a = 0; a <= prev; ++a) {
        if (dc[taken + a][a] > LLONG_MAX) break;
        if (prod > want / C(taken + a, a)) break;
        dfs(now + 1, a, taken + a, prod * C(taken + a, a), want, val);
        if ((long double)ps[now] * (long double) val >= cur_ans) break;
        if (ps[now] >= cur_ans / val) break;
        val *= ps[now];
    }
}

long long solve(long long n) {
    if (n == 1) return 2;
    cur_ans = LLONG_MAX;
    dfs(0, INT_MAX, 0, 1, n, 1);
    return cur_ans;
}

void init() {
    c[0][0] = 1;
    dc[0][0] = 1;
    for (int i = 1; i < 100; ++i) {
        for (int j = 0; j <= i; ++j) {
            c[i][j] = c[i - 1][j];
            dc[i][j] = dc[i - 1][j];
            if (j) {
                c[i][j] += c[i - 1][j - 1];
                dc[i][j] += dc[i - 1][j - 1];
            }
            if (dc[i][j] >= 1e30) dc[i][j] = 1e30;
        }
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
