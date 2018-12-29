#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
long long a[maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
        vector<long long> v = {a[0] - 1, a[0], a[0] + 1};
        for (int i = 1; i < n; ++i) {
            vector<long long> x;
            for (int j = 0; j < (int)v.size(); ++j) {
                x.push_back(__gcd(v[j], a[i] - 1));
                x.push_back(__gcd(v[j], a[i] - 0));
                x.push_back(__gcd(v[j], a[i] + 1));
            }
            sort(x.begin(), x.end());
            x.resize(unique(x.begin(), x.end()) - x.begin());
            v = x;
        }
        printf("%lld\n", *max_element(v.begin(), v.end()));
    }
}
