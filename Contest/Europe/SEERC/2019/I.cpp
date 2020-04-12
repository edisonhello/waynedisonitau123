#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    int res = 0;
    for (int i = 0; i < n; ++i) {
        int x = 1e9;
        for (int j = 0; j < n; ++j) {
            x = min(x, abs(a[i] - b[j]));
        }
        res = max(res, x);
    }
    cout << res << "\n";
}

