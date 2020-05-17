#include <bits/stdc++.h>
using namespace std;

int main() {
	int t, n; cin >> t >> n;
	cout << fixed << setprecision(12);
	while (t--) {
		if (n == 1) {
			cout << 0 << ' ' << 0.6666666667 << endl;
			fflush(stdout);
			int z; cin >> z;
			if (z == 0) exit(0);
		} else {
			vector<double> cho(n + 1, 0);
			cho[0] = 1;
			for (int i = 1; i <= n; ++i) {
				if (i & 1) {
					if (i == 1) {
						cout << "0 0.3333333333333" << endl;
						fflush(stdout);
						cho[0] = (double)2 / 3;
						cho[1] = (double)1 / 3;
					} else if (i == n) {
						cout << "0 0.6666666667" << endl;
						fflush(stdout);
						int x; cin >> x;
						if (x == 0) exit(0);
					} else {
						int mx = 2;
						for (int j = 4; j <= i; j += 2) if (cho[j] > cho[mx]) {
							mx = j;
						}

						cout << mx << " " << (double)2 / 3 << endl;
						fflush(stdout);
						cho[i] = cho[mx] * 2 / 3;
						cho[mx] /= 3;
					}
				} else {
					int j; double p; cin >> j >> p;
					cho[i] = cho[j] * p;
					cho[j] *= (1 - p);
				}

				// cerr << "cho = ";
				// for (double i : cho) cerr << i << ' ';
				// cerr << endl;
			}
		}
	}
}

