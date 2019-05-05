#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        string mp[3]; 
        for (int i = 0; i < 3; ++i) cin >> mp[i];
        while (n--) {
            string op; cin >> op;
            bool u = 0;
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    if (i * 2 + j + 1 == op[0] - '0' && !u) {
                        if (op[1] == 'C') {
                            tie(mp[i][j], mp[i + 1][j], mp[i + 1][j + 1], mp[i][j + 1]) = 
                                make_tuple(mp[i + 1][j], mp[i + 1][j + 1], mp[i][j + 1], mp[i][j]);
                        } else {
                            tie(mp[i][j], mp[i + 1][j], mp[i + 1][j + 1], mp[i][j + 1]) = 
                                make_tuple(mp[i + 1][j], mp[i + 1][j + 1], mp[i][j + 1], mp[i][j]);
                            tie(mp[i][j], mp[i + 1][j], mp[i + 1][j + 1], mp[i][j + 1]) = 
                                make_tuple(mp[i + 1][j], mp[i + 1][j + 1], mp[i][j + 1], mp[i][j]);
                            tie(mp[i][j], mp[i + 1][j], mp[i + 1][j + 1], mp[i][j + 1]) = 
                                make_tuple(mp[i + 1][j], mp[i + 1][j + 1], mp[i][j + 1], mp[i][j]);
                        }
                        u = 1;
                    }
                }
            }
        }
        for (int i = 0; i < 3; ++i) cout << mp[i] << '\n';
    }
}
