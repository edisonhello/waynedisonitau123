#include<bits/stdc++.h>
using namespace std;

string s;

int dfs(int l,int r){
    if(l==r && s[l]=='a')return 1;
    // cout<<"dfs: "<<l<<" "<<r<<endl;
   if(s[l]!='(' || s[r]!=')'){
       // cout<<"not"<<endl;
       return -2;
   }
   ++l, --r;
   if(r-l+1<=2)return -1;
   int le=0;
   vector<int> pos;
   for(int i=l;i<=r;++i){
       if(s[i]=='(')++le;
       else if(s[i]==')'){
           --le;
       }
       if(le==0 && s[i]=='+')pos.push_back(i);
   }
   // cout<<"pos size: "<<pos.size()<<endl;
   if(pos.size()!=1u)return -2;
   if(pos[0]==l+1 && s[l]=='a' && s[l+1]=='+' && s[l+2]=='a')return 1;
   int r1=dfs(l,pos[0]-1);
   int r2=dfs(pos[0]+1,r);
   if(r1==1 && r2==1 && s[pos[0]]=='+')return 1;
   if(r1==-1 || r2==-1)return -1;
   return -2;

   /* vector<int> ops;
   int le=0;
   for(int i=l;i<=r;++i){
       if(s[i]=='(')++le;
       else if(s[i]==')'){
           --le;
           if(le==0){
               if(s[i+1]!='+'){
                   cout<<"error"<<endl;
                   exit(0);
               }
               ops.push_back(i+1);
               ++i;
           }
       }
   } */
}

int main(){
    getline(cin,s);
    string ss;
    for(char c:s)if(c!=' ')ss+=c;
    s=ss;
    for(char &c:s)if(c=='-' || c=='*' || c=='/' || c=='%')c='+';
    for(char &c:s)if(c>='a' && c<='z')c='a';

    if(s=="a")exit((cout<<"proper"<<endl,0));
    int counta=0,countp=0,countl=0,countr=0;
    for(char c:s){
        if(c=='a')++counta;
        if(c=='+')++countp;
        if(c=='(')++countl;
        if(c==')')++countr;
    }
    if(countp!=counta-1)exit((cout<<"error"<<endl,0));
    if(countl!=countr)exit((cout<<"error"<<endl,0));

    int le=0;
    int items=1;
    for(char c:s){
        if(c=='(')++le;
        else if(c==')'){
            --le;
            if(le<0){
                cout<<"error"<<endl;
                exit(0);
            }
        }
        if(le==0 && c=='+')++items;
    }
    if(le!=0){
        cout<<"error"<<endl;
        exit(0);
    }
    for(int i=1;i<int(s.size());++i){
        if(s[i]=='+' && s[i-1]=='+'){
            cout<<"error"<<endl;
            exit(0);
        }
        if(s[i]==')' && s[i-1]=='('){
            cout<<"error"<<endl;
            exit(0);
        }
        if(s[i]=='(' && s[i-1]==')'){
            cout<<"error"<<endl;
            exit(0);
        }
        if(s[i]=='a' && s[i-1]=='a'){
            cout<<"error"<<endl;
            exit(0);
        }
        if(s[i-1]=='(' && s[i]=='+'){
            cout<<"error"<<endl;
            exit(0);
        }
        if(s[i-1]=='+' && s[i]==')'){
            cout<<"error"<<endl;
            exit(0);
        }
    }
    for(int i=2;i<int(s.size());++i){
        if(s[i-2]=='(' && s[i]==')'){
            if(s[i-1]=='+')exit((cout<<"error"<<endl,0));
            // else cout<<"improper"<<endl;
        }
        if(s[i-2]==')' && s[i]=='('){
            if(s[i-1]=='+');
            else exit((cout<<"error"<<endl,0));
        }
    }
    if(items!=2){
        cout<<"improper"<<endl;
        exit(0);
    }
    for(int i=2;i<int(s.size());++i){
        if(s[i-2]=='(' && s[i]==')'){
            cout<<"improper"<<endl;
            exit(0);
        }
    }
    
    // cout<<"go dfs"<<endl;
    s="("+s+")";
    // cout<<"s: "<<s<<endl;
    int res=dfs(0,s.size()-1);

    if(res==-1)cout<<"error"<<endl;
    else if(res==-2)cout<<"improper"<<endl;
    else cout<<"proper"<<endl;
}
