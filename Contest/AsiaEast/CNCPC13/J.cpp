#include <bits/stdc++.h> 
using namespace std;

int main() {
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];

        for (int x = 3 * v[0]; ; ++x) {
            if (x & 1) continue;
            bool good = 1;
            for (int i = 0; i < n; ++i) {
                if (x <= v[i]) good = 0;
            }
            if (good) {
                cout << x << '\n';
                break;
            }
        }
    }
}

