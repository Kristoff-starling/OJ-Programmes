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

int print(int l,int r)
{
    printf("? %d %d\n",l,r);
    fflush(stdout);
    int res;scanf("%d",&res);return res;
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    cerr<<"Running..."<<endl;
#endif
    int n;scanf("%d",&n);
    int pos=print(1,n);int l=1,r=n;
    while (r-l+1>=4)
    {
        int mid=(l+r)>>1;
        if (l<=pos && pos<=r)
        {
            if (pos<=mid)
            {
                int res=print(l,mid);
                if (res==pos) r=mid; else l=mid+1;
            }
            else
            {
                int res=print(mid+1,r);
                if (res==pos) l=mid+1; else r=mid;
            }
        }
        else
        {
            if (pos<l)
            {
                int res=print(pos,mid);
                if (res==pos) r=mid; else l=mid+1;
            }
            else
            {
                int res=print(mid+1,pos);
                if (res==pos) l=mid+1; else r=mid;
            }
        }
    }
    if (l==r) printf("! %d\n",l);
    else if (l+1==r)
    {
        int res=print(l,r),ans=l+r-res;
        printf("! %d\n",ans);
    }
    else
    {
        int res=print(l,r);
        if (res==l)
        {
            int rres=print(l+1,r),ans=l+1+r-rres;
            printf("! %d\n",ans);
        }
        else if (res==r)
        {
            int rres=print(l,r-1),ans=l+r-1-rres;
            printf("! %d\n",ans);
        }
        else
        {
            int rres=print(l,r-1);
            if (rres==r-1) printf("! %d\n",l); else printf("! %d\n",r);
        }
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}