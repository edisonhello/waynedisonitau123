#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
long long l[maxn];
int d[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%lld%d", &l[i], &d[i]);
    priority_queue<pair<int, int>> pq;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = i;
    sort(v.begin(), v.end(), [&](int i, int j) {
        if (l[i] + d[i] == l[j] + d[j]) return d[i] < d[j];
        return l[i] + d[i] < l[j] + d[j];
    });
    long long sum = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = v[i];
        if (sum <= l[j]) {
            pq.emplace(d[j], j);
            sum += d[j];
        } else if ((int)pq.size() > 0 && sum > l[j] && (int)pq.top().first > d[j] && sum - pq.top().first <= l[j]) {
            sum -= pq.top().first;
            pq.pop();
            pq.emplace(d[j], j);
            sum += d[j];
        }
        ans = max(ans, (int)pq.size());
    }
    printf("%d\n", ans);
    return 0;
}
