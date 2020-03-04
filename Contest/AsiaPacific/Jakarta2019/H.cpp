#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
int l[kN], w[kN];

int main() {
    int n; scanf("%d", &n);
    long long ans = 0;
    vector<int> s;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &l[i], &w[i]);
        if (l[i] > w[i]) swap(l[i], w[i]);
        ans = max(ans, 1LL * l[i] * w[i]);
        s.push_back(l[i]);
        s.push_back(w[i]);
    }
   
    sort(s.begin(), s.end());
    s.resize(unique(s.begin(), s.end()) - s.begin());

    vector<int> od(n);
    iota(od.begin(), od.end(), 0);
    sort(od.begin(), od.end(), [&](int i, int j) { return l[i] > l[j]; });

    multiset<int> ms;
    for (int i = s.size() - 1, j = 0; i >= 0; --i) {
        while (j < n && l[od[j]] >= s[i]) ms.insert(w[od[j++]]);
        if (ms.size() >= 2) ans = max(ans, 2LL * s[i] * *prev(prev(ms.end())));
    }
    printf("%lld", ans / 2);
    if (ans & 1) printf(".5\n");
    else printf(".0\n");
}
