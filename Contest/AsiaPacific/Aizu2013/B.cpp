#include <bits/stdc++.h>
using namespace std;

int tl[105], tr[105];
int ntl[105], ntr[105];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, l; while (cin >> n >> l) {
        if (n == 0 && l == 0) break;
        memset(tl, 0, sizeof(tl));
        memset(tr, 0, sizeof(tr));
        for (int i = 0; i < n; ++i) {
            char d; cin >> d;
            int p; cin >> p;
            if (d == 'L') tl[p] = i + 1;
            else tr[p] = i + 1;
        }
        int nt = 0;
        int last_exit = -1;
        auto ant_left = [&] () {
            for (int i = 0; i <= 100; ++i) if (tl[i] || tr[i]) return true;
            return false;
        };
        while (ant_left()) {
            ++nt;
            // cout << "nt = " << nt << endl;
            memset(ntl, 0, sizeof(ntl));
            memset(ntr, 0, sizeof(ntr));
            int lout = -1, rout = -1;
            for (int i = 1; i <= l - 1; ++i) {
                // cout << "i = " << i << endl;
                if (tl[i]) {
                    int me = tl[i];
                    // cout << "tl = " << me << endl;
                    if (i == 1) lout = me;
                    else {
                        if (i >= 3 && tr[i - 2]) ntr[i - 1] = me;
                        else ntl[i - 1] = me;
                    }
                }
                if (tr[i]) {
                    int me = tr[i];
                    // cout << "tr = " << me << endl;
                    if (i == l - 1) rout = me;
                    else {
                        if (i <= l - 3 && tl[i + 2]) ntl[i + 1] = me;
                        else ntr[i + 1] = me;
                    }
                }
            }
            if (rout != -1) last_exit = rout;
            if (lout != -1) last_exit = lout;
            for (int i = 0; i <= 100; ++i) tl[i] = ntl[i], tr[i] = ntr[i];
        }
        cout << nt << ' ' << last_exit << '\n';
    }
}
