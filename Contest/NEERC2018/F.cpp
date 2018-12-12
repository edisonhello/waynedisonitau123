#include<bits/stdc++.h>
using namespace std;

int mp[31630];
bitset<31630> notp;
vector<int> ps;
void init(){
    for(int i=2;i<31630;++i){
        if(notp[i])continue;
        ps.push_back(i);
        mp[i]=i;
        for(int j=i*i;j<31630;j+=i){
            mp[j]=i;
            notp[j]=1;
        }
    }
}

map<int,int> de;

int main(){
    init();
    int n; cin>>n;
    [&](int n){
        for(int i:ps){
            while(n%i==0){
                n/=i;
                ++de[i];
            }
        }
        if(n>1)++de[n];
    }(n);
    if(de.size()==1u){
        cout<<"NO"<<endl;
        exit(0);
    }
    int A=1,B=1;
    bool doA=1;
    for(auto p:de){
        if(doA){
            doA=0;
            while(p.second--)A*=p.first;
        }
        else{
            while(p.second--)B*=p.first;
        }
    }
    if(A>B)swap(A,B);
    // cerr<<"A: "<<A<<" , B: "<<B<<endl;
    for(int i=1;i<A;++i){
        int q=n-1-B*i;
        if(q%A==0){
            int j=q/A;
            cout<<"YES"<<endl;
            cout<<2<<endl;
            cout<<i<<" "<<A<<endl;
            cout<<j<<" "<<B<<endl;
            exit(0);
        }
    }
}
