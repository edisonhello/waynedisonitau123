#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    priority_queue<int, vector<int>, greater<int>> pq;
    int sum = 0;
    for (int i = 1; i <= k; ++i) {
        int t; cin >> t;
        pq.push(t);
        sum += t;
    }

    cout << sum << ' ';
    for (int i = k + 1; i <= n; ++i) {
        int t; cin >> t;
        pq.push(t);
        sum += t;
        t = pq.top();
        pq.pop();
        sum -= t;
        cout << sum << ' ';
    }
    cout << endl;
}

