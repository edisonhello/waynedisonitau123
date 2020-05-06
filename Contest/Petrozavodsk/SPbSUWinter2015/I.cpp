#include <bits/stdc++.h>
using namespace std;

bitset<12000> a[6001];
bool did[6001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;

    for (int i = 0; i <= n; ++i) {
        string s; cin >> s;
        int j = 0;
        for (char c : s) {
            c -= 33;
            for (int z = 0; z < 6; ++z) {
                a[i][j] = !!(c & (1 << z));
                ++j;
            }
        }

        // for (int j = 0; j < 2 * n; ++j) cerr << a[i][j];
        // cerr << endl;
    }

    vector<int> v(n + 1);
    iota(v.begin(), v.end(), 0);
    random_shuffle(v.begin(), v.end());
    int it = 0;

    while (true) {
        while (did[v[it]]) ++it;
        int i = v[it];
        did[i] = 1;

        int mxi = 0, mx = -1;
        for (int j = 0; j <= n; ++j) if (i != j && !did[j]) {
            bitset<12000> z = a[i] ^ a[j];
            int cc = z.count();
            int zero = 2 * n - cc;
            if (zero >= n) {
                cout << i + 1 << ' ' << j + 1 << endl;
                exit(0);
            }
            if (cc > mx) {
                mx = cc;
                mxi = j;
            }
        }

        i = mxi;
        did[i] = 1;
        for (int j = 0; j <= n; ++j) if (i != j && !did[j]) {
            bitset<12000> z = a[i] ^ a[j];
            int cc = z.count();
            int zero = 2 * n - cc;
            if (zero >= n) {
                cout << i + 1 << ' ' << j + 1 << endl;
                exit(0);
            }
        }
    }
}

