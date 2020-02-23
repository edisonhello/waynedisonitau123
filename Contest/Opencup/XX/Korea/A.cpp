#include <bits/stdc++.h>
using namespace std;

string mp[505];
int a[505][505];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> mp[i];
        for (int j = 0; j < m; ++j) {
            a[i][j] = mp[i][j] - '0';
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int ii = n - 1 - i, jj = m - 1 - j;
            // cerr << i << ' ' << j << " <-> " << ii << ' ' << jj << endl;
            if (i == ii && j == jj) {
                if (a[i][j] != 8) {
                    cout << -1 << endl;
                    exit(0);
                } 
            } else {
                if (a[i][j] == 6) {
                    if (a[ii][jj] == 6) ++ans;
                    else if (a[ii][jj] == 9);
                    else exit((cout << -1 << endl, 0));
                } else if (a[i][j] == 7) {
                    if (a[ii][jj] == 7) ++ans;
                    else exit((cout << -1 << endl, 0));
                } else if (a[i][j] == 8) {
                    if (a[ii][jj] == 8);
                    else exit((cout << -1 << endl, 0));
                } else if (a[i][j] == 9) {
                    if (a[ii][jj] == 9) ++ans;
                    else if (a[ii][jj] == 6);
                    else exit((cout << -1 << endl, 0));
                }
            }
        }
    }

    cout << ans / 2 << endl;
}

