#include <bits/stdc++.h>
using namespace std;

vector<int> pos[105];

void NO() {
    cout << "Impossible" << endl;
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    while (k--) {
        int x, y; cin >> x >> y;
        pos[x].push_back(y);
    }

    for (int i = 1; i <= n; ++i) sort(pos[i].begin(), pos[i].end());
    for (int i = 1; i <= n; ++i) reverse(pos[i].begin(), pos[i].end());

    int x = 1, y = 1;
    string ans;

    while (x != n || y != m) {
        // cerr << "x y " << x << ' ' << y << endl;
        if (x == n) {
            if (pos[x].size()) {
                // cerr << "back " << pos[x].back() << endl;
                if (y > pos[x].back()) NO();
                else if (y == pos[x].back()) pos[x].pop_back();
                else {
                    ans += "R";
                    ++y;
                }
            } else {
                ans += "R";
                ++y;
            }
        } else {
            if (pos[x].size()) {
                if (y > pos[x].back()) NO();
                else if (y == pos[x].back()) pos[x].pop_back();
                else {
                    ans += "R";
                    ++y;
                }
            } else {
                ans += "D";
                ++x;
            }
        }
    }

    if (pos[x].size() && pos[x].back() == y) pos[x].pop_back();

    for (int i = 1; i <= n; ++i) if (pos[i].size()) NO();

    cout << ans << endl;
}

