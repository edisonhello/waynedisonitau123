#include <bits/stdc++.h>
using namespace std;
int main() {
    srand(time(0) * clock());
    int t = 1; cout << t << endl; while (t--) {
        int n = 500000, m = 1000000;
        cout << n << ' ' << m << endl;
        for (int i = 0; i < 500000; ++i) cout << "0 " << rand() % n + 1 << ' ' << rand() % 1000000000 + 1 << '\n';
        for (int i = 0; i < 500000; ++i) {
            int l = rand() % n + 1, r = rand() % n + 1;
            if (r < l) swap(l, r);
            cout << "1 " << l << ' ' << r << ' ' << rand() % 1000000000 + 1 << '\n';
        }
    }
}
