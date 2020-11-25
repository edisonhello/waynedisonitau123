#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int x;
        cin >> x;
        if (x == 1) cout << 2 << "\n";
        else if (x == 2) cout << "16\n";
        else if (x == 3) cout << "32\n";
        else cout << "4\n";
    }
}

