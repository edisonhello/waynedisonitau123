#include <bits/stdc++.h>
using namespace std;

bitset<1000060> np;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    vector<int> p;
    for (int i = 2; i < 1000000; ++i) {
        if (!np[i]) p.push_back(i);
        for (long long j = 1ll * i * i; j < 1000000; j += i) np[j] = 1;
    }
    vector<int> ans;
    for (int i = 11; i <= 1000000; ++i) {
        if (np[i]) continue;
        stringstream ss; ss << i;
        string s; ss >> s;
        reverse(s.begin(), s.end());
        stringstream sss; sss << s;
        int j; sss >> j;
        if (np[j]) continue;
        if (i == j) continue;
        ans.push_back(i);
    }
    int k; cin >> k;
    if (k >= ans.size()) cout << -1 << endl;
    else cout << ans[k - 1] << endl;
}
