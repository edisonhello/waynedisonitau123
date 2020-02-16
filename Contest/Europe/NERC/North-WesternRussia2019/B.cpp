#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int pos[50000007];

int main() {
    int n; cin >> n;
    vector<double> lis;
    int i;
    for (i = 6; (int)lis.size() < n; i += 10) {
        double z = sin((double)i);
        // if (lis.empty() || z > lis.back()) {
        //     lis.push_back(z);
        //     pos[i] = lis.size();
        // } else {
        //     auto it = lower_bound(lis.begin(), lis.end(), z);
        //     *it = z;
        //     pos[i] = it - lis.begin() + 1;
        // }
        if (lis.empty() || z < lis.back()) {
            lis.push_back(z);
            pos[i] = lis.size();
        } else {
            auto it = lower_bound(lis.begin(), lis.end(), z, greater<double>());
            *it = z;
            pos[i] = it - lis.begin() + 1;
        }
    }

    // cerr << "i = " << i << endl;
    int pick = n;
    for (; i >= 1; i -= 10) {
        if (pos[i] == pick) {
            cout << i << '\n';
            --pick;
        }
    }

}

