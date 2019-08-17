#include <bits/stdc++.h>
#define double long double
using namespace std;

int n;

int d[505][505];
bool bye[505];

long long vssz;

bool bye2[505];
long long get_tot_dis(int start) {
    // cerr << "get_tot_dis = " << start << endl;
    for (int i = 1; i <= n; ++i) bye2[i] = bye[i];
    int alive = 0;
    for (int i = 1; i <= n; ++i) if (i != start && !bye2[i]) ++alive;
    long long ret = 0;
    for (int z = 1; z <= alive; ++z) {
        int farest = start;
        for (int i = 1; i <= n; ++i) if (i != start && !bye[i] && !bye2[i]) {
            if (d[start][farest] < d[start][i]) farest = i;
        }
        int split_at = d[start][farest];
        for (int i = 1; i <= n; ++i) if (i != start && !bye[i] && !bye2[i] && i != farest) {
            int dd = d[start][i] + d[i][farest];
            int more = (dd - d[start][farest]) / 2;
            int di = d[farest][i] - more;
            if (di < split_at) split_at = di;
        }
        ret += 1ll * split_at * (d[start][farest] * 2 - (split_at - 1)) / 2;
        vssz += split_at;
        bye2[farest] = 1;
        // cerr << "farest = " << farest << ", split_at = " << split_at << endl;
    }
    vssz += 1;
    // cerr << "ret = " << ret << ", vssz = " << vssz << endl;
    return ret;
}

double calc(double x, double y, double i) {
    return (i + 1) * x * y - i * (i + 1) / 2 * (x + y) + i * (i + 1) * (2 * i + 1) / 6;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            cin >> d[i][j];
            d[j][i] = d[i][j];
        }
    }
    for (int x = 1; x <= n; ++x) {
        for (int y = x + 1; y <= n; ++y) {
            for (int z = y + 1; z <= n; ++z) {
                bool ok = (d[x][y] + d[y][z] >= d[x][z] && d[x][z] + d[z][y] >= d[x][y] && d[y][x] + d[x][z] >= d[y][z]);
                if (!ok) {
                    puts("impossible");
                    return 0;
                }
                if ((d[x][y] + d[y][z] + d[x][z]) & 1) {
                    puts("impossible");
                    return 0;
                }
            }
        }
    }
    bye[0] = 1;
    for (int i = n + 1; i < 505; ++i) bye[i] = 1;
    double tot = 0;
    long long vs = 0;
    for (int __ = 1; __ <= n - 1; ++__) {
        int farest = 1;
        for (int i = 2; i <= n; ++i) if (!bye[i]) {
            if (d[1][i] > d[1][farest]) farest = i;
        }
        int split_at = d[1][farest];
        for (int i = 2; i <= n; ++i) if (!bye[i] && i != farest) {
            int dd = d[1][i] + d[i][farest];
            int more = (dd - d[1][farest]) / 2;
            int di = d[farest][i] - more;
            if (di < split_at) split_at = di;
        }
        // cerr << "farest = " << farest << " , split_at = " << split_at << endl;
        vssz = 0;
        long long td = get_tot_dis(farest);
        if (__ == 1) vs = vssz;
        tot += (double)split_at * td - calc(split_at - 1, vssz - 1, split_at - 2);
        bye[farest] = 1;
        // cerr << "tot = " << tot << ", inc = " << split_at * td - calc(split_at - 1, vssz - 1, split_at - 2) << endl;
    }
    // cerr << "vs = " << vs << endl;
    cout << fixed << setprecision(20) << tot / ((double)vs * (vs - 1) / 2) << endl;
}
