#include <bits/stdc++.h>
using namespace std;
#define int long long

int meow(const vector<int> &v, const vector<int> &u) {
    int a = 0, b = 0;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if (u[i] > v[i]) a = max(a, u[i] - v[i]);
        else if (u[i] < v[i]) b = max(b, v[i] - u[i]);
    }
    return a + b;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, d; cin >> n >> d;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<int> u(n), uu(n);
    u[0] = v[0];
    for (int i = 1; i < n; ++i) u[i] = u[i - 1] + d;
    uu[0] = v[0];
    for (int i = 1; i < n; ++i) uu[i] = uu[i - 1] - d;

    int ans = min(meow(v, u), meow(v, uu));

    cout << ans / 2 << "." << (ans & 1 ? "5" : "0") << endl;
}

