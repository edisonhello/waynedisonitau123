#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int x[maxn], y[maxn], z[maxn];
int a[maxn], b[maxn], c[maxn];
int pa[maxn], pb[maxn], pc[maxn];
int fw[maxn];

void add(int p, int v) {
	for (int i = p + 1; i < maxn; i += i & -i)
		fw[i] += v;
}

int query(int p) {
	int res = 0;
	for (int i = p + 1; i > 0; i -= i & -i)
		res += fw[i];
	return res;
}

long long dvcq(int l, int r, const vector<int> &p) {
	if (r - l == 1) return 0;
	if (p.empty()) return 0;
	int m = (l + r) >> 1;
	long long res = 0;
	for (int i = 0; i < (int)p.size(); ++i) {
		if (y[p[i]] >= m)
			res += query(z[p[i]]);
		else
			add(z[p[i]], 1);
	}
	for (int i = 0; i < (int)p.size(); ++i) {
		if (y[p[i]] < m)
			add(z[p[i]], -1);
	}
	
	vector<int> lp, rp;
	for (int i = 0; i < (int)p.size(); ++i) {
		if (y[p[i]] >= m) 
			rp.push_back(p[i]);
		else 
			lp.push_back(p[i]);
	}
	res += dvcq(l, m, lp) + dvcq(m, r, rp);
	return res;
}

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
	for (int i = 1; i <= n; ++i) pa[a[i]] = i;
	for (int i = 1; i <= n; ++i) pb[b[i]] = i;
	for (int i = 1; i <= n; ++i) pc[c[i]] = i;
	for (int i = 0; i < n; ++i) x[i] = pa[i + 1] - 1;
	for (int i = 0; i < n; ++i) y[i] = pb[i + 1] - 1;
	for (int i = 0; i < n; ++i) z[i] = pc[i + 1] - 1;

	vector<int> p;
	for (int i = 0; i < n; ++i) p.push_back(i);
	sort(p.begin(), p.end(), [&](int i, int j) {
		return x[i] < x[j];
	});

	printf("%lld\n", dvcq(0, n, p));
}
