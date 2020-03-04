#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        if (n % 2 == 1 && m % 2 == 1) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) cout << "(";
                cout << '\n';
            }
        } else if (n % 2 == 1 && m % 2 == 0) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m / 2; ++j) cout << "(";
                for (int j = 1; j <= m / 2; ++j) cout << ")";
                cout << '\n';
            }
        } else if (n % 2 == 0 && m % 2 == 1) {
            for (int i = 1; i <= n / 2; ++i) {
                for (int j = 1; j <= m; ++j) cout << "(";
                cout << '\n';
            }
            for (int i = 1; i <= n / 2; ++i) {
                for (int j = 1; j <= m; ++j) cout << ")";
                cout << '\n';
            }
        } else if (n == 2) {
            for (int i = 1; i <= m; ++i) cout << "("; cout << '\n';
            for (int i = 1; i <= m; ++i) cout << ")"; cout << '\n';
        } else if (m == 2) {
            for (int i = 1; i <= n; ++i) cout << "()\n";
        } else if (n == 4) {
            for (int i = 1; i <= m; ++i) cout << "("; cout << '\n';
            for (int i = 1; i <= m / 2; ++i) cout << "(";
            for (int i = 1; i <= m / 2; ++i) cout << ")"; cout << '\n';
            for (int i = 1; i <= m / 2; ++i) cout << ")";
            for (int i = 1; i <= m / 2; ++i) cout << "("; cout << '\n';
            for (int i = 1; i <= m; ++i) cout << ")"; cout << '\n';
        } else if (m == 4) {
            for (int i = 1; i <= n / 2; ++i) cout << "(())\n";
            for (int i = 1; i <= n / 2; ++i) cout << "()()\n";
        } else {
            vector<string> v(n, string(m, ' '));
            for (int i = 0; i < m; ++i) v[0][i] = '(';
            for (int i = 0; i < m; ++i) v[n - 1][i] = ')';
            for (int i = 0; i < n; ++i) v[i][0] = '(';
            for (int i = 0; i < n; ++i) v[i][m - 1] = ')';
            for (int i = 1; i < n - 1; ++i) {
                for (int j = 1; j < m - 1; ++j) {
                    v[i][j] = ((i + j) % 2 == 0 ? '(' : ')');
                }
            }
            for (int i = 0; i < n; ++i) cout << v[i] << '\n';
        }
    }
}
