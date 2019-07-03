#include <bits/stdc++.h>
using namespace std;
 
 
 
int main() {
    long long a, b; cin >> a >> b;
    vector<string> v;
    while (a != b) {
        if ((a & 1) == 0 && (b & 1) == 0) {
            a /= 2, b /= 2;
        } else if ((a & 1) == 0 && (b & 1) == 1) {
            v.push_back("B+=B");
            a /= 2;
        } else if ((a & 1) == 1 && (b & 1) == 0) {
            v.push_back("A+=A");
            b /= 2;
        } else if (a > b) {
            v.push_back("A+=B");
            v.push_back("B+=B");
            a = (a + b) / 2;
        } else if (a < b) {
            v.push_back("B+=A");
            v.push_back("A+=A");
            b = (a + b) / 2;
        }
    }
    cout << v.size() << endl;
    for (string s : v) cout << s << '\n';
}
