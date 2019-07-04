#include <bits/stdc++.h>
using namespace std;
 
unsigned a[10000007];
unsigned A, B, C;
unsigned rng() {
    A = A ^ (A << 16);
    A = A ^ (A >> 5);
    A = A ^ (A << 1);
    unsigned t = A;
    A = B; B = C; C = (t ^ A) ^ B;
    return C;
}
 
unsigned ans[10000007];
 
void dfs(int l, int r, vector<int> &q) {
    if (q.empty()) return;
    int X = -1;
    int mid = (l + r) >> 1;
    auto it = lower_bound(q.begin(), q.end(), mid);
    if (it == q.end()) X = *prev(it);
    else if (it == q.begin()) X = *it;
    else {
        if (mid - *prev(it) < *it - mid) X = *prev(it);
        else X = *it;
    }
    nth_element(a + l, a + X, a + r + 1);
    ans[X] = a[X];
    vector<int> vl, vr;
    for (int i : q) {
        if (i < X) vl.push_back(i);
        else if (i > X) vr.push_back(i);
    }
    dfs(l, X - 1, vl);
    dfs(X + 1, r, vr);
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, t = 0; while (cin >> n >> m) {
        cout << "Case #" << (++t) << ": ";
        cin >> A >> B >> C;
        for (int i = 1; i <= n; ++i) a[i] = rng();
        // cerr << "a = "; for (int i = 1; i <= n; ++i) cerr << a[i] << " "; cerr << endl;
        vector<int> care;
        vector<int> qs;
        for (int i = 1; i <= m; ++i) {
            int x; cin >> x; ++x;
            care.push_back(x);
            qs.push_back(x);
        }
        sort(care.begin(), care.end());
        care.resize(unique(care.begin(), care.end()) - care.begin());
        dfs(1, n, care);
        for (int i : qs) cout << ans[i] << ' '; cout << '\n';
    }
}
