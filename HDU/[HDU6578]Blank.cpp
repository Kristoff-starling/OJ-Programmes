//I'll always miss you like a darling.
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>
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
const int MOD=998244353;
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
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
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
vector<Pair> v[148];

int dp[2][101][101][101];

inline int mymax(int x,int y) {if (x>=y) return x; else return y;}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);int l,r,x;
        rep(i,1,n) v[i].clear();
        rep(i,1,m) scanf("%d%d%d",&l,&r,&x),v[r].pb(mp(l,x));
        bool f=true;
        for (auto item : v[1]) if (item.x==1 && item.y!=1) {f=false;break;}
        if (!f) {puts("0");continue;}
        int cur=0,nxt=1;
        memset(dp,0,sizeof(dp));
        dp[cur][0][0][0]=1;int p[10];
        rep(i,1,n-1)
        {
            rep(p1,0,i-1) rep(p2,0,mymax(0,p1-1)) rep(p3,0,mymax(0,p2-1))
            if (dp[cur][p1][p2][p3])
            {
                //first num
                bool f=true;
                p[1]=i+1;p[2]=p1;p[3]=p2;p[4]=p3;
                for (auto item : v[i+1])
                {
                    int L=item.x,R=i+1,X=item.y;
                    rep(tmp,1,4) if (p[tmp]>=L) X--;
                    if (X!=0) {f=false;break;}
                }
                if (f) Add(dp[nxt][p[2]][p[3]][p[4]],dp[cur][p1][p2][p3]);
                //second num
                f=true;
                p[1]=i+1;p[2]=i;p[3]=p2;p[4]=p3;
                for (auto item : v[i+1])
                {
                    int L=item.x,R=i+1,X=item.y;
                    rep(tmp,1,4) if (p[tmp]>=L) X--;
                    if (X!=0) {f=false;break;}
                }
                if (f) Add(dp[nxt][p[2]][p[3]][p[4]],dp[cur][p1][p2][p3]);
                //third num
                if (p1!=0)
                {
                    f=true;
                    p[1]=i+1;p[2]=i;p[3]=p1;p[4]=p3;
                    for (auto item : v[i+1])
                    {
                        int L=item.x,R=i+1,X=item.y;
                        rep(tmp,1,4) if (p[tmp]>=L) X--;
                        if (X!=0) {f=false;break;}
                    }
                    if (f) Add(dp[nxt][p[2]][p[3]][p[4]],dp[cur][p1][p2][p3]);
                }
                //fourth num
                if (p1!=0 && p2!=0)
                {
                    f=true;
                    p[1]=i+1;p[2]=i;p[3]=p1;p[4]=p2;
                    for (auto item : v[i+1])
                    {
                        int L=item.x,R=i+1,X=item.y;
                        rep(tmp,1,4) if (p[tmp]>=L) X--;
                        if (X!=0) {f=false;break;}
                    }
                    if (f) Add(dp[nxt][p[2]][p[3]][p[4]],dp[cur][p1][p2][p3]);
                }
                dp[cur][p1][p2][p3]=0;
            }
            swap(cur,nxt);
        }
        int ans=0;
        rep(p1,0,n-1) rep(p2,0,mymax(0,p1-1)) rep(p3,0,mymax(0,p2-1))
        {
            int cc=1;if (p1!=0) cc++;if (p2!=0) cc++;if (p3!=0) cc++;
            if (cc==1) Add(ans,1ll*dp[cur][p1][p2][p3]*4%MOD);
            if (cc==2) Add(ans,1ll*dp[cur][p1][p2][p3]*12%MOD);
            if (cc>=3) Add(ans,1ll*dp[cur][p1][p2][p3]*24%MOD);
        }
        printf("%d\n",ans);
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}