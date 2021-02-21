#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int x = n / 3, y = n - x;
    cout << 1LL * x * y + 1LL * x * (x - 1) / 2 << endl;
}

