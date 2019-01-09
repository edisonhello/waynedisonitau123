#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int ans[maxn];

long long calc(int x, int n) {
    if (n - x - 1 > 62) return 9e18;
    if (x == n) return 1;
    return 1ll << (n - x - 1);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
#endif
    int n; long long k;
    while (scanf("%d%lld", &n, &k) != EOF) {
        if (n == 0 && k == 0) break;
        queue<int> que;
        int cur = 1;
        set<int> st;
        for (int i = 1; i <= n; ++i) st.insert(i);
        for (int i = 1; i <= n; ++i) {
            if (que.size()) {
                ans[i] = que.front();
                st.erase(que.front());
                que.pop();
                continue;
            }
            int now = cur;
            long long sum = calc(now, n);
            while (sum < k) sum += calc(now + 1, n), ++now;
            for (int i = cur; i < now; ++i) k -= calc(i, n);
            ans[i] = now;
            st.erase(now);
            cur = now + 1;
            while (st.size() && *st.begin() <= now) {
                que.push(*st.begin());
                st.erase(st.begin());
            }
        }
        for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
        puts("");
    }
}
