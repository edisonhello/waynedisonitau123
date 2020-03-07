#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(clock() + time(0));
    int n = 10, m = 20, c = 10;
    cout << n << ' ' << m << ' ' << c << endl;
    for (int i = 0; i < m; ++i) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        int t = rand() % n + 1;
        while (x == y) {
            x = rand() % n + 1;
            y = rand() % n + 1;
        }
        cout << x << ' ' << y << ' ' << t << endl;
    }
    for (int i = 0; i < c; ++i) cout << rand() % n + 1 << ' ';
    cout << endl;
}
