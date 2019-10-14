#include <bits/stdc++.h>
using namespace std;


int main() {
    long long n; cin >> n;
    set<long long> append;
    long long ans = 0;
    while (n != 1) {
        if (append.count(n)) break;
        append.insert(n);
        long long k = n >> 1;
        if (n & 1) {
            ans += 2 * k + 2;
            n = 3 * k + 2;
        } else {
            ans += 2 * k;
            n = k;
        }
    }
    if (n == 1) cout << ans << endl;
    else cout << -1 << endl;
}
