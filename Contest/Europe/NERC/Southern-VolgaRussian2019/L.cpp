#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int a, b, c; cin >> a >> b >> c;
        cout << max(max(min(a, c), (a + b + c) / 3 + !!((a + b + c) % 3)), max((a + 1) / 2, (c + 1) / 2)) << '\n';
    }
}
