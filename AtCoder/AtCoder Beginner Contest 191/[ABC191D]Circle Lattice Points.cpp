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
const double eps=1e-14;
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

LL XX,YY,RR;

/*
LL bsearch1(long double y,LL rem)
{
    LL l=ceil(y),r=ceil(y)+100048,mid,ans=-1e18;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if ((YY-mid*10000)*(YY-mid*10000)<=rem) ans=mid,l=mid+1; else r=mid-1;
    }
    return ans;
}

LL bsearch2(long double y,LL rem)
{
    LL l=floor(y)-100048,r=floor(y),mid,ans=-1e18;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if ((YY-mid*10000)*(YY-mid*10000)<=rem) ans=mid,r=mid-1; else l=mid+1;
    }
    return ans;
}
*/

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    long double x,y,r;cin>>x>>y>>r;
    XX=x*10000;YY=y*10000;RR=r*10000;
    LL L=int(x)-100048,R=int(x)+100048;
    LL ans=0;
    for (LL i=L;i<=R;i++)
    {
        if (RR*RR-(XX-i*10000)*(XX-i*10000)<0) continue;
        long double up=y+sqrt((r+eps)*(r+eps)-(long double)(x-i)*(x-i));
        long double down=y-sqrt((r+eps)*(r+eps)-(long double)(x-i)*(x-i));
        ans+=floor(up)-ceil(down)+1;
        /*
        LL res=RR*RR-(XX-i*10000)*(XX-i*10000);
        if (res<0) continue;
        LL yy=bsearch1(y,res);if (yy!=-1e18) ans+=(yy-ceil(y)+1);
        yy=bsearch2(y,res);if (yy!=-1e18) ans+=(floor(y)-yy+1);
        if ((int(y))*10000==int(y*10000)) ans--;
        */
    }
    printf("%lld\n",ans);
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}