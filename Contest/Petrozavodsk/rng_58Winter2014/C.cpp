#include <bits/stdc++.h>
using namespace std;


int main() {
    int n; cin >> n;
    vector<int> v(n);

    for (int &i : v) cin >> i;
    long long tot = 0;
    for (int i : v) tot += i;

    long long mn = tot;
    auto Dfs = [&] (auto self, int now, vector<int> &cho) {
        if (now == (1 << n)) {
            long long t = tot;
            for (int i : cho) t -= __builtin_popcount(i) - 1;
            mn = min(t, mn);
            // cerr << "cho: ";
            // for (int i : cho) cerr << i << ' ';
            // cerr << "t = " << t << endl;
            return;
        }
        self(self, now + 1, cho);

        if (__builtin_popcount(now) > 1) {

            bool ok = 1;
            for (int z : cho) if (__builtin_popcount(z & now) > 1) ok = 0;

            for (int i = 0; i < n; ++i) if (now & (1 << i)) if (v[i] == 0) ok = 0;

            if (ok) {
                cho.push_back(now);
                for (int i = 0; i < n; ++i) if (now & (1 << i)) --v[i];
                self(self, now + 1, cho);
                for (int i = 0; i < n; ++i) if (now & (1 << i)) ++v[i];
                cho.pop_back();
            }
        }
    };

    vector<int> o;
    Dfs(Dfs, 0, o);

    cout << mn << endl;
}

