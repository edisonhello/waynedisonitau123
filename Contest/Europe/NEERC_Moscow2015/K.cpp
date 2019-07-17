#include <bits/stdc++.h>
using namespace std;
 
vector<int> G[200005];
int ind[200005];
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
 
    while (m--) {
        int u, v; cin >> u >> v;
        G[v].push_back(u);
        ++ind[u];
    }
 
    priority_queue<int, vector<int>, less<int>> pq;
    for (int i = 1; i <= n; ++i) if (ind[i] == 0) pq.push(i);
 
    stack<int> ans;
    while (pq.size()) {
        int now = pq.top();
        ans.push(now);
        pq.pop();
        for (int i : G[now]) {
            --ind[i];
            if (ind[i] == 0) pq.push(i);
        }
    }
    
    while (ans.size()) {
        cout << ans.top() << " ";
        ans.pop();
    }
    cout << endl;
}
