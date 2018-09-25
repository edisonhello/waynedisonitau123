#include<bits/stdc++.h>
using namespace std;

int cnt[10];
bool countmost(string s){
    memset(cnt,0,10<<2);
    for(char c:s)++cnt[c-'0'];
    int n=int(s.size());
    for(int i=0;i<10;++i){
        int ci=cnt[i],co=n-cnt[i];
        if(ci>n/2){
            int le=ci-co;
            if(i){ while(le--)cout<<i; cout<<"\n"; }
            else cout<<0<<"\n";
            return 1;
        }
        if(ci==co){
            cout<<"0\n";
            return 1;
        }
    }
    return 0;
}

int lm[1000006],rm[1000006];
void solve(){
    string s; cin>>s;
    int n=int(s.size());
    if(countmost(s))return;
    if(n%2==0){ cout<<0<<"\n"; return; }
    memset(cnt,0,10<<2);
    int mx=0;
    for(int i=0;i<n;++i){
        int z=s[i]-'0';
        ++cnt[z];
        mx=max(mx,cnt[z]);
        if(mx>(i+1)/2)lm[i]=1;
        else lm[i]=0;
        // cout<<"lm "<<i<<" "<<lm[i]<<endl;
    }
    memset(cnt,0,10<<2);
    mx=0;
    for(int i=n-1,j=1;i>=0;--i,++j){
        int z=s[i]-'0';
        ++cnt[z];
        mx=max(mx,cnt[z]);
        if(mx>j/2)rm[i]=1;
        else rm[i]=0;
        // cout<<"rm "<<i<<" "<<rm[i]<<endl;
    }
    int mn=87;
    if(!rm[1] && n%2==1)mn=min(mn,int(s[0]-'0'));
    if(!lm[n-2] && n%2==1)mn=min(mn,int(s[n-1]-'0'));
    for(int i=1;i<n-1;++i)if(!lm[i-1] && !rm[i+1] && i%2==0 && (n-i-1)%2==0)mn=min(mn,int(s[i]-'0'));
    cout<<mn<<"\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--)solve();
}
