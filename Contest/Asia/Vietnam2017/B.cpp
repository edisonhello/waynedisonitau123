#include<bits/stdc++.h>
using namespace std;

/* struct mat{
    int a[2][2];
    void init(int v=0){
        if(v==0){ memset(a,0,sizeof(a)); }
        if(v==1){ memset(a,0,sizeof(a)); a[0][0]=a[1][1]=1; }
    }
    mat(int v=0){ init(v); }
};

mat operator*(const mat &a,const mat &b){
    mat rt(0);

} */

const int maxn = 2e6 + 5;
int f[maxn], inv[maxn];
int fi[1000006];

int fpow(int a, int n, int mod) {
    int r = 1;
    for (; n; n >>= 1) {
        if (n & 1) r = r * 1ll * a % mod;
        a = a * 1ll * a % mod;
    }
    return r;
}

int cnk(int n, int k, int m) {
    if (n < k) return 0;
    if(n>=m || k>=m)return cnk(n/m,k/m,m) * 1ll * cnk(n%m,k%m,m) % m;
    return f[n] * 1ll * inv[k] % m * 1ll * inv[n - k] % m;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts; cin>>ts; while(ts--){
        int n,m; cin>>n>>m;
        fi[0]=1; fi[1]=2%m;
        for(int i=2;i<=n;++i){
            fi[i]=fi[i-1]+fi[i-2];
            if(fi[i]>=m)fi[i]-=m;
        }
        int ans = fi[n];
        if (n % 2 == 0) {
            f[0] = inv[0] = 1;
            int far = min(n + 1, m - 1);
            for (int i = 1; i <= far; ++i) {
                f[i] = f[i - 1] * 1ll * i % m;
                // inv[i] = fpow(f[i], m - 2, m);
            }
            inv[far] = fpow(f[far], m-2, m);
            for(int i = far - 1; i >= 0; --i) {
                inv[i] = inv[i + 1] * 1ll * (i + 1) % m;
            }
            int tans = cnk(n,n/2,m);
            // int tans = f[n] * 1ll * inv[n / 2] % m * 1ll * inv[n / 2] % m;
            (ans += tans) %= m;
            ans -= n / 2 + 1;
            ans %= m;
            ans += m;
            ans %= m;
        }
        cout << ans << '\n';
    }
}
