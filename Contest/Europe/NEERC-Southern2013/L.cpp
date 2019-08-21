#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    long long n, d, a, b; cin >> n >> d >> a >> b;
    long long ctnup = 0, ctndn = 0, prv; cin >> prv; --n;
    long long itm = 0;
    while (n--) {
        long long cost; cin >> cost;
        if (cost > prv) {
            ctndn = 0;
            ctnup++;
            long long buy = min(ctnup * a, d / cost);
            itm += buy;
            d -= buy * cost;
        } else if (cost < prv) {
            ctnup = 0;
            ctndn++;
            long long sell = min(itm, ctndn * b);
            itm -= sell;
            d += sell * cost;
        } else {
            ctndn = 0;
            ctnup = 0;
        }
        prv = cost;
    }
    cout << d << " " << itm << endl;
}
