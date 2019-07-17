#include <bits/stdc++.h>
using namespace std;
 
int main() {
    double h1, t1, h2, t2; cin >> h1 >> t1 >> h2 >> t2;
    double k = sqrt(h1 / h2);
    double ans = (t1 - k * t2) / (1 - k);
    cout << fixed << setprecision(20) << ans << endl;
}
