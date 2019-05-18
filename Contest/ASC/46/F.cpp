#include<bits/stdc++.h>
using namespace std;

const int mod=998244353;

#define mat vector<vector<int>> 

void open(mat &v){
    v=vector<vector<int>>(4,vector<int>(4,0));
}

mat operator*(const mat &a,const mat &b){
    mat r; open(r);
    for(int i=0;i<4;++i)for(int j=0;j<4;++j)for(int k=0;k<4;++k){
        int &z=r[i][j];
        z+=1ll*a[i][k]*b[k][j]%mod;
        if(z>=mod)z-=mod;
    }
    return r;
}

mat pw(mat b,int n){
    mat a; open(a);
    a[0][0]=a[1][1]=a[2][2]=a[3][3]=1;
    while(n){
        if(n&1)a=a*b;
        b=b*b; n>>=1;
    }
    return a;
}

int main(){
#ifdef ONLINE_JUDGE
    freopen("figure.in", "r", stdin);
    freopen("figure.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; while(cin>>n,n){
        mat tr; open(tr);
        tr[0][0]=1;
        tr[0][1]=1;
        tr[1][0]=1;
        tr[1][1]=2;
        tr[1][3]=1;
        tr[2][0]=1;
        tr[2][1]=2;
        tr[2][2]=1;
        tr[2][3]=2;
        tr[3][2]=1;
        tr[3][3]=1;
        tr=pw(tr,n);
        mat o; open(o);
        o[0][0]=1;
        cout<<(o*tr)[0][0]<<'\n';
    }
}
