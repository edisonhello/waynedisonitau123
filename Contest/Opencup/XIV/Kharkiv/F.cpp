#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n; cin >> n;
    for (int i = 2; n; ++i) {
        if (n % i == 0) continue;
        cout << i - 1 << " " << n % i << '\n';
        n -= n % i;
    }
}
