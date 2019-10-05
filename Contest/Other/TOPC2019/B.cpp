#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    set<int> s;
    while (n--) {
        int x; cin >> x;
        s.insert(x);
    }
    cout << s.size() << endl;
}
