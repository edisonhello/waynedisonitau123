#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        int n; cin >> n;
        cout << "Case #" << tc << ": ";
        if (n & 1) {
            if (n >= 7) cout << "Panda" << endl;
            else cout << "Draw" << endl;
        } else {
            if (n >= 16) cout << "Sheep" << endl;
            else cout << "Draw" << endl;
        }
    }
}
