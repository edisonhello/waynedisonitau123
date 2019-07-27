#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 5;
long long len[maxn];
int dd[maxn];

int main() {
    string s;
    int p = 0, prv = 0;
    for (int i = 1; p < maxn; ) {
        int sum = 0;
        vector<int> d;
        while (d.empty() || d.size() & 1) {
            int x = i++;
            vector<int> w;
            while (x > 0) w.push_back(x % 10), x /= 10;
            while (!w.empty()) d.push_back(w.back()), w.pop_back();
        }
        for (int j = 0; j < (int)d.size(); j += 2) {
            int a = d[j], b = d[j + 1];
            sum += a;
            while (a-- && p < maxn) dd[p++] = b;
        }
        len[i - 1] = len[prv] + sum;
        prv = i - 1;
    }
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        if (len[n] < m) puts("-1");
        else printf("%d\n", dd[m - 1]);
    }
}
