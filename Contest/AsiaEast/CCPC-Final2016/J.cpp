#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; 
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int g; cin >> g;
        int ans = -1;
        string is; cin >> is;

        array<array<string, 20>, 6> v;
        for (int i = 0; i < 6; ++i) for (int j = 0; j < 20; ++j) cin >> v[i][j];

        for (int y = 0; y <= g; ++y) {
            int x = g - y;
            
            set<string> took;
            for (int j = 0; j < 20; ++j) {
                for (int i = 0; i < 5; ++i) {
                    if (took.size() == x) break;
                    took.insert(v[i][j]);
                }
            }

            // cerr << "first: ";
            // for (string s : took) cerr << s << ' ';
            // cerr << endl;

            for (int j = 0; j < 20; ++j) {
                if (took.size() == g) break;
                took.insert(v.back()[j]);
            }

            if (!took.count(is)) {
                ans = y;
                break;
            }
        }

        if (ans == -1) {
            cout << "ADVANCED!" << '\n';
        } else {
            cout << ans << '\n';
        }
    }
}

