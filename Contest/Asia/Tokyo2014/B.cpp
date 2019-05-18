#include<bits/stdc++.h>
using namespace std;

int lr(string s){
    int now=0;
    char op='+';
    for(char c:s){
        if(c=='+' || c=='*')op=c;
        else{
            if(op=='*')now*=c-'0';
            else now+=c-'0';
        }
    }
    return now;
}
int pp(string s){
    vector<int> num;
    vector<int> op;
    for(char c:s){
        if(c=='+' || c=='*'){
            op.push_back(c);
        }
        else{
            int n=c-'0';
            if(op.size()){
                if(op.back()=='*'){
                    int t=num.back(); num.pop_back();
                    op.pop_back();
                    num.push_back(t*n);
                }
                else{
                    num.push_back(n);
                }
            }
            else num.push_back(n);
        }
    }
    int x=0;
    for(int i:num)x+=i;
    return x;
}

int main(){
    string s; cin>>s;
    int ans; cin>>ans;
    int a=pp(s)==ans;
    int b=lr(s)==ans;
    // cout<<pp(s)<<" "<<lr(s)<<endl;
    if(a && b)cout<<"U"<<endl;
    else if(!a && !b)cout<<"I"<<endl;
    else if(a)cout<<"M"<<endl;
    else cout<<"L"<<endl;
}
