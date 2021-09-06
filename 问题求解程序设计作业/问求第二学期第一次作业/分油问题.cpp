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

int A,B,C,K;

int dist[101][101][101];
int q[5000048],head,tail;
bool flag=false;

void bfs()
{
    rep(i,0,A) rep(j,0,B) rep(k,0,C) dist[i][j][k]=INF;
    dist[A][0][0]=0;head=1;tail=0;q[++tail]=A;q[++tail]=0;q[++tail]=0;
    while (head<=tail)
    {
        int curA=q[head++],curB=q[head++],curC=q[head++],toA,toB,toC,delta;
        if (curA==K || curB==K || curC==K)
        {
            printf("yes\n%d\n",dist[curA][curB][curC]);
            flag=true;return;
        }
        //A->B
        toC=curC;delta=min(B-curB,curA);toA=curA-delta;toB=curB+delta;
        if (dist[toA][toB][toC]>=INF) dist[toA][toB][toC]=dist[curA][curB][curC]+1,q[++tail]=toA,q[++tail]=toB,q[++tail]=toC;
        //A->C
        toB=curB;delta=min(C-curC,curA);toA=curA-delta;toC=curC+delta;
        if (dist[toA][toB][toC]>=INF) dist[toA][toB][toC]=dist[curA][curB][curC]+1,q[++tail]=toA,q[++tail]=toB,q[++tail]=toC;
        //B->A
        toC=curC;delta=min(A-curA,curB);toB=curB-delta;toA=curA+delta;
        if (dist[toA][toB][toC]>=INF) dist[toA][toB][toC]=dist[curA][curB][curC]+1,q[++tail]=toA,q[++tail]=toB,q[++tail]=toC;
        //B->C
        toA=curA;delta=min(C-curC,curB);toB=curB-delta;toC=curC+delta;
        if (dist[toA][toB][toC]>=INF) dist[toA][toB][toC]=dist[curA][curB][curC]+1,q[++tail]=toA,q[++tail]=toB,q[++tail]=toC;
        //C->A
        toB=curB;delta=min(A-curA,curC);toC=curC-delta;toA=curA+delta;
        if (dist[toA][toB][toC]>=INF) dist[toA][toB][toC]=dist[curA][curB][curC]+1,q[++tail]=toA,q[++tail]=toB,q[++tail]=toC;
        //C->B
        toA=curA;delta=min(B-curB,curC);toC=curC-delta;toB=curB+delta;
        if (dist[toA][toB][toC]>=INF) dist[toA][toB][toC]=dist[curA][curB][curC]+1,q[++tail]=toA,q[++tail]=toB,q[++tail]=toC;
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d%d%d",&A,&B,&C,&K);
    bfs();
    if (!flag) puts("no");
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}