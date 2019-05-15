#include <bits/stdc++.h>
using namespace std;

long long meow(int n, set<int> &pl, set<int> &mi) {
    long long rt = 0;
    {
        vector<int> vpl, vmi;
        for (int i : pl) if (i > n) {
            vpl.push_back(i - n);
            if (i - n == 1);
            else vpl.push_back(i - n);
        }
        for (int i : mi) if (i <= 0) {
            vmi.push_back(i + n);
            if (i + n == n);
            else vmi.push_back(i + n);
        }
        sort(vpl.begin(), vpl.end());
        for (int i : vmi) {
            rt += upper_bound(vpl.begin(), vpl.end(), i) - vpl.begin();
        }
    } 
    // cerr << "up , rt = " << rt << endl;
    {
        vector<int> vpl, vmi;
        for (int i : pl) if (i > n) {
            vpl.push_back(i - n);
            if (i - n == 1);
            else vpl.push_back(i - n);
        }
        for (int i : mi) if (i >= 0) {
            vmi.push_back(n - i);
            if (n - i == n);
            else vmi.push_back(n - i);
        }
        sort(vpl.begin(), vpl.end());
        for (int i : vmi) {
            rt += upper_bound(vpl.begin(), vpl.end(), i) - vpl.begin();
        }
    }
    // cerr << "right , rt = " << rt << endl;
    {
        vector<int> vpl, vmi;
        for (int i : pl) if (i <= n + 1) {
            vpl.push_back(i - 1);
            if (i - 1 == n);
            else vpl.push_back(i - 1);
        }
        for (int i : mi) if (i >= 0) {
            vmi.push_back(i + 1);
            if (i + 1 == 1);
            else vmi.push_back(i + 1);
        }
        sort(vmi.begin(), vmi.end());
        for (int i : vpl) {
            rt += upper_bound(vmi.begin(), vmi.end(), i) - vmi.begin();
        }
    }
    // cerr << "down , rt = " << rt << endl;
    {
        vector<int> vpl, vmi;
        for (int i : pl) if (i <= n + 1) {
            vpl.push_back(i - 1);
            if (i - 1 == n);
            else vpl.push_back(i - 1);
        }
        for (int i : mi) if (i <= 0) {
            vmi.push_back(1 - i);
            if (1 - i == 1);
            else vmi.push_back(1 - i);
        }
        sort(vmi.begin(), vmi.end());
        for (int i : vpl) {
            rt += upper_bound(vmi.begin(), vmi.end(), i) - vmi.begin();
        }
    }
    // cerr << "left , rt = " << rt << endl;
    return rt / 4;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    set<int> pl, mi;
    while (m--) {
        int a, b; cin >> a >> b;
        pl.insert(a + b);
        mi.insert(a - b);
    }
    long long ans = 0;
    for (int i : pl) {
        if (i == n + 1) ans += n;
        else if (i < n + 1) ans += i - 1;
        else ans += n * 2 + 1 - i;
    }
    for (int i : mi) {
        ans += n - abs(i);
    }
    // cerr << "after add, ans = " << ans << endl;
    for (int i = 0; i < 2; ++i) {
        set<int> zpl, zmi;
        for (int j : pl) if ((j & 1) == i) zpl.insert(j);
        for (int j : mi) if ((j & 1) == i) zmi.insert(j);
        ans -= meow(n, zpl, zmi);
        // cerr << "after " << i << " , = " << ans << endl;
    }
    // cerr << "after repeat count = " << ans << endl;
    cout << 1ll * n * n - ans << endl;
}
