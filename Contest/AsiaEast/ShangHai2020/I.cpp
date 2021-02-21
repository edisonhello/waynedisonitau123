#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
double angle[1000];

int main() {
    int n, m; cin >> n >> m;

    double perangle = pi / m;
    double ans = 0, ansz = 0;
    for (int i = 1; i <= n; ++i) {
        for (int ii = 1; ii <= n; ++ii) {
            ansz += abs(ii - i);
            for (int j = 1; j < m; ++j) {
                double dd = min((double)min(i, ii) * 2, min(i, ii) * perangle * j) + abs(ii - i);
                ans += dd;
            }
            ansz += i + ii;
        }
    }

    ans = (ans * 2 * m + ansz * m);


    double anso = n * (n + 1) / 2 * m * 2;

    if (m == 1) anso = 0;

    cout << fixed << setprecision(20) << ans + anso << endl;


}

