#include <bits/stdc++.h>
using namespace std;


int main() {
    int n, x; cin >> n >> x;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    sort(v.begin(), v.end());
    int last = v[0];
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        if (last + v[i] <= x) {
            ++cnt;
            last = v[i];
        } else break;
    }
    cout << cnt << endl;
}

