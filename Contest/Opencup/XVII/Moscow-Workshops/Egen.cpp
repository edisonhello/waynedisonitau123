#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0) * clock());
    int n = rand() % 200000 + 1;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        cout << rand() % 10 + 1 << ' ';
    }
    cout << endl;
}
