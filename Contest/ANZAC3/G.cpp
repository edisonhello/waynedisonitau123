#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    deque<int> v;
    while (m--) {
        int t; cin >> t;
        v.push_back(t);
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (v.size() && v.front() < i) v.pop_front();
        if (v.empty()) break;
        int ok = n - i + 1;
        ok -= v.front() - i;
        ans += ok;
    }
    cout << ans << endl;
}
