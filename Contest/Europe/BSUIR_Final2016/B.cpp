#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    if (n == 2 || n == 3) {
        cout << "-1" << endl;
        exit(0);
    }
    vector<int> pat;
    for (int i = 2; i <= n; i += 2) {
        pat.push_back(i);
    }
    for (int i = 1; i <= n; i += 2) {
        pat.push_back(i);
    }
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j : pat) cout << j << " ";
        cout << endl;
        for (int &j : pat) j += n;
    }
}
