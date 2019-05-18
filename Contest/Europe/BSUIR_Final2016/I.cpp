#include <bits/stdc++.h>
using namespace std;

string ans[50];

int main() {
    ans[1] = "1";
    for (int i = 2; i < 45; ++i) {
        ans[i] = ans[i - 1];
        for (char &c : ans[i]) if (c == '1') c = '2'; else c = '1';
        ++i;
        ans[i] = ans[i - 1] + "1";
        ++i;
        ans[i] = "1" + ans[i - 1];
    }
    int t; cin >> t; cout << ans[t] << endl;
}
