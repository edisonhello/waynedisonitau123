#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n; while (n--) {
        long long n; cin >> n;
        long long ans = -1;
        for (long long i = 2; ; ++i) {
            if (n % i == 0) {
                break;
            } else {
                long long del = n / i;
                if (del == 0) {
                    ans = n;
                    break;
                }
                n -= del;
            }
        }
        cout << ans << endl;
    }
}
