#include<bits/stdc++.h>
using namespace std;

bitset<6556> cover;

int main(){
    int n; cin>>n; while(n--){
        int l,r; cin>>l>>r;
        for(int i=l;i<=r;++i){
            cover[i]=1;
        }
    }
    cout<<cover.count()<<endl;
}


