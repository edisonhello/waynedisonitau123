#include <bits/stdc++.h>
using namespace std;

int a[1005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    set<int> aru;
    for (int l = 1; l <= 6; ++l) {
        for (int i = 1; i <= n; ++i) {
            int x = 0;
            for (int j = 0; j < l; ++j) {
                if (i + j > n) break;
                x = x * 10 + a[i + j];
            }
            aru.insert(x);
        }
    }
    for (int i = 0; ; ++i) {
        if (aru.count(i) == 0) {
            cout << i << '\n';
            exit(0);
        }
    }
}

