

#include <bits/stdc++.h>
using namespace std;

int V(long long x) {
    int c = 0;
    while (x && x % 2 == 0) {
        x /= 2;
        ++c;
    }
    return c;
}

long long p[100005][2];

int main() {
#ifdef ONLINE_JUDGE
    freopen("semi-cool.in", "r", stdin);
    freopen("semi-cool.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i][0] >> p[i][1];
    long long A = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1 == n ? 0 : i + 1);
        A += p[i][0] * p[j][1] - p[i][1] * p[j][0];
    }
    A = abs(A);
    long long a = 0, c = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1 == n ? 0 : i + 1);
        long long dx = abs(p[i][0] - p[j][0]);
        long long dy = abs(p[i][1] - p[j][1]);
        a += __gcd(dx, dy);
        if (dx && dy && V(dx) == V(dy)) {
            c += __gcd(dx, dy);
        }
    }
    long long b = A + 2 - a;
    long long d = 2 * A + 2 - b - (a + c);
    // cerr << A << " " << a << " " << b << " " << c << " " << d << endl;
    cout << c + d / 2 << endl;
}
