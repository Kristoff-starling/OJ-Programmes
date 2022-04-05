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

const int MAXN=1000;

int n;
int a[MAXN+48],b[MAXN+48];
int val[MAXN+48],tot;
int N,L[MAXN+48],R[MAXN+48];
int dp[2][1048][548],sum[2][1048];

int c[1048][548];
inline void init_c()
{
    for (register int i=1;i<=N;i++)
    {
        c[i][0]=1;int up=R[i]-L[i]+1,down=1;
        for (register int j=1;j<=n;j++) c[i][j]=1ll*c[i][j-1]*up%MOD*quick_pow(down,MOD-2)%MOD,up--,down++;
    }
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d",&n);
    for (register int i=1;i<=n;i++) scanf("%d%d",a+i,b+i),val[++tot]=a[i],val[++tot]=b[i]+1;
    sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
    N=tot-1;for (register int i=1;i<=N;i++) L[i]=val[i],R[i]=val[i+1]-1;
    init_c();
    int pre=0,cur=1;dp[pre][0][0]=1;
    sum[pre][0]=1;
    for (register int j=1;j<=N;j++)
    {
        sum[pre][j]=sum[pre][j-1];
        for (register int k=1;k<=n;k++)
            Add(sum[pre][j],1ll*dp[pre][j][k]*c[j][k]%MOD);
    }
    for (register int i=1;i<=n;i++)
    {
        memset(dp[cur],0,sizeof(dp[cur]));dp[cur][0][0]=1;
        for (register int j=1;j<=N;j++)
            for (register int k=1;k<=i;k++)
            {
                dp[cur][j][k]=dp[pre][j][k];
                if (a[i]<=L[j] && R[j]<=b[i])
                {
                    if (k==1) Add(dp[cur][j][k],sum[pre][j-1]);
                    else Add(dp[cur][j][k],dp[pre][j][k-1]);
                }
            }
        sum[cur][0]=1;
        for (register int j=1;j<=N;j++)
        {
            sum[cur][j]=sum[cur][j-1];
            for (register int k=1;k<=n;k++)
                Add(sum[cur][j],1ll*dp[cur][j][k]*c[j][k]%MOD);
        }
        cur^=1;pre^=1;
    }
    int ans=0;
    for (register int i=1;i<=N;i++)
        for (register int j=1;j<=n;j++)
            Add(ans,1ll*dp[pre][i][j]*c[i][j]%MOD);
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}