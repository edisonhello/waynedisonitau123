#include <bits/stdc++.h>
using namespace std;

int bit[100005];

void add(int x) {
    for (; x < 100005; x += x & -x) ++bit[x];
}

int query(int x) {
    int y = 0;
    for (; x; x -= x & -x) y += bit[x];
    return y;
}

int query(int l, int r) {
    return query(r) - query(l - 1);
}

int a[100005];
vector<int> pos[100005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    long long ans = 0;
    for (int i = 100000; i >= 1; --i) {
        for (int j : pos[i]) {
            ans += min(query(1, j - 1), query(j + 1, n));
        }
        for (int j : pos[i]) add(j);
    }
    cout << ans << endl;
}
