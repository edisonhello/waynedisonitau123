#include <bits/stdc++.h>
using namespace std;

int bnd[22];

int main() {
    for (int i = 10; i >= 0; --i) {
        bnd[i] = 20 * (11 - i) * 20 * (11 - i);
    }
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        int pt = 0;
        while (n--) {
            int x, y; cin >> x >> y;
            int dd = x * x + y * y;
            for (int i = 10; i >= 1; --i) {
                if (bnd[i] >= dd) {
                    pt += i;
                    break;
                }
            }
        }

        cout << pt << endl;
    }
}

