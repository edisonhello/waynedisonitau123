#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    int q; cin >> q;
    int m; cin >> m;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < m; ++i) pq.push(0);
    int s, l; cin >> s >> l;
    while (l--) {
        pq.push(pq.top() + q);
        pq.pop();
    }
    while (s--) {
        pq.push(pq.top() + 1);
        pq.pop();
    }
    int mx = pq.top();
    while (pq.size()) {
        mx = max(mx, pq.top());
        pq.pop();
    }
    cout << mx << endl;
}
