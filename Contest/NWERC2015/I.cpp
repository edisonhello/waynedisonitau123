#include <bits/stdc++.h>
using namespace std;

int main() {
	string s; cin >> s; 
	long long x = 0, y = 0;
	for (char c : s) {
		if (c == '0' || c == '2') x *= 2;
		else x = x * 2 + 1;
		if (c == '0' || c == '1') y *= 2;
		else y = y * 2 + 1;
	}
	cout << s.size() << " " << x << " " << y << endl;
}
