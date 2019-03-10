#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 87;
const int pr = 7902131;

string s; 

int hh[100005], ihh[100005], pp[100005];
int nxq[100005], pvq[100005];

int main() {
#ifdef ONLINE_JUDGE
    freopen("palindromes.in", "r", stdin);
    freopen("palindromes.out", "w", stdout);
#endif
    cin >> s;
    int n = int(s.size());
    s = " " + s + " ";

    pvq[0] = 0; nxq[n + 1] = n + 1;
    for (int i = 1; i <= n; ++i) pvq[i] = (s[i - 1] == '?' ? i - 1 : pvq[i - 1]);
    for (int i = n; i >= 1; --i) nxq[i] = (s[i + 1] == '?' ? i + 1 : nxq[i + 1]);

    pp[0] = 1;
    for (int i = 1; i <= n + 2; ++i) pp[i] = pp[i - 1] * 7902131ll % mod;
    for (int i = 1; i <= n; ++i) hh[i] = (hh[i - 1] * 1ll * pr + s[i]) % mod;
    for (int i = n; i >= 1; --i) ihh[i] = (ihh[i + 1] * 1ll * pr + s[i]) % mod;

    auto hash = [&] (const int L, const int R) -> int {
        if (L > R) return 0;
        return (hh[R] + mod - hh[L - 1] * 1ll * pp[R - L + 1] % mod) % mod;
    };
    auto ihash = [&] (const int L, const int R) -> int {
        if (L > R) return 0;
        return (ihh[L] + mod - ihh[R + 1] * 1ll * pp[R - L + 1] % mod) % mod;
    };

    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        int L = i, R = i;
        double ch = 1;
        double add = 0;
        add += ch;
        // cerr << "at mid = " << i << endl;
        while (L >= 1 && R <= n && ch > 1e-12) {
            int pv = pvq[L], nx = nxq[R];
            // cerr << "<- " << pv << " -> " << nx << endl;
            int pvl = L - pv, nxl = nx - R;
            int jd = min(pvl, nxl);
            int nL = L - jd, nR = R + jd;
            // cerr << "cur LR: " << L << " " << R << " , jd = " << jd << endl;
            // cerr << "new LR: " << nL << " " << nR << endl;
            // cerr << "now ch: " << ch << endl;
            if (ihash(nL + 1, L - 1) == hash(R + 1, nR - 1)) {
                add -= ch * (R - L + 1);
                L = nL, R = nR;
                if (L == 0 || R == n + 1) {
                    ++L; --R;
                    // cerr << "last LR: " << L << " " << R << endl;
                    add += ch * (R - L + 1);
                    break;
                } else {
                    add += ch * (R - L - 1);
                    ch /= 26;
                    add += ch * 2;
                }
            } else {
                int bl = 0, br = jd - 1;
                while (bl < br) {
                    int bjd = (bl + br + 1) >> 1;
                    int nL = L - bjd, nR = R + bjd;
                    if (ihash(nL, L - 1) == hash(R + 1, nR)) bl = bjd;
                    else br = bjd - 1;
                }
                // cout << "last jd: " << jd << endl;
                jd = bl;
                add -= ch * (R - L + 1);
                L = L - jd, R = R + jd;
                add += ch * (R - L + 1);
                break;
            }
        }
        // cerr << "at i = " << i << " add " << add << endl;
        ans += add;
    }
    ans /= n;
    cout << fixed << setprecision(20) << ans << endl;
}
