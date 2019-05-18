#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

char parse(int n){
    if(n<10)return '0'+n;
    else return 'A'+n-10;
}

int main() {
    srand(clock());
    int n=7;
    cout << n << endl;
    for (int i = 2; i <= n; ++i) {
        int p = rand() % (i - 1) + 1;
        int d = rand() % 100 + 1;
        cout << p << ' ' << i << ' ' << d << endl;
    }
}
