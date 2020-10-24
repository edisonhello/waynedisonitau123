#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; ++T) {
        string s; cin >> s;
        long long n; cin >> n;
        vector<int> v(s.size());
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == 'W') v[i] = 0;
            else if (s[i] == 'R') v[i] = 1;
            else v[i] = 2;
        }
        
        long long b = 1, A = 0;
        while (b <= n) b *= 3, ++A;

        while (n >= 1) {
            while (b > n) {
                b /= 3;
                --A;
            }
            n -= b;
            
            vector<int> nv(s.size());
            for (int i = 0; i < (int)s.size(); ++i) {
                nv[i] = (v[i] + v[(i + b) % s.size()]) % 3;
            }
            v.swap(nv);

        }

        vector<int> cc(3, 0);
        for (int i : v) ++cc[i];

        cout << "Case #" << T <<": " << cc[0] << ' ' << cc[1] << ' ' << cc[2] << endl;

    }
}
