#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,avx,avx2")
#include<bits/stdc++.h>
using namespace std;

#define grid vector<vector<int>>

int n,m,c;
vector<int> comm;

grid newgrid(){
    return grid(n,vector<int>(m,0));
}

vector<vector<long long>> last;

void draw(long long ink,grid &rt){
    int nx=n-1,ny=0;
    long long step=0;
    for(int z:comm){
        int d=z>>25;
        int s=z&((1<<25)-1);
        // cout<<"ds: "<<d<<" "<<s<<endl;
        if(d==0){
            for(int z=0;z<s;++z){
                ++step;
                if(step>ink){
                    rt[nx][ny]=0;
                }
                else{
                    rt[nx][ny]=1;
                }
                --nx;
            }
        }
        else if(d==1){
            for(int z=0;z<s;++z){
                ++step;
                if(step>ink){
                    rt[nx][ny]=0;
                }
                else{
                    rt[nx][ny]=1;
                }
                ++nx;
            }
        }
        else if(d==2){
            for(int z=0;z<s;++z){
                ++step;
                if(step>ink){
                    rt[nx][ny]=0;
                }
                else{
                    rt[nx][ny]=1;
                }
                ++ny;
            }
        }
        else{
            for(int z=0;z<s;++z){
                ++step;
                if(step>ink){
                    rt[nx][ny]=0;
                }
                else{
                    rt[nx][ny]=1;
                }
                --ny;
            }
        }
    }
    ++step;
    if(step>ink)rt[nx][ny]=0;
    else rt[nx][ny]=1;
}

void cleargrid(grid &v){
    for(auto &vv:v)fill(vv.begin(),vv.end(),0);
}

void print(grid v){
    for(auto s:v){
        for(bool i:s){
            if(i)cout<<"#";
            else cout<<".";
        }
        cout<<endl;
    }
}

