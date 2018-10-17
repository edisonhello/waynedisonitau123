#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int l[maxn], r[maxn], s[maxn], c[maxn], st[20][maxn];
int sl[maxn], sr[maxn];
// vector<int> st[maxn], ed[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &l[i], &r[i]);
        ++s[l[i]], --s[r[i]];
    }
    for (int i = 1; i < maxn; ++i) s[i] += s[i - 1];
    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < maxn; ++i) ans1 = max(ans1, s[i]);
    memset(s, 0, sizeof(s));
    for (int i = 0; i < n; ++i) {
        ++sl[l[i]];
        ++sr[r[i] - 1];
    }
    for (int i = 1; i < maxn; ++i) sr[i] += sr[i - 1];
    for (int i = maxn - 1; i >= 0; --i) sl[i] += sl[i + 1];
    for (int i = 0; i < n; ++i) {
        int q = n - sr[l[i] - 1] - sl[r[i]]; 
        ans2 = max(ans2, q);
    }
    printf("%d %d\n", ans2, ans1);
    return 0;
}
