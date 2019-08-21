#include <bits/stdc++.h>
using namespace std;

int l[100005], A[100005], B[100005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int a, b, n; cin >> a >> b >> n;
        for (int i = 1; i <= a; ++i) cin >> l[i];
        for (int i = 2; i <= a; ++i) l[i] += l[i - 1];
        for (int i = 1, at = 1; i <= a; ++i) {
            for (int bb = 1; at <= l[i] && at <= 100000; ++at, ++bb) A[at] = i, B[at] = bb;
            if (at > 100000) break;
        }
        while (n--) {
            if (A[a] == a && B[a] == b) break;
            tie(a, b) = make_pair(A[a], B[a]);
        }
        cout << a << "-" << b << endl;
    }
}
