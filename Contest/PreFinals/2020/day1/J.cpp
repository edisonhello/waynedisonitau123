#include <bits/stdc++.h>
using namespace std;


int main() {
	int c1 = 0, c2 = 0, c3 = 0;
	while (true) {
		char c; cin >> c;
		if (c == 'W') break;
		
		if (c == 'I') {
			c1 = 1;
			cout << 1 << ' ' << 1 << endl;
		} else if (c == 'O' || c == 'S' || c == 'T' || c == 'Z') {
			if (c == 'O') cout << 0 << ' ';
			else cout << 1 << ' ';

			++c2;
			if (c2 % 3 == 1) cout << 2 << endl;
			else if (c2 % 3 == 2) cout << 4 << endl;
			else cout << 6 << endl;
		} else {
			c3 = 1;
			cout << 2 << ' ' << 8 << endl;
		}
	}
}

