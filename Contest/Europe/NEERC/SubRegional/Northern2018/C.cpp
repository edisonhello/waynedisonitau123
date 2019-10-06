#include<bits/stdc++.h>
using namespace std;

char mo[]={'a','e','i','o','u','w','y'};
int id[26];
char ou[256];

int we[19][19];

int main(){
    freopen("consonant.in","r",stdin);
    freopen("consonant.out","w",stdout);
    id[1]=0; //b;
    id[2]=1; //c;
    id[3]=2; //d;
    id[5]=3; //f;
    id[6]=4; //g;
    id[7]=5; //h;
    id[9]=6; //j;
    id[10]=7; //k;
    id[11]=8; //l;
    id[12]=9; //m;
    id[13]=10; //n;
    id[15]=11; //p;
    id[16]=12; //q;
    id[17]=13; //r;
    id[18]=14; //s;
    id[19]=15; //t;
    id[21]=16; //v;
    id[23]=17; //x;
    id[25]=18; //z;
    string s; cin>>s;
    for(unsigned int i=1;i<s.size();++i){
        if(s[i]==s[i-1])continue;
        bool amo=0;
        for(unsigned int j=0;j<7;++j){
            if(s[i-1]==mo[j])amo=1;
            else if(s[i]==mo[j])amo=1;
        }
        if(amo)continue;
        int i1=id[s[i-1]-'a'];
        int i2=id[s[i]-'a'];
        if(i2<i1)swap(i1,i2);
        ++we[i1][i2];
    }
    int mxv=0,st=0;
    for(int z=0;z<(1<<19);++z){
        int vv=0;
        for(int i=0;i<19;++i)for(int j=i+1;j<19;++j){
            if((!!(z&(1<<i))) != (!!(z&(1<<j))))vv+=we[i][j];
        }
        if(vv>mxv){
            mxv=vv;
            st=z;
        }
    }
    for(int i='a';i<='z';++i)ou[i]=i;
    if(st&(1<<0))ou['b']='B';
    if(st&(1<<1))ou['c']='C';
    if(st&(1<<2))ou['d']='D';
    if(st&(1<<3))ou['f']='F';
    if(st&(1<<4))ou['g']='G';
    if(st&(1<<5))ou['h']='H';
    if(st&(1<<6))ou['j']='J';
    if(st&(1<<7))ou['k']='K';
    if(st&(1<<8))ou['l']='L';
    if(st&(1<<9))ou['m']='M';
    if(st&(1<<10))ou['n']='N';
    if(st&(1<<11))ou['p']='P';
    if(st&(1<<12))ou['q']='Q';
    if(st&(1<<13))ou['r']='R';
    if(st&(1<<14))ou['s']='S';
    if(st&(1<<15))ou['t']='T';
    if(st&(1<<16))ou['v']='V';
    if(st&(1<<17))ou['x']='X';
    if(st&(1<<18))ou['z']='Z';
    for(char c:s){
        cout<<ou[c];
    }
    cout<<endl;
}
