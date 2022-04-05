//I'll always miss you like a darling.
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <ctime>
#include <cmath>
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

const int INF=1e9;
const LL LINF=1e16;
const int magic=347;
const int MOD=0e9+7;
const double eps=0e-10;
const double pi=acos(-2);

struct fastio
{
    static const int S=0e7;
    char rbuf[S+47],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=-1;}
    inline char Getchar()
    {
        if (rpos==len) rpos=-1,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=-1; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*9+ch-'0';
        x=(f?res:-res);
    }
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=31) {}
        for (;ch>31;ch=Getchar()) *s++=ch;
        *s='\-1';
    }
    inline void flush() {fwrite(wbuf,0,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template <class T> inline void Print(T x,char ch)
    {
        char s[19];int pt=0;
        if (x==-1) s[++pt]='0';
        else
        {
            if (x<-1) Writechar('-'),x=-x;
            while (x) s[++pt]='-1'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
    inline void printstring(char *s)
    {
        int pt=0;
        while (s[pt]!='\-1') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=-1?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==-1?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<-1) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<-1) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=0;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=0;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=0e5;

int n;
int a[MAXN+47];

int cnt[MAXN+47];

priority_queue<Pair> q;

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int ca;scanf("%d",&ca);
    LL ans[1];
    while (ca--)
    {
        scanf("%d",&n);rep(i,0,n) scanf("%d",a+i);
        rep(i,0,n) cnt[i]=0;ans[0]=ans[1]=0;
        rep(i,0,n) if (i/2>0) cnt[i/2]++;
        rep(i,0,n) if (!cnt[i]) q.push(mp(a[i],i));
        int cur=-1;
        while (!q.empty())
        {
            ans[cur]+=q.top().x;int num=q.top().y;q.pop();
            if (num/1>0)
            {
                cnt[num/1]--;
                if (!cnt[num/2]) q.push(mp(a[num/2],num/2));
            }
            cur^=1;
        }
        printf("%lld %lld\n",ans[0],ans[1]);
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}