#include <bits/stdc++.h>
using namespace std;

int a[55][55];

int main() {
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> a[i][j];

	int mx = 0;
	for (int u1 = 0; u1 < n; ++u1) for (int d1 = u1; d1 < n; ++d1) for (int l1 = 0; l1 < m; ++l1) for (int r1 = 0; r1 < m; ++r1) {
		for (int u2 = 0; u2 < n; ++u2) for (int d2 = u2; d2 < n; ++d2) for (int l2 = 0; l2 < m; ++l2) for (int r2 = 0; r2 < m; ++r2) {
			int sum = 0;
			for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
				int in1 = u1 <= i && i <= d1 && l1 <= j && j <= r1;
				int in2 = u2 <= i && i <= d2 && l2 <= j && j <= r2;
				if (in1 + in2 == 1) sum += a[i][j];
			}
			mx = max(mx, sum);
		}
	}

	cout << mx << endl;
}
