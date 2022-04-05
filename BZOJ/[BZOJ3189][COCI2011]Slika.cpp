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
const int MAXM=1e5;

int n,k,q;

int ans[MAXN+48][MAXN+48],col;

int stot=0;
struct Operation
{
    int op,x1,y1,x2,y2,x;
    inline void input()
    {
        char type[10];scanf("%s",type+1);
        if (type[1]=='P') op=1;
        else if (type[1]=='S') op=2;
        else op=3;
        if (op==1) scanf("%d%d%d%d%d",&x,&x1,&y1,&x2,&y2),x1++,y1++,x2++,y2++;
        else if (op==2) x=++stot;
        else scanf("%d",&x);
    }
}a[MAXM+48];

namespace SegmentTree
{
    int sum[2][1<<11][1<<11];
    inline void pushup(int type,int x,int y)
    {
        for (register int i=x;i;i>>=1)
            for (register int j=y;j;j>>=1)
                sum[type][i][j]++;
    }
    inline int queryy(int type,int curx,int cury,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return sum[type][curx][cury];
        int mid=(l+r)>>1,res=0;
        if (left<=mid) res+=queryy(type,curx,cury<<1,left,right,l,mid);
        if (mid+1<=right) res+=queryy(type,curx,cury<<1|1,left,right,mid+1,r);
        return res;
    }
    int X;
    inline void updatey(int type,int curx,int cury,int l,int r)
    {
        if (l==r)
        {
            if (((X+l)&1)==type) ans[X][l]=col;
            pushup(type,curx,cury);
            return;
        }
        int mid=(l+r)>>1;
        if (sum[type][curx][cury<<1]<mid-l+1) updatey(type,curx,cury<<1,l,mid);
        if (sum[type][curx][cury<<1|1]<r-mid) updatey(type,curx,cury<<1|1,mid+1,r);
    }
    inline void findy(int type,int curx,int cury,int left,int right,int l,int r)
    {
        if (left<=l && r<=right)
        {
            if (sum[type][curx][cury]==(right-left+1)) return;
            updatey(type,curx,cury,l,r);return;
        }
        int mid=(l+r)>>1;
        if (left<=mid && sum[type][curx][cury<<1]<mid-l+1) findy(type,curx,cury<<1,left,right,l,mid);
        if (mid+1<=right && sum[type][curx][cury<<1|1]<r-mid) findy(type,curx,cury<<1|1,left,right,mid+1,r);
    }
    inline void updatex(int type,int cur,int ly,int ry,int l,int r)
    {
        if (l==r) {X=l;findy(type,cur,1,ly,ry,1,n);return;}
        int mid=(l+r)>>1;
        if (queryy(type,cur<<1,1,ly,ry,1,n)<(mid-l+1)*(ry-ly+1)) updatex(type,cur<<1,ly,ry,l,mid);
        if (queryy(type,cur<<1|1,1,ly,ry,1,n)<(r-mid)*(ry-ly+1)) updatex(type,cur<<1|1,ly,ry,mid+1,r);
    }
    inline bool findx(int type,int cur,int lx,int rx,int ly,int ry,int l,int r)
    {
        if (lx<=l && r<=rx)
        {
            int sm=queryy(type,cur,1,ly,ry,1,n);
            if (sm==(r-l+1)*(ry-ly+1)) return false;
            updatex(type,cur,ly,ry,l,r);
            return true;
        }
        int mid=(l+r)>>1;bool res=false;
        if (lx<=mid && sum[type][cur<<1][1]<(mid-l+1)*n) res|=findx(type,cur<<1,lx,rx,ly,ry,l,mid);
        if (mid+1<=rx && sum[type][cur<<1|1][1]<(r-mid)*n) res|=findx(type,cur<<1|1,lx,rx,ly,ry,mid+1,r);
        return res;
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
    scanf("%d%d%d",&n,&k,&q);
    for (register int i=1;i<=q;i++) a[i].input();
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=n;j++)
            ans[i][j]=1;
    for (register int i=q;i>=1;i--)
    {
        if (a[i].op==1)
        {
            int type=(a[i].x1+a[i].y1)&1;
            col=a[i].x;
            for (;SegmentTree::findx(type,1,a[i].x1,a[i].x2,a[i].y1,a[i].y2,1,n););
        }
        if (a[i].op==3)
            for (register int ind=a[i].x;!(a[i].op==2 && a[i].x==ind);i--);
    }
    for (register int i=1;i<=n;i++)
    {
        for (register int j=1;j<=n;j++)
            printf("%d ",ans[i][j]);
        printf("\n");
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}