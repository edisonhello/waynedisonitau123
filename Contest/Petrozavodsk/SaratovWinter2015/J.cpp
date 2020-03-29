#include <bits/stdc++.h>
using namespace std;

int c[200005];

int main() {
    int n, m; cin >> n >> m;
    vector<int> ex(n);
    vector<int> us(m);
    for (int i = 0; i < n; ++i) cin >> ex[i];
    for (int i = 0; i < m; ++i) cin >> us[i];
    sort(ex.begin(), ex.end(), greater<int>());
    sort(us.begin(), us.end(), greater<int>());

    auto ok = [&] (int M) -> bool {
        // cerr << "M = " << M << endl;

        memset(c, 0, sizeof(c));
        for (int i = 0; i < M; ++i) ++c[us[i]];

        long long emt = 1;
        long long nxe = 0;
        int ly = 0;
        int exit = 0;

        while (ly <= 200000) {
            // cerr << "ly = " << ly << " c[ly] " << c[ly] << " exit " << exit << " emt " << emt << endl;

            if (c[ly] > emt) return false;
            emt -= c[ly];

            while (emt && exit < n) {
                nxe += ex[exit];
                ++exit;
                --emt;
            }

            emt += nxe;
            nxe = 0;
            ++ly;
        }

        return true;
    };

    int L = 0, R = m;
    while (L < R) {
        int M = (L + R + 1) / 2;
        if (ok(M)) L = M;
        else R = M - 1;
    }

    cout << L << endl;
}

