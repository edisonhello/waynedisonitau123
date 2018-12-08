#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int sum[maxn], p[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; getline(cin, s);
    stringstream ss(s);
    vector<int> v;
    while (ss >> s) v.push_back((int)s.size());
    int a, b; cin >> a >> b;
    int len = 0, c = 0;
    /* for (int i = 0; i < (int)v.size(); ) {
        int j = i;
        while (j < (int)v.size() && sum[c] + v[j] + p[c] <= a) {
            sum[c] += v[j];
            p[c]++;
            st[c].push_back(v[j]);
            j++;
        }
        len += (int)v[i].size();
        ++c;
        i = j;
    } */
    sum[0] = v[0];
    for (int i = 1; i < (int)v.size(); ++i) sum[i] = sum[i - 1] + v[i];
    for (int i = a; i <= b; ++i) {
        int j = 0;
        int len = 0, c = 0;
        while (j < (int)v.size()) {
            int k = j;
            for (int d = 20; d >= 0; --d) {
                if (k + (1 << d) < (int)v.size()) {
                    int s = sum[k + (1 << d)] - (j ? sum[j - 1] : 0);
                    if (s + k + (1 << d) - j <= i) k += (1 << d);
                }
            }
            len += v[j];
            ++c;
            j = k + 1;
        }
        printf("%d\n", len + c - 1);
    }
    return 0;
}
