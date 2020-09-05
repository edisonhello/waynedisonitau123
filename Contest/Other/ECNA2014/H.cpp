#include <bits/stdc++.h>
using namespace std;

void output(double t) {
    int h = floor(t / 3600);
    t -= h * 3600;
    if (h == 0) cout << "12:";
    else cout << h << ":";
    int m = (int)t / 60;
    printf("%02d:", m);
    t -= m * 60;
    printf("%02d\n", (int)round(t));
}

int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; ++T) {
        cout << "Case " << T << ": ";
        int deg; string str; double tm; cin >> deg >> str >> tm;
        if (tm == 12) tm = 0;
        tm *= 3600;
        vector<double> tms;
        for (int i = 0; i < 11; ++i) {
            tms.push_back((i * 360 + deg) * 120 / (double)(11));
        }
        sort(tms.begin(), tms.end());
        
        if (str == "after") {
            bool o = 0;
            for (int i = 0; i < (int)tms.size(); ++i) {
                if (tms[i] > tm) {
                    output(tms[i]);
                    o = 1;
                    break;
                }
            }
            if (!o) {
                output(tms[0]);
            }
        } else {
            bool o = 0;
            for (int i = (int)tms.size() - 1; i >= 0; --i) {
                if (tms[i] < tm) {
                    output(tms[i]);
                    o = 1;
                    break;
                }
            }
            if (!o) {
                output(tms.back());
            }
        }
    }
}

