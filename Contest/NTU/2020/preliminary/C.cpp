#include <bits/stdc++.h>
using namespace std;

struct sfxarray {
	static const int maxn = 1000000 + 6;
	bool t[maxn * 2];
	int hi[maxn], rev[maxn];
	int _s[maxn * 2], sa[maxn * 2], c[maxn * 2], x[maxn], p[maxn], q[maxn * 2];
	void pre(int *sa, int *c, int n, int z) {
		memset(sa, 0, sizeof(int) * n);
		memcpy(x, c, sizeof(int) * z);
	}
	void induce(int *sa, int *c, int *s, bool *t, int n, int z) {
		memcpy(x + 1, c, sizeof(int) * (z - 1));
		for (int i = 0; i < n; ++i) if (sa[i] && !t[sa[i] - 1]) sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
		memcpy(x, c, sizeof(int) * z);
		for (int i = n - 1; i >= 0; --i) if (sa[i] && t[sa[i] - 1]) sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
	}

	void sais(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z) {
		bool uniq = t[n - 1] = true;
		int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, last = -1;
		memset(c, 0, sizeof(int) * z);
		for (int i = 0; i < n; ++i) uniq &= ++c[s[i]] < 2;
		for (int i = 0; i < z - 1; ++i) c[i + 1] += c[i];
		if (uniq) {
			for (int i = 0; i < n; ++i) sa[--c[s[i]]] = i;
			return;
		}
		for (int i = n - 2; i >= 0; --i) t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
		pre(sa, c, n, z);
		for (int i = 1; i <= n - 1; ++i) if (t[i] && !t[i - 1]) sa[--x[s[i]]] = p[q[i] = nn++] = i;
		induce(sa, c, s, t, n, z);
		for (int i = 0; i < n; ++i) if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
			bool neq = last < 0 || memcmp(s + sa[i], s + last, (p[q[sa[i]] + 1] - sa[i]) * sizeof(int));
			ns[q[last = sa[i]]] = nmxz += neq;
		}
		sais(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
		pre(sa, c, n, z);
		for (int i = nn - 1; i >= 0; --i) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
		induce(sa, c, s, t, n, z);
	}
	
	void build(const vector<int> &v) {
		for (int i = 0; i < (int)v.size(); ++i) _s[i] = v[i];
		_s[(int)v.size()] = 0;
		sais(_s, sa, p, q, t, c, (int)v.size() + 1, v.size());
		for (int i = 0; i < (int)v.size(); ++i) sa[i] = sa[i + 1];
		for (int i = 0; i < (int)v.size(); ++i) rev[sa[i]] = i;
	}
} sa;

void solve() {
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) cin >> v[i];

	if (n == 1) {
		cout << v[0] << '\n';
		return;
	}

	vector<int> num = v;
	sort(num.begin(), num.end());
	num.resize(unique(num.begin(), num.end()) - num.begin());
	for (int &i : v) {
		i = upper_bound(num.begin(), num.end(), i) - num.begin();
	}
	reverse(v.begin(), v.end());
	for (int i = 0; i < n; ++i) v.push_back(v[i]);

	// cerr << "v: ";
	// for (int i : v) cerr << i << ' ';
	// cerr << endl;
	// cerr << "num: ";
	// for (int i : num) cerr << i << ' ';
	// cerr << endl;

	sa.build(v);

	// reverse(v.begin(), v.end());
	for (int i = 0; i < n * 2; ++i) if (sa.sa[i] > 0 && sa.sa[i] < n) {
		// cerr << "i sa.sa[i] " << i << ' ' << sa.sa[i] << endl;
		int st = sa.sa[i];
		for (int j = 0; j < n; ++j) {
			// cerr << "st + j " << st + j << endl;
			// cerr << "v[st + j] " << v[st + j] << endl;
			// cerr << "num[] " << num[v[st + j] - 1] << endl;
			cout << num[v[st + j] - 1] << ' ';
		}
		cout << '\n';
		return;
	}
	assert(0);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; while (t--) solve();
}
