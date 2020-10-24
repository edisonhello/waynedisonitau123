#include <bits/stdc++.h>
using namespace std;

int pre[10005 * 370];
int Did[10000][13][35];

char str[10];
int Contains(int Y, int M, int D) {
    sprintf(str, "%04d%02d%02d", Y, M, D);
    for (int i = 0; i < 6; ++i) {
        if (str[i] == '2' && str[i + 1] == '0' && str[i + 2] == '2') {
            return 1;
        }
    }
    return 0;
}

int GetD(int Y, int M) {
    if (M == 2) {
        if (Y % 4 == 0) {
            if (Y % 100 == 0) {
                if (Y % 400 == 0) {
                    return 29;
                } else return 28;
            } else return 29;
        } else return 28;
    }
    if (M == 1) return 31;
    if (M == 3) return 31;
    if (M == 4) return 30;
    if (M == 5) return 31;
    if (M == 6) return 30;
    if (M == 7) return 31;
    if (M == 8) return 31;
    if (M == 9) return 30;
    if (M == 10) return 31;
    if (M == 11) return 30;
    if (M == 12) return 31;
    assert(0);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int c = 0;
    for (int Y = 2000; Y <= 9999; ++Y) {
        for (int M = 1; M <= 12; ++M) {
            int mxd = GetD(Y, M);
            for (int D = 1; D <= mxd; ++D) {
                ++c;
                Did[Y][M][D] = c;
                pre[c] = pre[c - 1] + Contains(Y, M, D);
            }
        }
    }
    

    int t; cin >> t; while (t--) {
        int a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;
        cout << pre[Did[d][e][f]] - pre[Did[a][b][c] - 1] << '\n';
    }
}

