#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ":" << endl;
        cout << "YES" << endl;

        int n; cin >> n;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                cout << i << ' ' << j << ' '
                    << 1 << ' ' << j << ' ' << i << ' '
                    << 0 << ' ' << j << ' ' << i << '\n';
            }
        }
        
    }
}

