#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        if (n == 1) cout << "1\n";
        else if (n == 2) cout << "2 2\n";
        else if (n == 3) cout << "1 2 3\n";
        else {
            for (int i = 1; i <= n - 2; ++i) cout << "1 ";
            cout << "2 " << n << '\n';
        }
    }
}
