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
const int magic=967;
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

const int MAXN=1e5;

int n,q,a[MAXN+48];LL sum[MAXN+48];
int N;

struct Seg
{
    int dx;LL dy;
    Seg () {}
    inline Seg(int _x,LL _y) {dx=_x;dy=_y;}
    inline bool operator < (const Seg &other) const {return dy*other.dx<other.dy*dx;}
    inline void print()
    {
        LL up=dy,down=dx;
        if (up==0) {puts("0/1");return;}
        LL g=gcd(myabs(up),myabs(down));
        up/=g;down/=g;
        if (down<0) up=-up,down=-down;
        printf("%lld/%lld\n",up,down);
    }
};

inline Seg gen(pLL pt1,pLL pt2) {return Seg(pt1.x-pt2.x,pt1.y-pt2.y);}

Seg f[110][MAXN+1];
pLL sta[MAXN+48];int stot;
int bel[MAXN+48];

inline pLL query(pLL cur)
{
    int l=1,r=stot;
    while (l<=r)
    {
        int mid=(l+r)>>1;
        if (mid<stot && gen(cur,sta[mid])<gen(cur,sta[mid+1])) l=mid+1; else r=mid-1;
    }
    return sta[l];
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&q);int l,r;
    for (register int i=1;i<=n;i++) scanf("%d",a+i),sum[i]=sum[i-1]+a[i];
    N=n/magic;if (n%magic) N++;
    for (register int i=1,id=1;i<=n;i++)
    {
        bel[i]=id;
        if (i%magic==0) id++;
    }
    for (register int i=1;i<=N;i++)
    {
        int st=(i-1)*magic+1;
        if (st!=n)
        {
            stot=2;sta[1]=mp(st,sum[st-1]);sta[2]=mp(st+1,sum[st]);
            f[i][st+1]=gen(mp(st,sum[st-1]),mp(st+1,sum[st+1]));
            for (register int j=st+2;j<=n;j++)
            {
                f[i][j]=f[i][j-1];
                pLL chosen=query(mp(j,sum[j]));
                if (f[i][j]<gen(chosen,mp(j,sum[j]))) f[i][j]=gen(chosen,mp(j,sum[j]));
                sta[++stot]=mp(j,sum[j-1]);
                while (stot>=3 && gen(sta[stot-1],sta[stot])<gen(sta[stot-2],sta[stot-1])) sta[stot-1]=sta[stot],stot--;
            }
        }
        int ed=((i==N)?n:i*magic);
        if (ed!=1)
        {
            stot=2;sta[1]=mp(ed,sum[ed]);sta[2]=mp(ed-1,sum[ed-1]);
            f[i][ed-1]=gen(mp(ed-1,sum[ed-2]),mp(ed,sum[ed]));
            for (register int j=ed-2;j>=1;j--)
            {
                f[i][j]=f[i][j+1];
                pLL chosen=query(mp(j,sum[j-1]));
                if (f[i][j]<gen(mp(j,sum[j-1]),chosen)) f[i][j]=gen(mp(j,sum[j-1]),chosen);
                sta[++stot]=mp(j,sum[j]);
                while (stot>=3 && gen(sta[stot],sta[stot-1])<gen(sta[stot-1],sta[stot-2])) sta[stot-1]=sta[stot],stot--;
            }
        }
    }
    while (q--)
    {
        scanf("%d%d",&l,&r);
        if (bel[l]+1>=bel[r])
        {
            stot=2;sta[1]=mp(r,sum[r]);sta[2]=mp(r-1,sum[r-1]);
            Seg ans=gen(mp(r-1,sum[r-2]),mp(r,sum[r]));
            for (register int i=r-2;i>=l;i--)
            {
                pLL chosen=query(mp(i,sum[i-1]));
                if (ans<gen(mp(i,sum[i-1]),chosen)) ans=gen(mp(i,sum[i-1]),chosen);
                sta[++stot]=mp(i,sum[i]);
                while (stot>=3 && gen(sta[stot],sta[stot-1])<gen(sta[stot-1],sta[stot-2])) sta[stot-1]=sta[stot],stot--; 
            }
            ans.print();continue;
        }
        Seg ans=f[bel[l]+1][r];
        if (ans<f[bel[r]-1][l]) ans=f[bel[r]-1][l];
        int st=(bel[r]-1)*magic+1;
        stot=1;sta[1]=mp(r,sum[r]);
        for (register int i=r-1;i>=st;i--)
        {
            sta[++stot]=mp(i,sum[i]);
            while (stot>=3 && gen(sta[stot],sta[stot-1])<gen(sta[stot-1],sta[stot-2])) sta[stot-1]=sta[stot],stot--;
        }
        int ed=magic*bel[l];
        for (register int i=l;i<=ed;i++)
        {
            pLL chosen=query(mp(i,sum[i-1]));
            if (ans<gen(mp(i,sum[i-1]),chosen)) ans=gen(mp(i,sum[i-1]),chosen);
        }
        ans.print();
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}