#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        bool ans = true;
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            ans &= x % 3 == 0;
        }
        cout << "Case #" << tc << ": " << (ans ? "Yes" : "No") << "\n";
    }
}

