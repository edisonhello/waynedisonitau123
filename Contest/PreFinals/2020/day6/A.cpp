#include <bits/stdc++.h>
using namespace std;

int a[1005];

int main() {
    int n; cin >> n;
    a[0] = a[1] = 1;

    for (int i = 2; i <= 1000; ++i) {
        set<int> no;
        for (int k = 1; i - k - k >= 0; ++k) no.insert(2 * a[i - k] - a[i - k - k]);
        int z = 1;
        for (; no.count(z); ++z);
        a[i] = z;
    }

    // for (int i = 0; i <= 100; ++i) cout << a[i] << ' ';
    // cout << endl;

    cout << a[n] << endl;
}

