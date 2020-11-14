#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<bool> ok((1 << 15) + 1);
    for (int a = 1; a <= (1 << 15); ++a) {
        for (int b = a; a * b <= (1 << 15); ++b) {
            if (b <= 2 * a) {
                ok[a * b] = true;
            }
        }
    }
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        cout << ok[x] << "\n";
    }
}
