#include <bits/stdc++.h>
using namespace std;
#define abs(x) ((x)<0?(-(x)):(x))

long long p[100005][2];
__float128 b[100005];
__float128 lambda[100005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n; ++n;
    for (int i = 0; i < n; ++i) cin >> p[i][0] >> p[i][1];
    if ((p[1][1] - p[0][1]) * (p[n - 1][0] - p[n - 2][0]) == -(p[n - 1][1] - p[n - 2][1]) * (p[1][0] - p[0][0])) {
        for (int i = 0; i < n - 1; ++i) {
            b[i] = (__float128)(p[i + 1][1] - p[i][1]) / (p[i + 1][0] - p[i][0]);
            // cout << "b[" << i << "] = " << b[i] << endl;
        }
        for (int i = 1; i < n - 1; ++i) {
            lambda[i] = (b[i] - b[i - 1]) / 2;
            // cout << "lambda[" << i << "] = " << lambda[i] << endl;
        }
        long long x = p[0][0];
        __float128 sigma = 0;
        for (int i = 1; i < n - 1; ++i) {
            sigma += lambda[i] * abs(x - p[i][0]);
        }
        // cout << "sigma: " << sigma << endl;
        if (abs(sigma - p[0][1]) < 1e-20) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    else cout << "No" << endl;
}
