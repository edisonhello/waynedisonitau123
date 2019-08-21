#include <bits/stdc++.h>
using namespace std;


int main() {
    int m = 300000, n = 300000, r = 1000;
    cout << m << " " << n << " " << r << endl;
    vector<double> cmr;
    for (int i = 0; i < m; ++i) cmr.push_back((double)(rand() % 100000) / 10);
    sort(cmr.begin(), cmr.end());
    for (double i : cmr) cout << fixed << setprecision(1) << i << " "; cout << endl;
    for (int i = 0; i < n; ++i) cout << fixed << setprecision(1) << (double)(rand() % 100000) / 10 << " "; cout << endl;
}
