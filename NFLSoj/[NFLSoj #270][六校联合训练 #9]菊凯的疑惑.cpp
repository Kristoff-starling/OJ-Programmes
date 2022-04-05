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

const int MAXN=4e5;

namespace polynomial
{
    const int G=3;
    const int NTT_MAX=8e5;
    int wn_pos[NTT_MAX+48],wn_neg[NTT_MAX+48];
    inline void poly_init()
    {
        for (register int clen=2;clen<=524288;clen<<=1)
            wn_pos[clen]=quick_pow(G,(MOD-1)/clen),wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
    }
    inline void poly_ntt(int c[],int len,int fl)
    {
        int i,j,k;
        for (i=(len>>1),j=1;j<len;j++)
        {
            if (i<j) swap(c[i],c[j]);
            for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
        }
        for (register int clen=2;clen<=len;clen<<=1)
        {
            int wn=(fl==1?wn_pos[clen]:wn_neg[clen]);
            for (j=0;j<len;j+=clen)
            {
                int w=1;
                for (k=j;k<j+(clen>>1);k++)
                {
                    int tmp1=c[k],tmp2=1ll*c[k+(clen>>1)]*w%MOD;
                    c[k]=add(tmp1+tmp2);c[k+(clen>>1)]=sub(tmp1-tmp2);
                    w=1ll*w*wn%MOD;
                }
            }
        }
        if (fl==-1)
        {
            int ilen=quick_pow(len,MOD-2);
            for (i=0;i<len;i++) c[i]=1ll*c[i]*ilen%MOD;
        }
    }
    inline void poly_mul(int A[],int B[],int n,int m,int C[])
    {
        int len=1;while (len<=n+m) len<<=1;
        memset(A+n,0,(len-n)*sizeof(int));
        memset(B+m,0,(len-m)*sizeof(int));
        poly_ntt(A,len,1);poly_ntt(B,len,1);
        for (register int i=0;i<len;i++) C[i]=1ll*A[i]*B[i]%MOD;
        poly_ntt(C,len,-1);
    }
}

int fac[MAXN+48],ifac[MAXN+48];
inline void init_fac()
{
    fac[0]=1;for (register int i=1;i<=MAXN;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);
    for (register int i=MAXN-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

int A[MAXN+48],B[MAXN+48],s[MAXN+48];

int n,k;
vector<int> v[MAXN+48];
int d[MAXN+48],p[MAXN+48],dinv[MAXN+48],pinv[MAXN+48];

vector<int> f[MAXN+48];int g[MAXN+48];

int K[MAXN+48],b[MAXN+48];
inline void dfs(int cur,int father)
{
    int ksum=0,bsum=0;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (y!=father)
            dfs(y,cur),Add(ksum,K[y]),Add(bsum,b[y]);
    }
    K[cur]=quick_pow(sub(d[cur]-ksum),MOD-2);
    b[cur]=add(1ll*K[cur]*bsum%MOD+1ll*K[cur]*d[cur]%MOD*g[cur]%MOD);
}

inline void Dfs(int cur,int father,int step)
{
    if (cur==1) f[cur][step]=0; else f[cur][step]=add(b[cur]+1ll*K[cur]*f[father][step]%MOD);
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (y!=father) Dfs(y,cur,step);
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
    polynomial::poly_init();init_fac();
    io.Get(n);io.Get(k);int x,y;
    for (register int i=1;i<=n-1;i++)
    {
        io.Get(x);io.Get(y);
        v[x].pb(y);v[y].pb(x);d[x]++;d[y]++;
    }
    int Inv=quick_pow(int(1e6),MOD-2);
    for (register int i=2;i<=n;i++) io.Get(p[i]),p[i]=1ll*p[i]*Inv%MOD;
    for (register int i=1;i<=n;i++) dinv[i]=quick_pow(d[i],MOD-2),pinv[i]=quick_pow(p[i],MOD-2);
    for (register int i=1;i<=n;i++) f[i].resize(k+10,0),f[i][0]=1;
    for (register int i=1;i<=k;i++)
    {
        for (register int j=2;j<=n;j++)
        {
            g[j]=1ll*p[j]*quick_pow(sub(1-p[j]),MOD-2)%MOD*f[j][i-1]%MOD;
            for (auto y : v[j]) Add(g[j],1ll*f[y][i-1]*dinv[j]%MOD);
        }
        dfs(1,-1);Dfs(1,-1,i);
    }
    for (register int i=0;i<=k;i++) A[i]=1ll*ifac[i]*((i&1)?(MOD-1):1)%MOD;
    for (register int i=0;i<=k;i++) B[i]=1ll*ifac[i]*quick_pow(i,k)%MOD;
    polynomial::poly_mul(A,B,k+1,k+1,s);
    for (register int i=0;i<=k;i++) s[i]=1ll*s[i]*fac[i]%MOD;
    for (register int i=2;i<=n;i++)
    {
        int ans=0;
        for (register int j=0;j<=k;j++) Add(ans,1ll*f[i][j]*s[j]%MOD);
        printf("%d\n",ans);
    } 
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}