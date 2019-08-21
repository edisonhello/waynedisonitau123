#include <bits/stdc++.h>
using namespace std;
 
int p[2205];
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    while (n--) {
        int l, r; cin >> l >> r;
        for (int i = l; i <= r; ++i) p[i] = 1;
    }
    for (int i = 1; i <= 2200; ++i) p[i] += p[i - 1];
    for (int i = 1; i <= 2000; ++i) {
        if (p[i + 179] - p[i - 1] > 90) {
            cout << "No" << endl;
            exit(0);
        }
    }
    cout << "Yes" << endl;
}
