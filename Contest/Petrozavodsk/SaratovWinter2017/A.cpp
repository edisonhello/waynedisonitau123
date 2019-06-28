#include <bits/stdc++.h>
using namespace std;

int a[500005], b[500005], c[500005];
pair<int, int> btoc[500005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int d, na, nb, nc; while (cin >> d >> na >> nb >> nc) {
        for (int i = 1; i <= na; ++i) cin >> a[i];
        for (int i = 1; i <= nb; ++i) cin >> b[i];
        for (int i = 1; i <= nc; ++i) cin >> c[i];
        int aL = 1, aR = 0;
        int bL = 1, bR = 0;
        int cL = 1, cR = 0;
        long long ans = 0;
        for (int i = 1; i <= na; ++i) {
            while (bR < nb && b[bR + 1] < a[i]) ++bR;
            while (bL <= bR && a[i] - b[bL] > d) ++bL;
            while (cR < nc && c[cR + 1] < a[i]) ++cR;
            while (cL <= cR && a[i] - c[cL] > d) ++cL;
            ans += 1ll * (bR - bL + 1) * (cR - cL + 1);
        }
        aL = 1, aR = 0;
        bL = 1, bR = 0;
        cL = 1, cR = 0;
        for (int i = 1; i <= nb; ++i) {
            while (aR < na && a[aR + 1] <= b[i]) ++aR;
            while (aL <= aR && b[i] - a[aL] > d) ++aL;
            while (cR < nc && c[cR + 1] < b[i]) ++cR;
            while (cL <= cR && b[i] - c[cL] > d) ++cL;
            ans += 1ll * (aR - aL + 1) * (cR - cL + 1);
        }
        aL = 1, aR = 0;
        bL = 1, bR = 0;
        cL = 1, cR = 0;
        for (int i = 1; i <= nc; ++i) {
            while (aR < na && a[aR + 1] <= c[i]) ++aR;
            while (aL <= aR && c[i] - a[aL] > d) ++aL;
            while (bR < nb && b[bR + 1] <= c[i]) ++bR;
            while (bL <= bR && c[i] - b[bL] > d) ++bL;
            ans += 1ll * (aR - aL + 1) * (bR - bL + 1);
        }
        cout << ans << endl;
    }
}
