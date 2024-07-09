//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
    static const int S=1e7;
    char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=0;}
    inline char Getchar()
    {
        if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
    }
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=32) {}
        for (;ch>32;ch=Getchar()) *s++=ch;
        *s='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template <class T> inline void Print(T x,char ch)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T mygcd(T x,T y) {return y==0?x:mygcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int n,m;
int pw[48];

struct node
{
    int x,y,c;
    node () {}
    node (int _x,int _y,int _c) {x=_x;y=_y;c=_c;}
};
vector<node> edge;

void print()
{
    puts("YES");
    printf("32 %d\n",m);
    for (auto item : edge) printf("%d %d %d\n",item.x,item.y,item.c);
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    pw[0]=1;rep(i,1,25) pw[i]=pw[i-1]+pw[i-1];
    int l,r;scanf("%d%d",&l,&r);int L,R;
    if (r<=31)
    {
        m=0;
        edge.pb(node(1,32,l));m++;
        int cur=2;rep(i,l+1,r) edge.pb(node(1,cur,1)),edge.pb(node(cur,32,i-1)),m+=2,cur++;
        print();
    }
    else
    {
        L=max(l,31);R=r;m=0;
        int cnt=1,cur=2,curlen=1;
        while (cnt*2<=R-L+1)
        {
            cur++;curlen++;
            REP(i,cur-2,2) edge.pb(node(i,cur,curlen+1-(i-1))),m++,curlen+=pw[i-2];
            edge.pb(node(1,cur,++curlen));m++;
            cnt<<=1;
        }
        int rem=R-L+1-cnt;
        cur++;curlen++;
        REP(i,cur-2,2) if (pw[i-2]<=rem)
        {
            edge.pb(node(i,cur,curlen+1-(i-1)));m++;
            curlen+=pw[i-2];rem-=pw[i-2];
        }
        rep(i,1,cur-1) edge.pb(node(i,i+1,1)),m++;
        edge.pb(node(cur,cur+1,L-30));m++;
        rep(i,cur+1,31) edge.pb(node(i,i+1,1)),m++;
        if (l<=30)
        {
            int ce=30;
            REP(i,cur-1,2) if (pw[i-2]<=ce-l+1 && (ce-pw[i-2]+1-(i-1))>0)
            {
                edge.pb(node(i,32,(ce-pw[i-2]+1-(i-1))));m++;
                ce-=pw[i-2]; 
            }
            if (ce>=l)
            {
                REP(i,32,32-(ce-l)) edge.pb(node(1,i,l)),m++;
            }
        }
        print();
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}