#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tt = 0;
    long double x; while (cin >> x) {
        ++tt; cout << "Case #" << tt << ": ";
        long double g = x * log10(2);
        cout << fixed << setprecision(0) << floor(g) << '\n';
    }
}
