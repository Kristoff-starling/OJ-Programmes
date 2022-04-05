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

const int MAXN=1e5;
const int NTT_MAX=8e5;

int n,w[MAXN+48],sum[MAXN+48];

namespace polynomial
{
    const int G=3;
    int wpos[NTT_MAX+48],wneg[NTT_MAX+48];bool done=false;
    inline void poly_init()
    {
        done=true;
        for (register int clen=2;clen<=262144*2;clen<<=1)
            wpos[clen]=quick_pow(G,(MOD-1)/clen),wneg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
    }
    int w[NTT_MAX+48];
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
            int wn=(fl==1?wpos[clen]:wneg[clen]);
            w[0]=1;for (register int i=1;i<=(clen>>1);i++) w[i]=1ll*w[i-1]*wn%MOD;
            for (j=0;j<len;j+=clen)
                for (k=j;k<j+(clen>>1);k++)
                {
                    int tmp1=c[k],tmp2=1ll*c[k+(clen>>1)]*w[k-j]%MOD;
                    c[k]=add(tmp1+tmp2);c[k+(clen>>1)]=sub(tmp1-tmp2);
                }
        }
        if (fl==-1)
        {
            int ilen=quick_pow(len,MOD-2);
            for (i=0;i<len;i++) c[i]=1ll*c[i]*ilen%MOD;
        }
    }
    inline void poly_mul(int A[],int B[],int n,int m)
    {
        if (!done) poly_init();
        int len=1;while (len<=n+m) len<<=1;
        memset(A+n,0,(len-n)*sizeof(int));
        memset(B+m,0,(len-m)*sizeof(int));
        poly_ntt(A,len,1);poly_ntt(B,len,1);
        for (register int i=0;i<len;i++) A[i]=1ll*A[i]*B[i]%MOD;
        poly_ntt(A,len,-1);
    }
}

int tmp[NTT_MAX+48],A[NTT_MAX+48],B[NTT_MAX+48];
inline void solve(int left,int right)
{
    if (left==right)
    {
        memset(tmp,0,(w[left]+1)*sizeof(int));
        tmp[0]=1;tmp[w[left]]=MOD-1;return;
    }
    int mid=(left+right)>>1,N=sum[mid]-sum[left-1]+1,M=sum[right]-sum[mid]+1;
    int len=1;while (len<=N+M) len<<=1;
    int Tmp[len+48];
    solve(left,mid);memcpy(Tmp,tmp,N*sizeof(int));
    solve(mid+1,right);
    memcpy(A,Tmp,N*sizeof(int));memcpy(B,tmp,M*sizeof(int));
    polynomial::poly_mul(A,B,N,M);
    memcpy(tmp,A,len*sizeof(int));
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);for (register int i=1;i<=n;i++) io.Get(w[i]);
    sum[1]=0;for (register int i=2;i<=n;i++) sum[i]=sum[i-1]+w[i];
    solve(2,n);int ans=0;
    for (register int i=0;i<=sum[n];i++) Add(ans,1ll*A[i]*quick_pow(w[1]+i,MOD-2)%MOD);
    ans=1ll*ans*w[1]%MOD;printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}