#include <bits/stdc++.h>
using namespace std;


int main() {
    srand(time(0) * clock());
    int n = 300, m = 40, k = 6;
    cout << n << " " << m << " " << k << endl;
    for (int i = 1; i <= n; ++i) {
        cout << rand() % 10000 << " " << rand() % 10000 << '\n';
    }
    for (int i = 1; i <= n; ++i) cout << rand() % 6 + 1 << " "; cout << endl;
    for (int i = 1; i <= m; ++i) {
        cout << rand() % 10000 << " " << rand() % 10000 << '\n';
    }
}
