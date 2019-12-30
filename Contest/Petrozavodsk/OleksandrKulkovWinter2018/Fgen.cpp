#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0) * clock());
    int n = 100, m = rand() % 100 + (n - 1);
    cout << n << ' ' << m << endl;
    for (int i = 1; i < n; ++i) {
        cout << 1 << ' ' << i + 1 << ' ' << rand() % i + 1 << ' ' << rand() % 1000 + 1 << endl;
    }
    for (int i = n - 1; i < m; ++i) {
        cout << 0 << ' ' << rand() % n + 1 << ' ' << rand() % n + 1 << ' ' << rand() % 1000 + 1 << endl;
    }
}
