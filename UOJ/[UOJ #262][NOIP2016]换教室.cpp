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

const int MAXV=300;
const int MAXN=2000;

int n,m,v,e;

int dist[MAXV+48][MAXV+48];
inline void floyd()
{
    for (register int k=1;k<=v;k++)
        for (register int i=1;i<=v;i++)
            for (register int j=1;j<=v;j++)
                if (i!=j && i!=k && j!=k && dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
}

int c[MAXN+48],d[MAXN+48];double k[MAXN+48];

double dp[MAXN+48][MAXN+48][2];

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d%d%d",&n,&m,&v,&e);
    for (register int i=1;i<=n;i++) scanf("%d",c+i);
    for (register int i=1;i<=n;i++) scanf("%d",d+i);
    for (register int i=1;i<=n;i++) scanf("%lf",k+i);
    memset(dist,0x3f,sizeof(dist));int x,y,C;
    for (register int i=1;i<=v;i++) dist[i][i]=0;
    for (register int i=1;i<=e;i++)
    {
        scanf("%d%d%d",&x,&y,&C);
        dist[x][y]=dist[y][x]=min(dist[x][y],C);
    }
    floyd();
    for (register int i=1;i<=n;i++)
        for (register int j=0;j<=m;j++)
            for (register int p=0;p<=1;p++)
                dp[i][j][p]=1e9;
    memset(dp[1],0,sizeof(dp[1]));
    for (register int i=2;i<=n;i++)
        for (register int j=0;j<=m;j++)
            for (register int sta=0;sta<=1;sta++)
                if (j-sta>=0)
                    for (register int psta=0;psta<=1;psta++)
                        if (j-sta-psta>=0)
                        {
                            //p: probability to change 
                            double p1=(psta==1?k[i-1]:0),p2=(sta==1?k[i]:0);
                            check_min(dp[i][j][sta],dp[i-1][j-sta][psta]+double(1.0-p1)*double(1.0-p2)*dist[c[i-1]][c[i]]+double(1.0-p1)*p2*dist[c[i-1]][d[i]]+p1*double(1.0-p2)*dist[d[i-1]][c[i]]+p1*p2*dist[d[i-1]][d[i]]);
                        }
    double ans=INF;
    for (register int i=0;i<=m;i++) check_min(ans,dp[n][i][0]),check_min(ans,dp[n][i][1]);
    printf("%.2lf\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
