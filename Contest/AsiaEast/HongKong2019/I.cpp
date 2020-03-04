#include <bits/stdc++.h>
using namespace std;

const int kN = 200'000 + 5;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq[kN];
long long sum[kN];
int deg[kN];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    int last = 0, z = 0;
    for (int i = 0; i < m; ++i) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int y, k; scanf("%d%d", &y, &k);
            y ^= last;
            deg[z] = k;
            for (int i = 0; i < k; ++i) {
                int x; scanf("%d", &x);
                x ^= last;
                pq[x - 1].emplace(y, z);
            }
            z++;
        } else {
            int x, y; scanf("%d%d", &x, &y);
            x ^= last, y ^= last;
            x--;
            vector<int> ans;
            while (!pq[x].empty() && pq[x].top().first <= sum[x]) {
                if (--deg[pq[x].top().second] == 0) ans.push_back(pq[x].top().second);
                pq[x].pop();
            }
            printf("%d", (int)ans.size());
            for (int u : ans) printf(" %d", u + 1);
            puts("");
            last = ans.size();
        }
    }
}
