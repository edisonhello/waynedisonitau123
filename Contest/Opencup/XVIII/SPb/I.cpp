#include <bits/stdc++.h>
using namespace std;


int main() {
    int n; cin >> n;

    vector<int> v(n);
    iota(v.begin(), v.end(), 1);

    sort(v.begin(), v.end(), [&] (const int a, const int b) {
        cout << "? " << a << ' ' << b << endl;
        fflush(stdout);
        int t; cin >> t;
        return t;
    });

    vector<int> yes, no;
    for (int i = 0; i < n - 1; ++i) {
        cout << "? " << v[i] << ' ' << v.back() << endl;
        fflush(stdout);
        int t; cin >> t;
        if (t) yes.push_back(v[i]);
        else no.push_back(v[i]);
    }

    // cerr << "large = " << v.back() << endl;
    // cerr << "yes: = "; for (int i : yes) cerr << i << ' '; cerr << endl;
    // cerr << "no: = "; for (int i : no) cerr << i << ' '; cerr << endl;

    if (no.empty()) {
        cout << "! " << "YES" << endl;
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << v[i];
        }
        cout << endl;
        exit(0);
    }

    assert(yes.size() && no.size());
    sort(yes.begin(), yes.end(), [&] (const int a, const int b) {
        cout << "? " << a << ' ' << b << endl;
        fflush(stdout);
        int t; cin >> t;
        return t;
    });
    sort(no.begin(), no.end(), [&] (const int a, const int b) {
        cout << "? " << a << ' ' << b << endl;
        fflush(stdout);
        int t; cin >> t;
        return t;
    });

    cout << "! " << "NO" << endl;
    // cout << "3 " << v.back() << ' ' << yes.back() << ' ' << no[0] << endl;
    cout << "3 " << yes[0] << ' ' << v.back() << ' ' << no.back() << endl;
}

