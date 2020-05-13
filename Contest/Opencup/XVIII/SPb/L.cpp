#include <bits/stdc++.h>
using namespace std;


int main() {
    int n; cin >> n;
    map<long long, int> cnt;
    long long xx = 0;
    int m = n;
    while (n--) {
        long long t; cin >> t;
        xx ^= t;
        cnt[t]++;
    }
    if (xx) {
        cout << 0 << endl;
        exit(0);
    }
    cout << (1LL << m) - 2 << endl;
}

