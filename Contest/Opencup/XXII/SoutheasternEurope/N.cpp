#include <bits/stdc++.h>
#define int ll
using namespace std;
#define ll long long
#define y1 zck_is_king
#define pii pair<ll, ll>
#define ull unsigned ll
#define f first
#define s second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (int)x.size()
#define SQ(x) (x)*(x)
#define MN(a,b) a = min(a,(__typeof__(a))(b))
#define MX(a,b) a = max(a,(__typeof__(a))(b))
#define pb push_back
#define REP(i,n) for (int i = 0; i<n; ++i)
#define RREP(i,n) for (int i = n-1; i>=0; --i)
#define REP1(i,n) for (int i = 1; i<=n; ++i)
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#ifdef BALBIT
#define IOS()
#define bug(...) fprintf(stderr,"#%d (%s) = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define bug(...)
#endif

const int iinf = 1e9+10;
const ll inf = 1ll<<60;
const ll mod = 1e9+7 ;


void GG(){cout<<"0\n"; exit(0);}

ll mpow(ll a, ll n, ll mo = mod){ // a^n % mod
    ll re=1;
    while (n>0){
        if (n&1) re = re*a %mo;
        a = a*a %mo;
        n>>=1;
    }
    return re;
}

ll inv (ll b, ll mo = mod){
    if (b==1) return b;
    return (mo-mo/b) * inv(mo%b,mo) % mo;
}

const int maxn = 1000000+5;

ll prod2[maxn*4], sum[maxn*4], tg[maxn*4];
//bool has[maxn*4];

void push(int o, int l, int r){
    if (tg[o]!=1) {
        sum[o] *= tg[o]; sum[o] %= mod;
        prod2[o] *= tg[o]; prod2[o] %= mod;
        if (l!=r) {
            (tg[o*2] *= tg[o])%=mod;
            (tg[o*2+1] *= tg[o]) %= mod;
        }
        tg[o] = 1;
    }
}
void MOmul(int L, int R, ll p, int o=1, int l=0, int r=maxn-1) {
    push(o,l,r);
    if (l>R || r<L) return;
    if (l >= L && r <= R) {
        tg[o] *= p; tg[o] %= mod;
        push(o,l,r);
        return;
    }
    int mid = (l+r)/2;
    MOmul(L,R,p,o*2,l,mid);
    MOmul(L,R,p,o*2+1,mid+1,r);
    sum[o] = (sum[o*2] + sum[o*2+1])%mod;
}
void MOset(int p, ll v, int o=1, int l=0, int r=maxn-1) {
    push(o,l,r);
    if (l>p || r<p) return;
    if (l >= p && r <= p) {
        sum[o] = v * prod2[o] % mod;
        bug(sum[o]);
        return;
    }
    int mid = (l+r)/2;
    MOset(p,v,o*2,l,mid);
    MOset(p,v,o*2+1,mid+1,r);
    sum[o] = (sum[o*2] + sum[o*2+1])%mod;
}

struct upd{
    ll l,r; bool on;
};

int IT = 0;
vector<pair<ll, ll> > hi[maxn];
//int at[maxn*4];

signed main(){
    IOS();

    map<pii, int > mp;
    int n; cin>>n;
//    assert(n <= 200000);
    vector<upd> ev;
    vector<ll> hv;
    REP(i,n) {
        ll t,l,r; cin>>t>>l>>r;  --l; --r;
        assert(l <= 1e9 && r <= 1e9);
        int ho = mp.count({l,r})?mp[{l,r}]:mp[{l,r}]=IT++;
        if (t == 1) {
            pii p = hi[ho].back(); hi[ho].pop_back();
            ev.pb({p.f, p.s, 0});
        }else{
            pii p = {l*(n+10), r*(n+10) + i + 1};
            hi[ho] .pb( p );
            ev.pb({p.f, p.s, 1});
        }
        hv.pb({ev.back().l});
        hv.pb({ev.back().r});
    }
    fill(tg, tg+maxn*4,1);
    fill(prod2, prod2+maxn*4,1);
    SORT_UNIQUE(hv);
    ll i2 = inv(2)%mod;
    for (auto u : ev) {
        int L = lower_bound(ALL(hv), u.l)-hv.begin();
        int R = lower_bound(ALL(hv), u.r)-hv.begin();
        bug(L,R,u.on);
        MOmul(L, R-1, u.on?2:i2);
        MOset(R, u.on);
        cout<<sum[1]%mod<<endl;
    }


}

