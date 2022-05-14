#include <bits/stdc++.h>
using namespace std;

int mx[105];
int app[105];

int main() {
	int t; cin >> t; while (t--) {
		memset(app, 0, sizeof(app));
		memset(mx, 0, sizeof(mx));
		int n; 
		cin >> n;
		for (int i = 0; i < n; ++i) {
			int b, t;
			cin >> b >> t;
			app[t] = 1;
			mx[t] = max(mx[t], b);
		}

		int out = 0;
		int sum = 0;
		for (int i = 1; i <= 10; ++i) {
			if (!app[i]) {
				cout << "MOREPROBLEMS" << endl;
				out = 1;
break;
			}
			sum += mx[i];
		}

		if (!out) {
			cout << sum << endl;
		}
	} }

