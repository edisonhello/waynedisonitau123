#include <bits/stdc++.h>
using namespace std;

string mp[505];

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> mp[i];

    for (int j = 0; j < m; ++j) if (mp[0][j] == '.') mp[0][j] = 'w';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) if (mp[i][j] == 'w') {
            if (mp[i + 1][j] == '#' && j < m - 1 && mp[i][j + 1] == '.') mp[i][j + 1] = 'w';
        }
        for (int j = m - 1; j >= 0; --j) if (mp[i][j] == 'w') {
            if (mp[i + 1][j] == '#' && j > 0 && mp[i][j - 1] == '.') mp[i][j - 1] = 'w';
        }
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 'w' && mp[i + 1][j] == '.') {
                mp[i + 1][j] = 'w';
            }
        }
    }

    // for (int i = 0; i < n; ++i) cout << mp[i] << endl;
    [&] () {
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (mp[i][j] == '.') {
            mp[i][j] = 'X';
            return;
        }
        cout << "No" << endl;
        exit(0);
    } ();
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (mp[i][j] == 'w') mp[i][j] = '.';
    
    cout << "Yes" << endl;
    for (int i = 0; i < n; ++i) cout << mp[i] << '\n';
}

