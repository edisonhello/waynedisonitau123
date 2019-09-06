#include <bits/stdc++.h>
using namespace std;

int a[100];

int now = 1000;
int acts = 0;
int sa = 2, sb = 1;

int ask(char c) {
    // if (c == '+') now += sa;
    // else now -= sb;
    // ++acts;
    // return now == 0;
    cout << c << endl; int x; cin >> x; return x;
}

int _main() {
    // a[1] = 1; a[2] = 50; a[3] = 106;
    a[1] = 5;
    // for (int i = 2; i <= 30; ++i) a[i] = a[i - 1] * 2 + a[i - 2] + 4;
    // for (int i = 4; i <= 30; ++i) a[i] = a[i - 1] * 2 + a[i - 2] + 10;
    for (int i = 2; i < 100; ++i) a[i] = a[i - 1] * (i & 1 ? 3.2 : 3.5);
    // for (int i = 3; i <= 30; ++i) cout << a[i] << endl;
    for (int i = 1; ; ++i) {
        char out = (i & 1 ? '+' : '-');
        for (int j = 0; j < a[i]; ++j) {
            int x = ask(out);
            if (x == 1) {
                x = ask('+');
                x = ask('-');
                if (x == 1) {
                    cout << "! ugly" << endl;
                    return 0;
                }
                x = ask('-');
                if (x == 1) {
                    cout << "! good" << endl;
                    return 0;
                } 
                cout << "! bad" << endl;
                return 0;
            }
        }
        // cerr << "i = " << i << endl;
    }
}

int main() {
    _main();
    return 0;
    int mx = 0;
    for (int i = 1; i <= 10000; ++i) {
        now = i; acts = 0;
        sa = 2; sb = 1;
        _main();
        cerr << "i = " << i << " m = " << i << " sa = " << sa << " sb = " << sb << " acts = " <<acts << endl;
        mx = max(mx, acts);

        now = -i; acts = 0;
        sa = 1; sb = 2;
        _main();
        cerr << "i = " << i << " m = " << -i << " sa = " << sa << " sb = " << sb << " acts = " <<acts << endl;
        mx = max(mx, acts);

        now = i; acts = 0;
        sa = 1; sb = 1;
        _main();
        cerr << "i = " << i << " m = " << i << " sa = " << sa << " sb = " << sb << " acts = " <<acts << endl;
        mx = max(mx, acts);

        now = i; acts = 0;
        sa = -1; sb = -1;
        _main();
        cerr << "i = " << i << " m = " << i << " sa = " << sa << " sb = " << sb << " acts = " <<acts << endl;
        mx = max(mx, acts);

        now = -i; acts = 0;
        sa = 1; sb = 1;
        _main();
        cerr << "i = " << i << " m = " << -i << " sa = " << sa << " sb = " << sb << " acts = " <<acts << endl;
        mx = max(mx, acts);

        now = -i; acts = 0;
        sa = -1; sb = -1;
        _main();
        cerr << "i = " << i << " m = " << -i << " sa = " << sa << " sb = " << sb << " acts = " <<acts << endl;
        mx = max(mx, acts);
        if (mx > 30 * i) {
            cerr << "jizz" << endl;
            return 0;
        }
    }    
}
