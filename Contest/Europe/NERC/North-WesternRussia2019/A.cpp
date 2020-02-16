#include <bits/stdc++.h>
using namespace std;


int main() {
    int a, b, n; cin >> a >> b >> n;
    int al = 0, ar = b, bl = 0, br = a;
    int ans = 0;
    while (ar != n || br != n) {
        if (ar != n && al != bl) {
            int d = min(n - ar, bl - al);
            al += d, ar += d;
            ++ans;
        } else {
            int d = ar - br;
            bl += d, br += d;
            ++ans;
        }
    }
    cout << ans << endl;
}

