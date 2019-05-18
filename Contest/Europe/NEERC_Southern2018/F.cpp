#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> a[4];
int s[4][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int x; cin >> x;
        int k = (s[0] - '0') * 2 + (s[1] - '0');
        a[k].push_back(x);
    }
    for (int i = 0; i < 4; ++i) {
        sort(a[i].begin(), a[i].end(), greater<int>());
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j <= a[i].size(); ++j) s[i][j] = s[i][j - 1] + a[i][j - 1];
    }
    int a11 = a[3].size();
    long long sum = 0, ans = 0;
    for (int i = 0; i < a[3].size(); ++i) sum += a[3][i];
    for (int i = 0; i <= a[0].size(); ++i) {
        int diff = a11 - i;
        if (diff < 0) break;
        if (abs(int(a[1].size()) - int(a[2].size())) <= diff) ans = max(ans, sum + s[1][a[1].size()] + s[2][a[2].size()]);
        else if (a[1].size() < a[2].size()) ans = max(ans, sum + s[1][a[1].size()] + s[2][a[1].size() + diff]);
        else ans = max(ans, sum + s[2][a[2].size()] + s[1][a[2].size() + diff]);
        if (i < a[0].size()) sum += a[0][i];
    }
    cout << ans << endl;
}
