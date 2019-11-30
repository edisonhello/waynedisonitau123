#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        for (int c = 1; c <= 50; ++c) {
            if (c != a + b) {
                cout << c << endl;
                break;
            }
        }
    }
}
