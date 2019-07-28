#include <bits/stdc++.h>
using namespace std;

queue<pair<long long, long long>> q[100005];

int main() {
    freopen("cards.in", "r", stdin);
    freopen("cards.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    long long score = 0;
    for (int y = 1; y <= n; ++y) {
        vector<long long> t;
        int z; cin >> z; t.resize(z);
        for (long long &i : t) cin >> i;
        for (int i = 0, j; i < z; i = j) {
            j = i;
            long long need = 0, now = 0;
            while (j < z) {
                for (; j < z && t[j] <= 0; ++j) now += t[j], need = min(need, now);
                for (; j < z && t[j] >= 0; ++j) now += t[j];
                if (j == z) break;
                if (now > 0) break;
            }
            if (now <= 0) break;
            q[y].emplace(need, now);
        }
    }
    auto cmp = [&] (const int &a, const int &b) -> bool {
        if (q[a].empty()) return 1;
        if (q[b].empty()) return 0;
        return q[a].front().first < q[b].front().first;
    };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    for (int i = 1; i <= n; ++i) {
        pq.push(i);
    }
    while (pq.size()) {
        int now = pq.top(); pq.pop();
        if (q[now].empty()) continue;
        if (score + q[now].front().first < 0) break;
        score += q[now].front().second;
        q[now].pop();
        pq.push(now);
    }
    cout << score << endl;
}
