#include <bits/stdc++.h>
using namespace std;

vector<int> p;
bool isp[1000006];

int main() {
    for (int i = 2; i <= 1000000; ++i) {
        if (!isp[i]) {
            p.push_back(i);
            for (long long j = 1ll * i * i; j <= 1000000; j += i) {
                isp[j] = 1;
            }
        }
    }
    int t; cin >> t; while (t--) {
        long long x; cin >> x;
        if (x == 1) {
            cout << "no" << endl;
            continue;
        }

        bool yes = 0;
        for (int pp : p) {
            int c = 0;
            while (x % pp == 0) {
                ++c;
                x /= pp;
            }
            if (c >= 2) {
                yes = 1;
                break;
            }
        }

        for (int i = max(2, (int)sqrt(x) - 3); i <= (int)sqrt(x) + 3; ++i) {
            if (1ll * i * i == x) {
                yes = 1;
                break;
            }
        }

        if (yes) {
            cout << "yes" << endl;
            continue;
        }

        cout << "no" << endl;
    }
}

