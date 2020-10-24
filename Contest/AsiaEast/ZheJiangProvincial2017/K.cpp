#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        
        bool found = 0;
        for (int i = 0; i < n; ++i) {
            if (3 * a[i] < b[i]) {
                cout << i + 1 << '\n';
                found = 1;
                break;

            }
        }
        if (!found) cout << -1 << '\n';
    }
}

