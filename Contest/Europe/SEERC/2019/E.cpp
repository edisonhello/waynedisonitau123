#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    int lc, pc, lm, pm; cin >> lc >> pc >> lm >> pm;
    int t, d; cin >> t >> d;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a.begin() + 1, a.end());

    vector<long long> provide_sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) provide_sum[i] = min(a[i] - 1, d);
    for (int i = 2; i <= n; ++i) provide_sum[i] += provide_sum[i - 1];

    vector<long long> need_mort(n + 1, 0);
    for (int i = 1; i <= n; ++i) need_mort[i] = max(0, lm - a[i]);
    for (int i = 2; i <= n; ++i) need_mort[i] += need_mort[i - 1];
    vector<long long> provide_mort(n + 1, 0);
    for (int i = 1; i <= n; ++i) provide_mort[i] = min(max(0, a[i] - lm), d);
    for (int i = 2; i <= n; ++i) provide_mort[i] += provide_mort[i - 1];
    
    vector<long long> need_car(n + 1, 0);
    for (int i = 1; i <= n; ++i) need_car[i] = max(0, lc - a[i]);
    for (int i = 2; i <= n; ++i) need_car[i] += need_car[i - 1];
    vector<long long> provide_car(n + 1, 0);
    for (int i = 1; i <= n; ++i) provide_car[i] = min(max(0, a[i] - lc), d);
    for (int i = 2; i <= n; ++i) provide_car[i] += provide_car[i - 1];

    long long mn = LLONG_MAX;
    for (int driver = 0; driver <= n; ++driver) {
        int passe = min(1ll * driver * (k - 1), 1ll * (n - driver));

        int mortl = passe + 1, mortr = n - driver;
        // cerr << "driver = " << driver << endl;
        if (mortl <= mortr) {
            if (a[mortl] + d < lm) continue;
        }
        // cerr << "driver = " << driver << endl;
        if (driver) {
            if (a[n - driver + 1] + d < lc) continue;
        }

        long long need = need_mort[mortr] - need_mort[mortl - 1];
        need += need_car[n] - need_car[n - driver];
        long long give = provide_sum[passe];
        give += provide_mort[mortr] - provide_mort[mortl - 1];
        give += provide_car[n] - provide_car[n - driver];

        // cerr << "driver = " << driver << endl;
        if (give < need) continue;
        mn = min(mn, 1ll * need * t + 1ll * pc * driver + 1ll * pm * (mortr - mortl + 1));
        // cerr << "driver = " << driver << endl;
        // cerr << "mn = " << mn << endl;
    }

    if (mn == LLONG_MAX) cout << -1 << endl;
    else cout << mn << endl;
}

