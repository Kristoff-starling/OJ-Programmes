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

const int MAXN=1e6;

char S[MAXN+48],T[MAXN+48];
int len1,len2,n,s,t,cnta,cntb,cntc,cntd;

int fac[MAXN+48],ifac[MAXN+48],pw[MAXN+48];
int mu[MAXN+48],prime[MAXN+48],tot;bool isprime[MAXN+48];
inline void init()
{
    fac[0]=1;for (register int i=1;i<=MAXN;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);
    for (register int i=MAXN-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
    pw[0]=1;for (register int i=1;i<=MAXN;i++) pw[i]=add(pw[i-1]+pw[i-1]);
    memset(isprime,true,sizeof(isprime));tot=0;mu[1]=1;
    for (register int i=2;i<=MAXN;i++)
    {
        if (isprime[i]) prime[++tot]=i,mu[i]=-1;
        for (register int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) {mu[i*prime[j]]=0;break;} else mu[i*prime[j]]=-mu[i];
        }
    }
    for (register int i=1;i<=MAXN;i++) if (mu[i]<0) mu[i]+=MOD;
}

inline int C(int x,int y)
{
    if (x<y || x<0) return 0;
    return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}

int ans=0,valueg=0;
inline void doit(int coef)
{
    valueg=0;
    for (register int g=1;g<=n;g++)
    {
        int curans=0;
        for (register int d=1;d*g<=n;d++) Add(curans,1ll*(n/g/d)*(n/g/d)%MOD*mu[d]%MOD);
        Add(valueg,1ll*curans*pw[g]%MOD);
    }
    Add(ans,1ll*valueg*coef%MOD);
}

inline void doit2()
{
    int coef=1;
    for (register int i=1;i<=len1;i++)
    {
        if (S[i]!='?' && T[i]!='?' && S[i]!=T[i]) return;
        if (S[i]=='?' && T[i]=='?') coef=1ll*coef*2%MOD;
    }
    int sum=0;
    for (register int i=1;i<=n;i++) Add(sum,pw[i]);
    sum=1ll*sum*sum%MOD;
    Add(ans,1ll*coef*sum%MOD);
    Sub(ans,1ll*coef*valueg);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%s%s%d",S+1,T+1,&n);len1=strlen(S+1);len2=strlen(T+1);init();
    s=cnta=cntb=0;for (register int i=1;i<=len1;i++) s+=(S[i]=='?'),cnta+=(S[i]=='A'),cntb+=(S[i]=='B');
    t=cntc=cntd=0;for (register int i=1;i<=len2;i++) t+=(T[i]=='?'),cntc+=(T[i]=='A'),cntd+=(T[i]=='B');
    for (register int i=-t;i<=s;i++)
    {
        int delta1=cnta-cntc+i,delta2=cntb-cntd+(s-i-t);
        if (delta1==0 && delta2==0) {doit(C(s+t,s-i));continue;}
        if (1ll*delta1*delta2>=0) continue;
        int coef=C(s+t,s-i);
        delta1=(delta1<0?-delta1:delta1);delta2=(delta2<0?-delta2:delta2);
        int g=gcd(delta1,delta2);delta1/=g;delta2/=g;
        Add(ans,1ll*coef*(pw[n/max(delta1,delta2)+1]-2)%MOD);
    }
    if (cnta+cntb+s==cntc+cntd+t) doit2();
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}