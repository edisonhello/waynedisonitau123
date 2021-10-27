#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    int n, m; cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> eat(n);
    for (int i = 0; i < m; ++i) {
        int t; cin >> t;
        ++eat[t - 1];
    }

    vector<int> as = a;
    sort(as.begin(), as.end());
    as.resize(unique(as.begin(), as.end()) - as.begin());

    vector<int> ias(100005);
    for (int i = 0; i < (int)as.size(); ++i) ias[as[i]] = i;

    vector<set<pair<int, int>>> asg(as.size());
    for (int i = 0; i < n; ++i) {
        int pos = ias[a[i]];
        asg[pos].insert(make_pair(eat[i], i));
    }

    int suma = 0;
    for (int i = 0; i < n; ++i) suma += a[i];
    assert(suma <= 100000);

    auto good = [&] (int n, int a, int s) {
        return 1ll * n * a - suma < 1ll * s * suma;
    };

    // toteat = m + extra;
    int extra = 0;
    while (extra < suma * 2) {
        int this_eat_at = -1;
        int this_eat = -1;
        ll this_eat_todie = 1e18;
        for (int i = 0; i < (int)asg.size(); ++i) {
            int mini = asg[i].begin()->second;
            int minieat = eat[mini];
            // cerr << "i mini minieat = " << i << ' ' << mini << ' ' << minieat << endl;
            ll d = 1ll * eat[mini] * suma - (1ll * (m + extra) * a[mini] - suma);
            d = (d - 1) / a[mini];
            if (d < this_eat_todie) {
                this_eat = mini;
                this_eat_todie = d;
                this_eat_at = i;
            }
        }

        int ok = 1;
        for (int i = 0; i < (int)asg.size(); ++i) {
            int mini = asg[i].begin()->second;
            int minieat = eat[mini];

            if (mini == this_eat) {
                if (!good(m + extra + 1, a[mini], eat[mini] + 1)) ok = 0;
                if (asg[i].size() > 1u) {
                    int mini2 = next(asg[i].begin())->second;
                    if (!good(m + extra + 1, a[mini2], eat[mini2])) ok = 0;
                }
            } else {
                if (!good(m + extra + 1, a[mini], eat[mini])) ok = 0;
            }
        }

        if (!ok) break;
        ++eat[this_eat];
        ++extra;
        asg[this_eat_at].erase(asg[this_eat_at].begin());
        asg[this_eat_at].insert(make_pair(eat[this_eat], this_eat));
        // cerr << "eat " << this_eat << endl;
    }

    if (extra >= suma * 2) {
        cout << "forever" << endl;
    } else {
        cout << extra << endl;
    }
}

