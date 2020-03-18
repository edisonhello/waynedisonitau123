#include <bits/stdc++.h>
using namespace std;

int n, k;
string mp[10];
int ship[10];
bool cur[10][10];

int dfs(int now) {
    // cerr << "dfs " << now << endl;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         cerr << cur[i][j];
    //     }
    //     cerr << endl;
    // }
    if (now >= k) {
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            if (mp[i][j] == '.');
            else if (mp[i][j] == 'O') {
                if (!cur[i][j]) return 0;
            } else {
                if (cur[i][j]) return 0;
            }
        }
        return 1;
    }
    int l = ship[now];
    // cerr << "now = " << now << endl;
    // cerr << "l = " << l << endl;
    int tot = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i + l - 1 < n) {
                bool ok = 1;
                for (int k = 0; k < l; ++k) {
                    if (cur[i + k][j]) { ok = 0; break; }
                    if (mp[i + k][j] == 'X') { ok = 0; break; }
                }
                if (ok) {
                    for (int k = 0; k < l; ++k) cur[i + k][j] = 1;
                    tot += dfs(now + 1);
                    for (int k = 0; k < l; ++k) cur[i + k][j] = 0;
                }
            } 
            if (j + l - 1 < n && l > 1) {
                bool ok = 1;
                for (int k = 0; k < l; ++k) {
                    if (cur[i][j + k]) { ok = 0; break; }
                    if (mp[i][j + k] == 'X') { ok = 0; break; }
                }
                if (ok) {
                    for (int k = 0; k < l; ++k) cur[i][j + k] = 1;
                    tot += dfs(now + 1);
                    for (int k = 0; k < l; ++k) cur[i][j + k] = 0;
                }
            }
        }
    }
    return tot;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> mp[i];
    for (int i = 0; i < k; ++i) cin >> ship[i];
    sort(ship, ship + k);
    reverse(ship, ship + k);
    cout << dfs(0) << endl;
}
