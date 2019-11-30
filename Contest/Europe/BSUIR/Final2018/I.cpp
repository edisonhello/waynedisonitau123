#include <bits/stdc++.h>
using namespace std;

map<long long, pair<long long, long long>> rec;
set<long long> isend;
long long solve(long long n) {
    if (n < 10) return n;
    auto it = rec.find(n);
    if (it != rec.end()) {
        return it->second.first;
    }
    if (isend.count(n)) return n;
    long long mn = LLONG_MAX, zto = -1;
    for (long long base = 10; base <= n; base *= 10) {
        long long r = n % base;
        long long l = n / base;
        if (l == r) continue;
        // if (l == 0 || r == 0) continue;
        long long fin = solve(abs(l - r));
        if (fin < mn) {
            mn = fin;
            zto = abs(l - r);
        }
    }
    // cerr << "solve " << n << " mn " << mn << " to " << zto << endl;
    if (zto == -1) {
        isend.insert(n);
        return n;
    }
    rec[n] = make_pair(mn, zto);
    return mn;
}

int main() {
    int n; cin >> n;
    while (n--) {
        long long x; cin >> x;
        solve(x);
        vector<long long> p = {x};
        while (x > 9 && !isend.count(x)) {
            x = rec[x].second;
            p.push_back(x);
        }

        cout << p.size();
        for (long long &i : p) cout << ' ' << i;
        cout << '\n';
    }
}
