

#include<bits/stdc++.h>
using namespace std;

struct token{
    int pos,route;
    char sym;
    bool win;
    void init(char c){
        sym=c;
        route=4;
    }
    void reset_begin(){
        pos=0;
        route=4;
    }
    void walk(int x){
        if(win)return;
        // cout<<"walk "<<x<<" route: "<<route<<" at "<<pos<<endl;
        if(route==4){
            pos+=x;
            if(pos>20){
                win=1;
            }
        }
        else if(route==3){
            while(x--){
                if(pos<5)++pos;
                else if(pos==5)pos=21;
                else if(pos>=21 && pos<=24)++pos;
                else if(pos==25)pos=15;
                else if(pos==20){
                    win=1;
                    break;
                }
                else ++pos;
            }
        }
        else if(route==2){
            while(x--){
                if(pos<10)++pos;
                else if(pos==10)pos=26;
                else if(pos==26)pos=27;
                else if(pos==27)pos=23;
                else if(pos==23)pos=28;
                else if(pos==28)pos=29;
                else if(pos==29)pos=20;
                else{
                    win=1;
                    break;
                }
            }
        }
        else{
            while(x--){
                if(pos<5)++pos;
                else if(pos==5)pos=21;
                else if(pos==21)pos=22;
                else if(pos==22)pos=23;
                else if(pos==23)pos=28;
                else if(pos==28)pos=29;
                else if(pos==29)pos=20;
                else{
                    win=1;
                    break;
                }
            }
        }
    }
    void update_route(){
        if(pos==5){
            route=3;
        }
        else if(pos==10){
            route=2;
        }
        else if(route==3 && pos==23){
            route=1;
        }
    }
} a[4],A[4];

void init(){
    a[0].init('a');
    a[1].init('b');
    a[2].init('c');
    a[3].init('d');
    A[0].init('A');
    A[1].init('B');
    A[2].init('C');
    A[3].init('D');
}

int getstep(string &yut){
    int cF=0;
    for(char c:yut)if(c=='F')++cF;
    if(cF==0)cF=5;
    return cF;
}

bool is_small(char c){
    return c>='a' && c<='d';
}

string ans[32];

void place_token(char c,int pos,int ox,int oy){
    int x=-1,y=-1;
#define c(q,w,e) if(pos==q)x=w,y=e
    c(1,24,30);
    c(2,18,30);
    c(3,12,30);
    c(4,6,30);
    c(5,0,30);
    c(6,0,24);
    c(7,0,18);
    c(8,0,12);
    c(9,0,6);
    c(10,0,0);
    c(11,6,0);
    c(12,12,0);
    c(13,18,0);
    c(14,24,0);
    c(15,30,0);
    c(16,30,6);
    c(17,30,12);
    c(18,30,18);
    c(19,30,24);
    c(20,30,30);
    c(21,5,25);
    c(22,10,20);
    c(23,15,15);
    c(24,20,10);
    c(25,25,5);
    c(26,5,5);
    c(27,10,10);
    c(28,20,20);
    c(29,25,25);
#undef c
    assert(x!=-1 && y!=-1);
    x+=ox; y+=oy;
    ans[x][y]=c;
}

void place_token(){
    int ofx[4]={0,0,1,1};
    int ofy[4]={0,1,0,1};
    for(int i=0;i<4;++i){
        if(a[i].pos && !a[i].win){
            place_token('a'+i,a[i].pos,ofx[i],ofy[i]);
        }
        if(A[i].pos && !A[i].win){
            place_token('A'+i,A[i].pos,ofx[i],ofy[i]);
        }
    }
}

void build_map(){
    ans[0] ="..----..----..----..----..----..";
    ans[1] ="..    ..    ..    ..    ..    ..";
    ans[2] ="| \\                          / |";
    ans[3] ="|  \\                        /  |";
    ans[4] ="|   \\                      /   |";
    ans[5] ="|    ..                  ..    |";
    ans[6] ="..   ..                  ..   ..";
    ans[7] ="..     \\                /     ..";
    ans[8] ="|       \\              /       |";
    ans[9] ="|        \\            /        |";
    ans[10]="|         ..        ..         |";
    ans[11]="|         ..        ..         |";
    ans[12]="..          \\      /          ..";
    ans[13]="..           \\    /           ..";
    ans[14]="|             \\  /             |";
    ans[15]="|              ..              |";
    ans[16]="|              ..              |";
    ans[17]="|             /  \\             |";
    ans[18]="..           /    \\           ..";
    ans[19]="..          /      \\          ..";
    ans[20]="|         ..        ..         |";
    ans[21]="|         ..        ..         |";
    ans[22]="|        /            \\        |";
    ans[23]="|       /              \\       |";
    ans[24]="..     /                \\     ..";
    ans[25]="..   ..                  ..   ..";
    ans[26]="|    ..                  ..    |";
    ans[27]="|   /                      \\   |";
    ans[28]="|  /                        \\  |";
    ans[29]="| /                          \\ |";
    ans[30]="..    ..    ..    ..    ..    ..";
    ans[31]="..----..----..----..----..----..";
    place_token();
}

int main(){
    init();
    int n; cin>>n; while(n--){
        char tok; cin>>tok;
        string yut; cin>>yut;
        int step=getstep(yut);
        vector<token*> walk;
        int numb=-1;
        if(is_small(tok)){
            numb=tok-'a';
            walk.push_back(&a[numb]);
            if(a[numb].pos)for(int i=0;i<4;++i){
                if(i==numb)continue;
                if(a[numb].pos==a[i].pos)walk.push_back(&a[i]);
            }
        }
        else{
            numb=tok-'A';
            walk.push_back(&A[numb]);
            if(A[numb].pos)for(int i=0;i<4;++i){
                if(i==numb)continue;
                if(A[numb].pos==A[i].pos)walk.push_back(&A[i]);
            }
        }
        for(auto *t:walk){
            t->walk(step);
            t->update_route();
        }
        if(is_small(tok) && !a[numb].win){
            for(int i=0;i<4;++i)if(!A[i].win && A[i].pos==a[numb].pos){
                A[i].reset_begin();
            }
        }
        else if(!is_small(tok) && !A[numb].win){
            for(int i=0;i<4;++i)if(!a[i].win && a[i].pos==A[numb].pos){
                a[i].reset_begin();
            }
        }
        /* build_map();
        for(int i=0;i<32;++i){
            cout<<ans[i]<<'\n';
        }
        cout<<"----------------------------------------------------"<<endl; */
    }
    build_map();
    for(int i=0;i<32;++i){
        cout<<ans[i]<<'\n';
    }
}
