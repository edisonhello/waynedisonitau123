#include <bits/stdc++.h>
using namespace std;

int xs[5005];
long long xsum[5005];
int ys[5005];
long long ysum[5005];
int lef[5005], rig[5005];
bitset<5005> tot[5005];

int main() {
    freopen("jenga.in", "r", stdin);
    freopen("jenga.out", "w", stdout);

    int n, w, h, m; cin >> n >> w >> h >> m;
    lef[1] = 1;
    rig[1] = n;
    for (int i = 2; i <= h; ++i) {
        xs[i] = xs[i - 1] + n;
        ys[i] = ys[i - 1] + n;
        xsum[i] = xsum[i - 1] + n * n;
        ysum[i] = ysum[i - 1] + n * n;


        lef[i] = 1;
        rig[i] = n;
        for (int j = 1; j <= n; ++j) {
            tot[i][j] = 1;
        }
    }

    for (int im = 1; im <= m; ++im) {
        // cerr << "im = " << im << endl;
        auto Fall = [&] () {
            cout << "yes" << endl;
            cout << im << endl;
            exit(0);
        };

        int l, k; cin >> l >> k;

        l = h + 1 - l;
        tot[l][k] = 0;
        // if (tot[l].count() == 0u) {
        //     Fall();
        // }

        while (lef[l] <= n && !tot[l][lef[l]]) ++lef[l];
        while (rig[l] >= 1 && !tot[l][rig[l]]) {
            --rig[l];
        }

        for (int i = l + 1; i <= h; ++i) {
            --xs[i];
            --ys[i];
            xsum[i] -= (l & 1 ? n : k * 2 - 1);
            ysum[i] -= (l & 1 ? k * 2 - 1 : n);
        }

        for (int i = l; i <= h; ++i) {
            long long u = (i & 1 ? ysum : xsum)[i];
            long long d = (i & 1 ? ys : xs)[i];
            // cerr << "layer " << i << " sum = " << u << " size = " << d << endl;
            if (u == 0) continue;

            if (u <= (lef[i] * 2 - 2) * d) {
                Fall();
            } else if (u >= (rig[i] * 2 + 0) * d) {
                Fall();
            }
        }
    }

    cout << "no" << endl;
}

