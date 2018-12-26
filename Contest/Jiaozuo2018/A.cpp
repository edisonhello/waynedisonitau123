#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n; while(n--){
        int c=0;
        for(int i=0;i<4;++i){
            int x; cin>>x;
            if(x)++c;
        }
        if(c==0)cout<<"Typically Otaku"<<'\n';
        else if(c==1)cout<<"Eye-opener\n";
        else if(c==2)cout<<"Young Traveller\n";
        else if(c==3)cout<<"Excellent Traveller\n";
        else if(c==4)cout<<"Contemporary Xu Xiake"<<'\n';
    }
}
