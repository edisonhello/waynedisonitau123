#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll get(string s) {
    reverse(s.begin(), s.end());
    ll pos = 0, len = 1;
    for (char c : s) {
        if (c == '0') {

        } else {
            pos = len + (len - pos) - 1;
        }
        len *= 2;
    }
    return pos;
}

int main() {
    int n; cin >> n;
    string a, b; cin >> a >> b;
    ll pa = get(a), pb = get(b);
    //cerr << "pa = " << pa << ", pb = " << pb << endl;
    cout << pb - pa - 1 << endl;
}
