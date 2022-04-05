#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
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
// #define LOCAL true

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

const int MAXN=5e5;

int n,a[MAXN+48];
int lim[MAXN+48],pre[MAXN+48],nxt[MAXN+48];
int sta[MAXN+48],stot;

int dp[MAXN+48],sum[MAXN+48],mark[MAXN+48];

int ST[MAXN+48][21],Log[MAXN+48];

inline void init_ST()
{
    Log[0]=Log[1]=0;
    for (register int i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
    for (register int i=1;i<=n;i++) ST[i][0]=a[i];
    for (register int j=1;j<=20;j++)
        for (register int i=1;i<=n;i++)
        {
            ST[i][j]=ST[i][j-1];
            if (i+(1<<(j-1))<=n) check_min(ST[i][j],ST[i+(1<<(j-1))][j-1]);
        }
}

inline int query(int l,int r)
{
    int k=r-l+1;
    return min(ST[l][Log[k]],ST[r-(1<<Log[k])+1][Log[k]]);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);for (register int i=1;i<=n;i++) io.Get(a[i]);
    a[0]=a[n+1]=INF;
    init_ST();
    for (register int i=1;i<=n;i++)
    {
        int l=1,r=i,ans=i+1,mid;
        while (l<=r)
        {
            mid=(l+r)>>1;
            if (query(mid,i)>i-mid+1) ans=mid,r=mid-1; else l=mid+1;
        }
        lim[i]=ans;
    }
    stot=1;sta[1]=0;
    for (register int i=1;i<=n;i++)
    {
        while (a[sta[stot]]<=a[i]) stot--;
        pre[i]=sta[stot];sta[++stot]=i;
    }
    stot=1;sta[1]=n+1;
    for (register int i=n;i>=1;i--)
    {
        while (a[sta[stot]]<a[i]) stot--;
        nxt[i]=sta[stot];sta[++stot]=i;
    }
    dp[0]=sum[0]=1;memset(mark,0,sizeof(mark));
    int cur=0;
    for (register int i=1;i<=n;i++)
    {
        int l=pre[i]+1,r=nxt[i]-1;
        if (i-l+1<=r-i+1)
        {
            for (register int j=l;j<=i;j++)
            {
                int x=i,y=min(j+a[i]-1,r);
                if (x<=y)
                {
                    Add(mark[x],dp[j-1]);
                    Sub(mark[y+1],dp[j-1]);
                }
            }
        }
        else
        {
            for (register int j=i;j<=r;j++)
            {
                int x=max(l-1,(j-1)-a[i]+1),y=i-1;
                if (x<=y)
                {
                    int val=sum[y];if (x) Sub(val,sum[x-1]);
                    Add(mark[j],val);Sub(mark[j+1],val);
                }
            }
        }
        Add(cur,mark[i]);
        dp[i]=sub(cur-sub(sum[i-1]-(((lim[i]-2>=0)?sum[lim[i]-2]:0))));
        sum[i]=add(sum[i-1]+dp[i]);
    }
    io.Print(dp[n],'\n');
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}