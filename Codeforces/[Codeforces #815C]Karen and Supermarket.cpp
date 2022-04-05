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

const int MAXN=5000;

int n,b;
int c[MAXN+48],d[MAXN+48];
vector<int> v[MAXN+48];

LL dp[MAXN+48][MAXN+48][2],dp2[2][MAXN+48][2];int sz[MAXN+48];
inline void dfs(int cur)
{
    sz[cur]=1;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        dfs(y);sz[cur]+=sz[y];
    }
    for (register int j=0;j<=sz[cur];j++) dp[cur][j][0]=dp[cur][j][1]=LINF;
    for (register int i=0;i<=1;i++)
        for (register int j=0;j<=sz[cur];j++)
            dp2[i][j][0]=dp2[i][j][1]=LINF;
    dp2[0][0][0]=0;int cu=0,nxt=1;
    int cursz=0,cc=0;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        ++cc;int y=v[cur][i];
        for (register int j=0;j<=sz[cur];j++) dp2[nxt][j][0]=dp2[nxt][j][1]=LINF;
        for (register int j=0;j<=cursz;j++)
            for (register int psta=0;psta<=1;psta++)
                if (dp2[cu][j][psta]<LINF)
                    for (register int k=0;k<=sz[y];k++)
                        for (register int sta=0;sta<=1;sta++)
                            check_min(dp2[nxt][j+k][psta|sta],dp2[cu][j][psta]+dp[y][k][sta]);
        cursz+=sz[y];cu^=1;nxt^=1;
    }
    for (register int j=0;j<=sz[cur]-1;j++)
    {
        //from 0, cur not chosen
        check_min(dp[cur][j][0],dp2[cu][j][0]);
        //from 0, cur chosen, not discounted
        check_min(dp[cur][j+1][0],dp2[cu][j][0]+c[cur]);
        //from 0, cur chosen and discounted
        check_min(dp[cur][j+1][1],dp2[cu][j][0]+c[cur]-d[cur]);
        //from 1, cur chosen and discounted
        check_min(dp[cur][j+1][1],dp2[cu][j][1]+c[cur]-d[cur]);
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
    io.Get(n);io.Get(b);int x;
    for (register int i=1;i<=n;i++)
    {
        io.Get(c[i]);io.Get(d[i]);
        if (i>1) io.Get(x),v[x].pb(i);
    }
    dfs(1);
    int ans;
    for (register int j=1;j<=n;j++) check_min(dp[1][j][0],dp[1][j][1]);
    for (ans=1;ans<=n;ans++) if (dp[1][ans][0]>b) break;
    printf("%d\n",ans-1);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}