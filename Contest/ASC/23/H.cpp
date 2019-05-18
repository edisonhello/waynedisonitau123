#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int sa[maxn], tmp[2][maxn], c[maxn], hi[maxn], r[maxn];
int ans[maxn];

void build(const string &s) {
    int *rnk = tmp[0], *rkn = tmp[1];
    for (int i = 0; i < 256; ++i) c[i] = 0;
    for (int i = 0; i < s.size(); ++i) c[rnk[i] = s[i]]++;
    for (int i = 1; i < 256; ++i) c[i] += c[i - 1];
    for (int i = s.size() - 1; i >= 0; --i) sa[--c[s[i]]] = i;
    int sigma = 256;
    for (int n = 1; n < s.size(); n *= 2) {
        for (int i = 0; i < sigma; ++i) c[i] = 0;
        for (int i = 0; i < s.size(); ++i) c[rnk[i]]++;
        for (int i = 1; i < sigma; ++i) c[i] += c[i - 1];
        int *sa2 = rkn;
        int r = 0;
        for (int i = s.size() - n; i < s.size(); ++i) sa2[r++] = i;
        for (int i = 0; i < s.size(); ++i) {
            if (sa[i] >= n) sa2[r++] = sa[i] - n;
        }
        for (int i = s.size() - 1; i >= 0; --i) sa[--c[rnk[sa2[i]]]] = sa2[i];
        rkn[sa[0]] = r = 0;
        for (int i = 1; i < s.size(); ++i) {
            if (!(rnk[sa[i - 1]] == rnk[sa[i]] && sa[i - 1] + n < s.size() && rnk[sa[i - 1] + n] == rnk[sa[i] + n])) r++;
            rkn[sa[i]] = r;
        }
        swap(rnk, rkn);
        if (r == s.size() - 1) break;
        sigma = r + 1;
    }
    for (int i = 0; i < s.size(); ++i) r[sa[i]] = i;
    int ind = 0; hi[0] = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (!r[i]) { ind = 0; continue; }
        while (i + ind < s.size() && s[i + ind] == s[sa[r[i] - 1] + ind]) ++ind;
        hi[r[i]] = ind ? ind-- : 0;
    }
}

int main() {
#ifndef LOCAL
    freopen("seti.in", "r", stdin);
    freopen("seti.out", "w", stdout);
#endif
    string s; cin >> s;
    build(s);
    /* for (int i = 0; i < s.size(); ++i) cout << hi[i] << ' ';
    cout << endl;
    for (int i = 0; i < s.size(); ++i) cout << sa[i] << ' ';
    cout << endl; */
    long long res = 0;
    for (int i = 0; i < s.size() - 1; ++i) {
        int lcp = hi[i + 1];
        for (int j = i + 1; j < s.size(); ++j) {
            ans[i] = max(ans[i], min(lcp, abs(sa[i] - sa[j])));
            if (j + 1 < s.size()) lcp = min(lcp, hi[j + 1]);
        }
        int k = 0;
        if (i) {
            lcp = hi[i];
            for (int j = i - 1; j >= 0; --j) {
                int x = min({ lcp, ans[i], ans[j] });
                // int x = min({ min(lcp, abs(sa[i] - sa[j])), ans[i], ans[j] });
                k = max(k, x);
            }
        }
        res += ans[i] - k;
        // cout << "ans[" << i << "] = " << ans[i] << endl;
        // cout << "k = " << k << endl;
    }
    // for (int i = 0; i < s.size(); ++i) res += ans[i];
    cout << res << endl;
    return 0;
}
