#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<int> p1{1, 2, 3, 3, 4, 10}, p2{1, 2, 2, 2, 3, 5, 11};

int32_t main() {
    int t; cin >> t; 
    for (int T = 1; T <= t; ++T) {
        cout << "Battle " << T << ": ";
        vector<int> c1(p1.size());
        vector<int> c2(p2.size());

        for (int &i : c1) cin >> i;
        for (int &i : c2) cin >> i;

        long long a = 0, b = 0;
        for (int i = 0; i < (int)p1.size(); ++i) {
            a += p1[i] * c1[i];
        }
        for (int i = 0; i < (int)p2.size(); ++i) {
            b += p2[i] * c2[i];
        }

        if (a > b) {

            cout << "Good triumphs over Evil" << '\n';
        } else if (a < b) {
            cout << "Evil eradicates all trace of Good" << '\n';
        } else {
            cout << "No victor on this battle field" << '\n';
        }
    }
}
