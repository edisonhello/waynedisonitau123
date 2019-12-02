#include <bits/stdc++.h>
using namespace std;


int main() {
    srand(time(0) * clock());
    int n = 100; cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        int l = rand() % 1000, r = rand() % 1000;
        if (r < l) swap(l, r);
        if (l == r) ++r;
        int t = rand() % (r - l) + 1;
        cout << l << ' ' << r << ' ' << t << endl;
    }
}
