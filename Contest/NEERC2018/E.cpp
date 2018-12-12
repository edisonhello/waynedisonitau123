

#include<bits/stdc++.h>
using namespace std;





int main(){
    int n; cin>>n;
    cout<<"a1 ";
    if(n==2)exit((cout<<"h1 h8"<<endl,0));
    string pos="a1";
    if(n<=54){
        auto nextpos=[&](string pos)->string{
            if((pos[1]-'0')%2==1){
                if(pos[0]=='h')++pos[1];
                else ++pos[0];
            }
            else{
                if(pos[0]=='a')++pos[1];
                else --pos[0];
            }
            return pos;
        };
        while(n>2){
            --n;
            pos=nextpos(pos);
            cout<<pos<<" ";
        }
        if(pos[0]=='h'){
            ++pos[1];
            cout<<pos<<" ";
            cout<<"h8"<<endl;
            exit(0);
        }
        else{
            pos[1]='8';
            cout<<pos<<" ";
            cout<<"h8"<<endl;
            exit(0);
        }
    }
    else{
        cout<<"a2 b2 b1 h1 g1 f1 e1 d1 c1 c2 d2 e2 f2 g2 h2 ";
        pos="h2";
        n-=15;
        auto nextpos=[&](string pos)->string{
            if((pos[1]-'0')%2==0){
                if(pos[0]=='h')++pos[1];
                else ++pos[0];
            }
            else{
                if(pos[0]=='a')++pos[1];
                else --pos[0];
            }
            return pos;
        };
        while(n>2){
            --n;
            pos=nextpos(pos);
            cout<<pos<<" ";
        }
        if(pos[1]=='7'){
            pos[1]='8';
            cout<<pos<<" ";
            cout<<"h8"<<endl;
            exit(0);
        }
        else{
            ++pos[0];
            cout<<pos<<" ";
            cout<<"h8"<<endl;
            exit(0);
        }
    }
}
