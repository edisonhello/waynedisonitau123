#include <bits/stdc++.h>
using namespace std;

void meow(vector<int> &v) {
    int n = v.size();
    if (n == 2) {
        swap(v[0], v[1]);
        return;
    }
    vector<int> l, r;
    for (int i = 0; i < n / 2; ++i) l.push_back(v[i]);
    for (int i = n / 2; i < n; ++i) r.push_back(v[i]);
    meow(l);
    meow(r);
    for (int i = 0; i < n / 2; ++i) v[i] = r[i];
    for (int i = n / 2; i < n; ++i) v[i] = l[i - n / 2];
}

int main() {
    int n; cin >> n;
    n = 1 << n;
    int t; cin >> t;
    t &= 1;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    if (t) {
        meow(a);
    }

    for (int i : a) cout << i << ' ';
    cout << endl;
}

