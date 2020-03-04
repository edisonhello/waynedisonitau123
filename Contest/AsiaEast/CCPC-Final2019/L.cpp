#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        int n, m;
        cin >> n >> m;
        if (n > m) swap(n, m);
        cout << "Case #" << tc << ": ";
        if (n == 1 && m == 1) cout << 1 << '\n';
        else if (n == 1) cout << 2 << "\n";
        else cout << (n + n + m + m - 4) << "\n";
    }
}

