#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t; while (t--) {
        long long n; cin >> n;
        long long L = 1, R = 8;
        while (true) {
            if (L <= n && n <= R) {
                cout << "YES" << endl;
                break;
            }
            L = R + 1;
            R = L * 2 - 1;
            if (L <= n && n <= R) {
                cout << "NO" << endl;
                break;
            }
            L = R + 1;
            R = L * 9 - 1;
        }
    }
}
