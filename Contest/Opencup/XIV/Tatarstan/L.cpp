#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    long long sum = 0, is0 = 0, not0 = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        int t; cin >> t;
        if (t == 0) ++is0; else ++not0;
        sum += t;
    }
    if (is0 > not0) cout << -1 << endl;
    else cout << sum << endl;
}
