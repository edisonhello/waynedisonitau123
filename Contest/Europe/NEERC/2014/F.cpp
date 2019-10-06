#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1000 + 5;
int a[maxn];
char s[maxn];
bitset<maxn> filter[maxn];
bitset<maxn> b[maxn];
 
int hex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'a' + 10;
}
 
int main() {
#ifdef ONLINE_JUDGE
    freopen("filter.in", "r", stdin);
    freopen("filter.out", "w", stdout);
#endif
 
    int m, f; scanf("%d%d", &m, &f);
    for (int i = 0; i < f; ++i) scanf("%d", &a[i]);
 
    int n; scanf("%d", &n);
    int l = (m + 3) >> 2;
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        assert(strlen(s) == l);
        for (int j = 0, p = 0; j < l; ++j) {
            int d = hex(s[j]);
            for (int k = 0; k < 4 && p < m; ++k, ++p) {
                if (d & 1) filter[i].set(p);
                d >>= 1;
            }
        }
    }
 
    int q; scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int u; scanf("%d", &u);
        for (int j = 0; j < f; ++j) {
            int d = u * 1ll * a[j] % m;
            b[i].set(d);
        }
    }
 
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < q; ++j) {
            if ((filter[i] & b[j]) == b[j]) {
                ans.push_back(i);
                break;
            }
        }
    }
 
    printf("%d ", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) printf("%d ", ans[i]);
}
