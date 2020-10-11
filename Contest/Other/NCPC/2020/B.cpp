#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        pair<int, int> X{1e9, -1}, Y{1e9, -1};
        for (int s = 0; s < (1 << n); ++s) {
            int m = __builtin_popcount(s);
            int f = ((m % 10) + 1) * ((s + 1) % (m + 1) + 1);
            pair<int, int> P{f, s};
            if (f < X.first) {
                X = make_pair(f, s);
            } 
            if (f > Y.first) {
                Y = make_pair(f, s);
            }
        }

        for (int i = n - 1; i >= 0; --i) cout << (Y.second >> i & 1);
        cout << ": " << Y.first << "\n";
        for (int i = n - 1; i >= 0; --i) cout << (X.second >> i & 1);
        cout << ": " << X.first << "\n";
    }

}
