#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() {
    int t; cin >> t; 
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int x, y; cin >> x >> y;
        int dir = 0;
        set<pair<int, int>> st;
        set<pair<int, int>> ans;
        string s; cin >> s;
        st.insert(make_pair(x, y));
        for (char c : s) {
            if (c == 'F') {
                x += dx[dir];
                y += dy[dir];
                if (st.count(make_pair(x, y))) {
                    ans.insert(make_pair(x, y));
                }
                st.insert(make_pair(x, y));
            } else if (c == 'L') {
                dir = (dir + 3) % 4;
            } else {
                dir = (dir + 1) % 4;
            }
        }

        cout << x << ' ' << y << ' ' << ans.size() << endl;
    }
}
