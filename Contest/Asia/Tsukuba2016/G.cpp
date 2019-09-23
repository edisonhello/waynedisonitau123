#include <bits/stdc++.h>
using namespace std;

int bit[1000006];

void add(int x, int v) {
	++x;
	for (; x < 1000006; x += x & -x) bit[x] += v;
}

int query(int x) {
	++x;
	int a = 0;
	for (; x; x -= x & -x) a += bit[x];
	return a;
}

int query(int l, int r) {
	return query(r) - query(l - 1);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	auto put = [&] (int x) {
		// cout << "put " << x << endl;
		while (query(x, x)) {
			add(x, -1);
			--x;
		}
		add(x, 1);
		cout << "Yes\n";
	};
	int n; cin >> n; while (n--) {
		int x; cin >> x;
		if (x > 1000000) x = 1000000;
		// cout << "query(1, x) == " << query(x) << endl;
		if (query(0)) {
			cout << "No\n";
		} else if (query(1, x) == x) {
			if (query(x + 1, 1000000)) {
				cout << "No\n";
			} else put(x);
		} else put(x);
	}
}
