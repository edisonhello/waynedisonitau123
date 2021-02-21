#include <bits/stdc++.h>
using namespace std;


int main() {
    long long n; cin >> n;
    vector<long long> a;
    for (int i = 1; i <= 10000000; ) {
        a.push_back(i); ++i;
        a.push_back(i); ++i;
        a.push_back(i); ++i;
        ++i;
        a.push_back(i); ++i;
        ++i;
    }

    vector<long long> b;
    b.push_back(1);
    long long mxlen = ceil(sqrt(n) * 2 / 3);
    for (int i = 1; i < (int)a.size(); ++i) {
        b.push_back(a[i - 1] * a[i]);
        if (b.back() > n) b.pop_back();
    }

    assert(b.size() >= mxlen);

    cout << b.size() << endl;
    for (long long i : b) cout << i << ' ';
    cout << endl;

}

