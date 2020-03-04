#include <bits/stdc++.h>
using namespace std;

const int maxn = 300005;

int a[maxn], b[maxn], apos[maxn], bpos[maxn];
int outa[maxn], outb[maxn];

int main() {
    int n;
    long long k; 
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) apos[a[i]] = i;
    for (int i = 1; i <= n; ++i) bpos[b[i]] = i;
    for (int i = 1; i <= n; ++i) outa[a[i]] = -n + i - 1;
    for (int i = 1; i <= n; ++i) outb[b[i]] = -n + i - 1;
    long long nowk = 1ll * n * (n - 1) / 2;
    int it = n;
    while (nowk > k) {
        int ii = b[it];
        // cerr << "ii = " << ii << endl;
        if (nowk - (ii - 1) == k) {
            outb[ii] = n;
            nowk -= ii - 1;
            break;
        } else if (nowk - (ii - 1) > k) {
            outb[ii] = n;
            nowk -= ii - 1;
        } else {
            vector<int> frset;
            for (int i = 1; i < ii; ++i) frset.push_back(outa[i]);
            sort(frset.begin(), frset.end());
            reverse(frset.begin(), frset.end());
            int sub = nowk - k;
            outb[ii] = -frset[sub - 1];
            nowk -= sub;
            break;
        }
        --it;
    }
    if (nowk == k) {
        cout << "Yes" << endl;
        for (int i = 1; i <= n; ++i) cout << outa[i] << ' '; cout << endl;
        for (int i = 1; i <= n; ++i) cout << outb[i] << ' '; cout << endl;
        exit(0);
    }

}

