#include <bits/stdc++.h>
using namespace std;

int a[250005];
int b[250005];

int bit[250005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int t; cin >> t;
        if (n & 1) {
            if (t == n / 2 + 1) a[i] = 0;
            else if (t >= n / 2 + 1) a[i] = 1;
            else a[i] = -1;
        } else {
            if (t > n / 2) a[i] = 1;
            else a[i] = -1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        int t; cin >> t;
        if (n & 1) {
            if (t == n / 2 + 1) b[i] = 0;
            else if (t >= n / 2 + 1) b[i] = 1;
            else b[i] = -1;
        } else {
            if (t > n / 2) b[i] = 1;
            else b[i] = -1;
        }
    }

    auto Calc = [&] () {
        memset(bit, 0, sizeof(bit));

        set<int> hi, lo;
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 1) hi.insert(i);
            else lo.insert(i);
        }

        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (b[i] == 1) {
                int pos = *lo.begin();
                ans += pos - 1;
                
                for (int x = pos; x; x -= x & -x) ans -= bit[x];
                for (int x = pos; x < 250005; x += x & -x) ++bit[x];

                lo.erase(pos);
            } else {
                int pos = *hi.begin();
                ans += pos - 1;
                
                for (int x = pos; x; x -= x & -x) ans -= bit[x];
                for (int x = pos; x < 250005; x += x & -x) ++bit[x];

                hi.erase(pos);
            }
        }

        return ans;
    };
    
    if (n & 1) {
        int pa = -1, pb = -1;
        for (int i = 1; i <= n; ++i) if (a[i] == 0) pa = i;
        for (int i = 1; i <= n; ++i) if (b[i] == 0) pb = i;
        a[pa] = 1, b[pb] = -1;
        long long a1 = Calc();
        a[pa] = -1, b[pb] = 1;
        long long a2 = Calc();
        cout << min(a1, a2) << endl;
    } else {
        cout << Calc() << endl;
    }
}