vector<vector<long long>> solve(vector<int> evv) {
    last.resize(n, vector<long long>(m, 0));
    vector<vector<vector<pair<long long, int>>>> rg(n + 1), lt(n + 1);
    vector<vector<vector<pair<long long, int>>>> dn(n + 1), up(n + 1);
    for (int i = 0; i < n; ++i) {
        rg[i].resize(m + 1);
        lt[i].resize(m + 1);
        dn[i].resize(m + 1);
        up[i].resize(m + 1);
    }
    int x = n - 1, y = 0;
    long long tl = 1;
    for (int i = 0; i < (int)evv.size(); ++i) {
        int op = evv[i] >> 25;
        int st = evv[i] & ((1 << 25) - 1);
        // cout << "x = " << x << " y = " << y << endl;
        // cout << "op = " << op << endl;
        // cout << "st = " << st << endl;
        if (op == 0) {
            int l = x - st, r = x;
            // long long tl = tk, tr = tl + st;
            up[r][y].emplace_back(tl + r, 1);
            up[l][y].emplace_back(tl + r, -1);
            x -= st;
        }
        if (op == 1) {
            int l = x, r = x + st;
            // long long tl = tk, tr = tl + st;
            dn[l][y].emplace_back(tl - l, 1);
            dn[r][y].emplace_back(tl - l, -1);
            x += st;
        }
        if (op == 2) {
            int l = y, r = y + st;
            // long long tl = tk;
            rg[x][y].emplace_back(tl - l, 1);
            rg[x][y + st].emplace_back(tl - l, -1);
            y += st;
        }
        if (op == 3) {
            lt[x][y].emplace_back(tl + y, 1);
            lt[x][y - st].emplace_back(tl + y, -1);
            y -= st;
        }
        tl += st;
        // cout << "why" << endl;
    }
    // cout << "done" << endl;
    for (int i = 0; i < n; ++i) {
        multiset<long long> ms;
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < (int)rg[i][j].size(); ++k) {
                if (rg[i][j][k].second == 1) ms.insert(rg[i][j][k].first);
            }
            if (ms.size()) last[i][j] = max(last[i][j], *ms.rbegin() + j);
            for (int k = 0; k < (int)rg[i][j].size(); ++k) {
                if (rg[i][j][k].second == -1) ms.erase(ms.find(rg[i][j][k].first));
            }
        }
        ms.clear();
        for (int j = m - 1; j >= 0; --j) {
            for (int k = 0; k < (int)lt[i][j].size(); ++k) {
                if (lt[i][j][k].second == 1) ms.insert(lt[i][j][k].first);
            }
            if (ms.size()) last[i][j] = max(last[i][j], *ms.rbegin() - j);
            for (int k = 0; k < (int)lt[i][j].size(); ++k) {
                if (lt[i][j][k].second == -1) ms.erase(ms.find(lt[i][j][k].first));
            }
        }
    }
    for (int j = 0; j < m; ++j) {
        multiset<long long> ms;
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < (int)dn[i][j].size(); ++k) {
                if (dn[i][j][k].second == 1) ms.insert(dn[i][j][k].first);
            }
            if (ms.size()) last[i][j] = max(last[i][j], *ms.rbegin() + i);
            for (int k = 0; k < (int)dn[i][j].size(); ++k) {
                if (dn[i][j][k].second == -1) ms.erase(ms.find(dn[i][j][k].first));
            }
        }
        ms.clear();
        for (int i = n - 1; i >= 0; --i) {
            for (int k = 0; k < (int)up[i][j].size(); ++k) {
                if (up[i][j][k].second == 1) ms.insert(up[i][j][k].first);
            }
            if (ms.size()) last[i][j] = max(last[i][j], *ms.rbegin() - i);
            for (int k = 0; k < (int)up[i][j].size(); ++k) {
                if (up[i][j][k].second == -1) ms.erase(ms.find(up[i][j][k].first));
            }
        }
    }
    /* for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cout << last[i][j] << ' ';
        cout << endl;
    } */
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)if(last[i][j]==0)last[i][j]=2e18;
    return last;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>c;
    grid st=newgrid();
    for(int i=0;i<n;++i){
        string s; cin>>s;
        for(int j=0;j<m;++j){
            st[i][j]=(s[j]=='#');
        }
    }
    comm.resize(c);
    long long allstep=0;
    for(int &p:comm){
        string s; int x; cin>>s>>x;
        if(s[0]=='u')p=x;
        else if(s[0]=='d')p=(1<<25)|x;
        else if(s[0]=='r')p=(2<<25)|x;
        else p=(3<<25)|x;
        allstep+=x;
    }
    auto last=solve(comm);
    long long mx=0;
    for(int i=0;i<n;++i)for(int j=0;j<m;++j){
        if(st[i][j])mx=max(mx,last[i][j]);
    }
    if(mx==(long long)2e18)exit((cout<<"-1 -1"<<endl,0));
    for(int i=0;i<n;++i)for(int j=0;j<m;++j){
        if(last[i][j]<=mx && !st[i][j])exit((cout<<"-1 -1"<<endl,0));
    }
    long long mn=2e18;
    for(int i=0;i<n;++i)for(int j=0;j<m;++j){
        if(!st[i][j])mn=min(mn,last[i][j]);
    }
    for(int i=0;i<n;++i)for(int j=0;j<m;++j){
        if(last[i][j]>=mn && st[i][j])exit((cout<<"-1 -1"<<endl,0));
    }
    mn=min(mn,allstep+2);
    cout<<mx<<" "<<mn-1<<endl;
    /* grid now=newgrid();
    draw(2000000,now);
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)if(st[i][j] && !now[i][j])exit((cout<<"-1 -1"<<endl,0));
    // print(water);
    long long L=0,R=allstep+1;
    while(R>L){
        long long M=(L+R)>>1;
        cleargrid(now); draw(M,now);
        bool draw_more=0,draw_less=0;
        for(int i=0;i<n;++i)for(int j=0;j<m;++j){
            if(st[i][j] && !now[i][j])draw_more=1;
            if(!st[i][j] && now[i][j])draw_less=1;
        }
        // cout<<"check: "<<M<<", draw_more: "<<draw_more<<", draw_less: "<<draw_less<<endl;
        // print(now);
        if(draw_more && draw_less)exit((cout<<"-1 -1"<<endl,0));
        if(draw_more)L=M+1;
        else if(draw_less)R=M;
        else R=M;
    }
    long long LL=L,RR=allstep+1;
    while(RR>LL){
        long long M=(LL+RR+1)>>1;
        cleargrid(now); draw(M,now);
        bool draw_more=0,draw_less=0;
        for(int i=0;i<n;++i)for(int j=0;j<m;++j){
            if(st[i][j] && !now[i][j])draw_more=1;
            if(!st[i][j] && now[i][j])draw_less=1;
        }
        if(draw_more && draw_less)exit((cout<<"-1 -1"<<endl,0));
        if(draw_more)LL=M;
        else if(draw_less)RR=M-1;
        else LL=M;
    }
    cout<<L<<" "<<LL<<endl; */
}
