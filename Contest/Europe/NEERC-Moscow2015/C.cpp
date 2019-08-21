#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int xl = 0, xr = 1000000000;
	while (xr > xl) {
		int xm = (xl + xr) >> 1;
		cout << xm << " " << 0 << endl << flush;
		int ans1; cin >> ans1;
		cout << xm + 1 << " " << 0 << endl << flush;
		int ans2; cin >> ans2;
		if (ans2) xl = xm + 1;
		else xr = xm;
	}
	int yl = 0, yr = 1000000000;
	while (yr > yl) {
		int ym = (yl + yr) >> 1;
		cout << 0 << " " << ym << endl << flush;
		int ans1; cin >> ans1;
		cout << 0 << " " << ym + 1 << endl << flush;
		int ans2; cin >> ans2;
		if (ans2) yl = ym + 1;
		else yr = ym;
	}
	cout << "A " << xl << " " << yl << endl;
}<Paste>
