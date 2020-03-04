#include <bits/stdc++.h>
using namespace std;

const int kN = 1000 + 5;
int a[kN];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]), pq.push(a[i]);
        long long ans = 0;
        while (pq.size() > 1) {
            long long x = pq.top(); pq.pop();
            long long y = pq.top(); pq.pop();
            ans += x + y;
            pq.push(x + y);
        }
        printf("%lld\n", ans);
    }
}
