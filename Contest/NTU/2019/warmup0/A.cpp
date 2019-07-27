#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        long long suma = 0, x = 0;
        while (n--) {
            long long a, b; cin >> a >> b;
            suma += a;
            if (suma % 2) x ^= b;
        }
        if (x) cout << "A-Mi-Ba" << '\n';
        else cout << "B-Mi-Ba" << '\n';
    }
}
