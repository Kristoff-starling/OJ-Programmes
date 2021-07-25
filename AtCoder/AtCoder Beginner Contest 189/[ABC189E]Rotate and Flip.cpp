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

struct Matrix
{
    LL b[5][5];
    void init()
    {
        memset(b,0,sizeof(b));
        b[1][1]=b[2][2]=1;
    }
    Matrix operator + (Matrix other)
    {
        Matrix res;memset(res.b,0,sizeof(res.b));
        rep(i,1,2) rep(j,1,2) res.b[i][j]+=b[i][j]+other.b[i][j];
        return res;
    }
    Matrix operator * (Matrix other)
    {
        Matrix res;memset(res.b,0,sizeof(res.b));
        rep(i,1,2) rep(j,1,2) rep(k,1,2)
            res.b[i][j]+=b[i][k]*other.b[k][j];
        return res;
    }
}clo,cclo,X,Y,coef,ad;

const int MAXN=2e5;

int n,m,q;
LL xx[MAXN+48],yy[MAXN+48];

LL ope[MAXN+48],p[MAXN+48];

struct node
{
    LL A,B,num;
    bool operator < (const node &other) const {return A<other.A;}
}s[MAXN+48];

pLL ans[MAXN+48];

Matrix Make(LL x,LL y)
{
    Matrix res;memset(res.b,0,sizeof(res.b));
    res.b[1][1]=x;res.b[2][1]=y;
    return res;
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    clo.b[1][1]=0;clo.b[1][2]=1;clo.b[2][1]=-1;clo.b[2][2]=0;
    cclo.b[1][1]=0;cclo.b[1][2]=-1;cclo.b[2][1]=1;cclo.b[2][2]=0;
    X.b[1][1]=-1;X.b[1][2]=0;X.b[2][1]=0;X.b[2][2]=1;
    Y.b[1][1]=1;Y.b[1][2]=0;Y.b[2][1]=0;Y.b[2][2]=-1;
    coef.init();memset(ad.b,0,sizeof(ad.b));
    scanf("%d",&n);rep(i,1,n) scanf("%lld%lld",xx+i,yy+i);
    scanf("%d",&m);
    rep(i,1,m)
    {
        scanf("%lld",ope+i);
        if (ope[i]==3 || ope[i]==4) scanf("%lld",p+i);
    }
    scanf("%d",&q);rep(i,1,q) scanf("%lld%lld",&s[i].A,&s[i].B),s[i].num=i;
    sort(s+1,s+q+1);int pt=1;
    rep(i,0,m)
    {
        if (i)
        {
            if (ope[i]==1) coef=clo*coef,ad=clo*ad;
            if (ope[i]==2) coef=cclo*coef,ad=cclo*ad;
            if (ope[i]==3) coef=X*coef,ad=X*ad,ad=ad+Make(p[i]*2,0);
            if (ope[i]==4) coef=Y*coef,ad=Y*ad,ad=ad+Make(0,p[i]*2);
        }
        while (pt<=q && s[pt].A==i)
        {
            Matrix res=coef*Make(xx[s[pt].B],yy[s[pt].B])+ad;
            ans[s[pt].num].x=res.b[1][1];ans[s[pt].num].y=res.b[2][1];
            pt++;
        }
    }
    rep(i,1,q) printf("%lld %lld\n",ans[i].x,ans[i].y);
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}