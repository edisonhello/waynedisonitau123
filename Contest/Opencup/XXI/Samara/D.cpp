#include <bits/stdc++.h>
using namespace std;

double rec[5005][5005];
int vis[5005][5005];

double f(int n, int k) {
    if (k == 0) return 0;
    if (k == 1) return 1;
    if (k > n || k < 0) return 0;
    if (vis[n][k]) return rec[n][k];
    vis[n][k] = 1;
    return rec[n][k] = (double)(k - 2) * f(n - 2, k - 2) / (n - 1) + 
                       (double)(n - k) * f(n - 2, k - 1) / (n - 1);
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end(), greater<int>());

    double tot = 0;
    for (int i : a) tot += i;

    double ans = 0;

    for (int i = 0; i < n; ++i) {
        // cerr << "f i " << i << " " << f(n, i + 1) << endl;
        ans += f(n, i + 1) * a[i];
    }


    cout << fixed << setprecision(12) << ans << ' ' << tot - ans << endl;
}

