#include <bits/stdc++.h>
using namespace std;

int req[505][505], cur[505][505], ans[505][505];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        for (int j = 1; j <= n; ++j) {
            req[i][j] = s[j - 1] - '0';
        }
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = i - 1; j >= 1; --j) {
            if (cur[j][i] != req[j][i]) {
                // cerr << "cur " << j << ' ' << i << " = " << cur[j][i] << " diff req " << req[j][i] << endl;
                ans[j][i] = 1;
                cur[j][i] = (cur[j][i] + 1) % 10;
                for (int k = 1; k < j; ++k) {
                    cur[k][i] = (cur[k][i] + cur[k][j]) % 10;
                }
                // cerr << "add edge " << j << " to " << i << endl;
                // cerr << "cur: " << endl;
                // for (int i = 1; i <= n; ++i) {
                //     for (int j = 1; j <= n; ++j) {
                //         cout << cur[i][j];
                //     }
                //     cout << endl;
                // }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << ans[i][j];
        }
        cout << endl;
    }
}

