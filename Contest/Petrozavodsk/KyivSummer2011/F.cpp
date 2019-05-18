#include <bits/stdc++.h>
using namespace std;


int main() {
#ifdef ONLINE_JUDGE
    freopen("continued.in", "r", stdin);
    freopen("continued.out", "w", stdout);
#endif
    int n, m; cin >> n >> m;
    if (n % m == 0) {
        cout << 1 << '\n';
        for (int z = 0; z < n / m - 1; ++z) {
            cout << '1';
            for (int x = 0; x < m - 1; ++x) cout << '0';
        }
        cout << '1';
        cout << ' ';
        for (int i = 0; i < m; ++i) cout << '9';
        cout << '\n';
    } else {
        cout << 3 << '\n';
        if (n < m) cout << '0';
        else {
            for (int z = 0; z < n / m - 1; ++z) {
                cout << '1';
                for (int x = 0; x < m - 1; ++x) cout << '0';
            }
            cout << '1';
            for (int i = 0; i < n % m; ++i) cout << '0';
        }
        cout << ' ';
        for (int i = 0; i < m - n % m; ++i) cout << '9';
        cout << ' ';
        cout << '1';
        cout << ' ';
        for (int i = 0; i < n % m; ++i) cout << '9';
        cout << '\n';
    }
}
