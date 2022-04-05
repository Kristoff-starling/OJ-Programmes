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

int n,X,Y;

struct Range
{
    int l,r;
    Range () {}
    inline Range(int L,int R) {l=L;r=R;}
    inline void clear() {l=0;r=0;}
    inline Range operator + (Range other) {return Range(l+other.l,r+other.r);}
    inline Range operator - (Range other) {return Range(l-other.r,r-other.l);}
    inline Range operator * (int t)
    {
        if (t>0) return Range(l*t,r*t);
        else return Range(r*t,l*t);
    }
}a[148];
pair<Range,Range> Move[148];int tot;

char type[148];

int dx[]={0,1,0,-1},dy[]={1,0,-1,0};

pair<Range,Range> A[148];int atot;
vector<Range> mx,my;
int ida[148];vector<int> idx,idy;
int coef[148],g[148];
Range fx,fy;int ans[148];

inline bool dfs_x(int step,Range cx)
{
    if (step==int(mx.size()))
    {
        if (cx.l<=X && X<=cx.r) {fx=cx;return true;} else return false;
    }
    if (dfs_x(step+1,cx+mx[step])) {coef[idx[step]]=1;return true;}
    if (dfs_x(step+1,cx-mx[step])) {coef[idx[step]]=-1;return true;}
    return false;
}

inline bool dfs_y(int step,Range cy)
{
    if (step==int(my.size()))
    {
        if (cy.l<=Y && Y<=cy.r) {fy=cy;return true;} else return false;
    }
    if (dfs_y(step+1,cy+my[step])) {coef[idy[step]]=1;return true;}
    if (dfs_y(step+1,cy-my[step])) {coef[idy[step]]=-1;return true;}
    return false;
}

inline void print()
{
    int deltax=X-fx.l,deltay=Y-fy.l,dir=1;
    for (register int i=1;i<=n;i++)
    {
        if (type[i]=='?')
        {
            int todir=(coef[g[i]]==1?0:2)+(!(i&1));
            todir=(todir-dir+4)%4;
            if (todir==1) type[i]='R'; else type[i]='L';
        }
        if (type[i]=='L') dir=(dir+3)%4; else dir=(dir+1)%4;
        if (i&1)
        {
            Range tmp=a[i]*dy[dir];
            int delta=min(tmp.r-tmp.l,deltay);
            ans[i]=myabs(tmp.l+delta);deltay-=delta;
        }
        else
        {
            Range tmp=a[i]*dx[dir];
            int delta=min(tmp.r-tmp.l,deltax);
            ans[i]=myabs(tmp.l+delta);deltax-=delta;
        }
    }
    printf("%d\n",n);
    for (register int i=1;i<=n;i++) printf("%c %d\n",type[i],ans[i]);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d%d",&n,&X,&Y);
    for (register int i=1;i<=n;i++)
    {
        char tmp[10];
        scanf("%s%d%d",tmp+1,&a[i].l,&a[i].r);
        type[i]=tmp[1];
    }
    Range Sx,Sy;Sx.clear();Sy.clear();
    for (register int i=1;i<=n;)
    {
        int dir=((i&1)?1:0),pt=i;
        ++tot;Move[tot].x.clear();Move[tot].y.clear();
        while (pt<=n && (i==pt || type[pt]!='?'))
        {
            if (type[pt]=='L') dir=(dir+3)%4;
            if (type[pt]=='R') dir=(dir+1)%4;
            if (type[pt]=='?') dir^=1;
            if (dx[dir]) Move[tot].x=Move[tot].x+a[pt]*dx[dir];
            if (dy[dir]) Move[tot].y=Move[tot].y+a[pt]*dy[dir];
            g[pt++]=tot;
        }
        if (type[i]!='?') Sx=Sx+Move[tot].x,Sy=Sy+Move[tot].y;
        else if (pt-i>=2) A[++atot]=Move[tot],ida[atot]=tot;
        else
        {
            if (i&1) my.pb(Move[tot].y),idy.pb(tot); else mx.pb(Move[tot].x),idx.pb(tot);
        }
        i=pt;
    }
    for (register int Mask=0;Mask<(1<<atot);Mask++)
    {
        Range cx=Sx,cy=Sy;
        for (register int i=1;i<=atot;i++)
        {
            int dir=((Mask&(1<<(i-1)))?1:-1);coef[ida[i]]=dir;
            cx=cx+A[i].x*dir;cy=cy+A[i].y*dir;
        }
        if (dfs_x(0,cx) && dfs_y(0,cy)) {print();return 0;}
    }
    puts("-1");
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}