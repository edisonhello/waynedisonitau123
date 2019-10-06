#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
int ga[maxn], gb[maxn], ma[1 << maxn], mb[1 << maxn];
int va[maxn], vb[maxn];
long long sa[1 << maxn], sb[1 << maxn];
bool ca[1 << maxn], cb[1 << maxn];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        static char s[maxn + 1];
        scanf("%s", s);
        for (int j = 0; j < m; ++j) {
            if (s[j] == '1') {
                ga[i] |= 1 << j;
                gb[j] |= 1 << i;
            }
        }
    }
    for (int s = 0; s < (1 << n); ++s) {
        for (int i = 0; i < n; ++i) {
            if (s >> i & 1)
                ma[s] |= ga[i];
        }
    }
    for (int s = 0; s < (1 << m); ++s) {
        for (int i = 0; i < m; ++i) {
            if (s >> i & 1)
                mb[s] |= gb[i];
        }
    }
    for (int i = 0; i < n; ++i) scanf("%d", &va[i]);
    for (int i = 0; i < m; ++i) scanf("%d", &vb[i]);
    for (int s = 0; s < (1 << n); ++s) {
        for (int i = 0; i < n; ++i) {
            if (s >> i & 1)
                sa[s] += va[i];
        }
    }
    for (int s = 0; s < (1 << m); ++s) {
        for (int i = 0; i < m; ++i) {
            if (s >> i & 1)
                sb[s] += vb[i];
        }
    }
    ca[0] = true;
    for (int i = 1; i < (1 << n); ++i) {
        ca[i] = __builtin_popcount(ma[i]) >= __builtin_popcount(i);
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1)
                ca[i] &= ca[i ^ (1 << j)];
        }
    }
    cb[0] = true;
    for (int i = 1; i < (1 << m); ++i) {
        cb[i] = __builtin_popcount(mb[i]) >= __builtin_popcount(i);
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1)
                cb[i] &= cb[i ^ (1 << j)];
        }
    }
    long long v; scanf("%lld", &v);
    vector<long long> pa, pb;
    for (int i = 0; i < (1 << n); ++i)
        if (ca[i]) pa.push_back(sa[i]);
    for (int i = 0; i < (1 << m); ++i)
        if (cb[i]) pb.push_back(sb[i]);
    sort(pa.begin(), pa.end());
    sort(pb.begin(), pb.end());
    long long ans = 0;
    int j = (int)pb.size() - 1;
    int seen = 0;
    for (int i = 0; i < (int)pa.size(); ++i) {
        while (j >= 0 && pa[i] + pb[j] >= v) ++seen, --j;
        ans += seen;
    }
    printf("%lld\n", ans);
    return 0;
}
