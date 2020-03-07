#include <bits/stdc++.h>
using namespace std;


int main() {
    srand(time(0) * clock());
    int n = 500, m = 500, a, b;
    do {
        a = rand() % 500 + 1;
        b = rand() % 500 + 1;
    } while ((n <= a && m <= b) || (n <= b && m <= a));
    cout << a << ' ' << b << ' ' << n << ' ' << m << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cout << rand() % 100 << ' ';
        cout << endl;
    }
}
