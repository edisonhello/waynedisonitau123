#include<bits/stdc++.h>
using namespace std;

const int magic = 500000;

int main(){
    int l, m; cin >> l >> m; cin.ignore();
    vector<string> v;
    int mp = 1000000000;
    for (int i = 0; i < m; ++i) {
        string s;
        int p = 0, c = 0, t = 0, r = 0; // cin >> s >> p >> c >> t >> r;
        char zz;
        while ((zz = getchar()) != ',') {
            s += zz;
        }
        while ((zz = getchar()) != ',') {
            p = p * 10 + zz - '0';
        }
        while ((zz = getchar()) != ',') {
            c = c * 10 + zz - '0';
        }
        while ((zz = getchar()) != ',') {
            t = t * 10 + zz - '0';
        }
        while ((zz = getchar()) != '\n') {
            r = r * 10 + zz - '0';
        }
        // cout << s << " " << p << " " << c << " " << t << " " << r << endl;
        bool ok = true;
        for (int j = 1; j <= magic; ++j) {
            long long k = j * 1ll * 10080;
            if ((k / (t + r)) * 1ll * t * c + min(1ll * t, k % (t + r)) * c < 1ll * j * l) {
                ok = false;
                break;
            }
        }
        if (ok) {
            if (p < mp) mp = p, v = { s };
            else if (p == mp) v.push_back(s);
        }
    }
    if (v.size() == 0) {
        cout << "no such mower" << endl;
    } else {
        for (string s : v) cout << s << endl;
    }
}
