

#include<bits/stdc++.h>
using namespace std;



int main(){
    long long k; cin>>k;
    string s; cin>>s;
    int le=1;
    while((1ll<<(le-1))<=k)++le; --le;
    // cout<<"le: "<<le<<endl;
    auto ok=[&](const int le)->bool{
        bitset<66> del;
        int de=int(s.size())-le;
        for(int i=1;i<int(s.size());++i){
            if(de==0)break;
            if(s[i]=='1'){
                del[i]=1;
                --de;
            }
        }
        for(int i=int(s.size())-1;i>=0;--i){
            if(de==0)break;
            if(s[i]=='0'){
                del[i]=1;
                --de;
            }
        }
        long long val=0,base=1;
        for(int i=int(s.size())-1;i>=0;--i){
            if(del[i])continue;
            if(s[i]=='1')val+=base;
            base<<=1;
        }
        return val<=k;
    };
    if(le>int(s.size()))exit((cout<<0<<endl,0));
    while(1){
        if(ok(le)){
            cout<<int(s.size())-le<<endl;
            exit(0);
        }
        --le;
    }
}

