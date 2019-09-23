#include <bits/stdc++.h>
using namespace std;

bool put[200005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> op;
    for (int i = n; i >= 1; --i) op.push_back(i);
    while (m--) {
        int x; cin >> x;
        op.push_back(x);
    }
    reverse(op.begin(), op.end());
    vector<int> ans;
    for (int i : op) {
        if (put[i]) continue;
        ans.push_back(i);
        put[i] = 1;
    }
    for (int i : ans) cout << i << '\n';
}
