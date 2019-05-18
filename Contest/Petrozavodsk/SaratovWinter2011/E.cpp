#include<bits/stdc++.h>
using namespace std;

int main(){
#ifdef ONLINE_JUDGE
    freopen("pour.in", "r", stdin);
    freopen("pour.out", "w", stdout);
#endif
    int n,a,b; cin>>n>>a>>b;
    int down = b/a;
    int ans = (n + (n + down-1) / down + 1) % 2 + 1;
    cout << ans << endl;
}
