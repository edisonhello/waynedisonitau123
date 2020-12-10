#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        int c0, c1, c2, c3;
        cin >> c0 >> c1 >> c2 >> c3;
        if (c0 == 0 && c1 == 0 && c2 == 0 && c3 == 0) {
            cout << "Horse\n";
        } else if (c1 == 0 && c2 == 0 && c3 == 0) {
            if (c0 & 1) cout << "Horse\n";
            else cout << "Rabbit\n";
        } else if (c0 % 2 == 0) {
            if (c1 % 3 == 0) {
                cout << "Horse\n";
            } else if (c1 % 3 == 1) {
                if (c2 == 0) cout << "Horse\n";
                else cout << "Rabbit\n";
            } else {
                cout << "Rabbit\n";
            }
        } else {
            if (c1 % 3 == 0) {
                cout << "Rabbit\n";
            } else if (c1 % 3 == 1) {
                if (c2 == 0) cout << "Rabbit\n";
                else cout << "Horse\n";
            } else {
                if (c2 <= 1) cout << "Horse\n";
                else cout << "Rabbit\n";
            }
        }
    }
}

