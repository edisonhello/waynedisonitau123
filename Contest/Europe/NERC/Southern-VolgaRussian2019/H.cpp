#include <bits/stdc++.h>
using namespace std;

int c[10];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        for (int i = 0; i <= 9; ++i) cin >> c[i];
        ++c[0];

        int mn = 1e6, id = -1;
        for (int i = 0; i <= 9; ++i) if (c[i] < mn) {
            mn = c[i];
            id = i;
        }
        
        if (id) {
            for (int i = 0; i <= c[id]; ++i) cout << id;
            cout << '\n';
        } else {
            cout << 1;
            for (int i = 0; i < c[id]; ++i) cout << 0;
            cout << '\n';
        }
    }
}
