#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    auto meow = [&] () {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        vector<int> lis;
        for (int i : a) {
            if (lis.empty() || i > lis.back()) lis.push_back(i);
            else *lower_bound(lis.begin(), lis.end(), i) = i;
        }
        return lis.size();
    };
    cout << meow() + meow() << endl;
}

