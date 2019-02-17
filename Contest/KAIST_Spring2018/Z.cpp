#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    int ans = 2;
    for (int i = 0; i < n; ++i) {
        vector<int> v;
        for (int j = i; j < n; ++j) {
            if (v.size() < 2) v.push_back(a[j]);
            else if (v[v.size() - 2] >= v[v.size() - 1] && v[v.size() - 1] >= a[j]) break;
            else if (v[v.size() - 2] <= v[v.size() - 1] && v[v.size() - 1] <= a[j]) break;
            else v.push_back(a[j]);
        }
        ans = max(ans, (int)v.size());
    }
    printf("%d\n", ans);
}
