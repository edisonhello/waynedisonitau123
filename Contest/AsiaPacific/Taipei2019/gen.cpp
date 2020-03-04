#include <bits/stdc++.h>
using namespace std;


int main() {
    srand(time(0) * clock());
    int n = rand() % 10 + 5; cout << n << endl;
    for (int i = 1; i < n; ++i) {
        cout << i + 1 << ' ' << rand() % i + 1 << '\n';
    }
}
