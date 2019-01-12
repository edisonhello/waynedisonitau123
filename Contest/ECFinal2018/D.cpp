#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int x;
        for (int i = 0; i < n + m; ++i) cin >> x;
        if (n <= m) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}
