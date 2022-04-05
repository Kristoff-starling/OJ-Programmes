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

const int MAXN=2000;

int n,q;

int link[MAXN*MAXN*2+48][4];
int mat[MAXN+48][MAXN+48];
int S,Two,Three,Four;

inline int getind(int x,int y) {return (x-1)*n+y;}

inline int go(int pre,int cur)
{
    for (register int i=0;i<=3;i++) if (link[cur][i]==pre) return link[cur][3-i];
}

int up[MAXN+48],down[MAXN+48],lft[MAXN+48],rght[MAXN+48];
int iup[MAXN+48],idown[MAXN+48],ilft[MAXN+48],irght[MAXN+48];
int opup[MAXN+48],opdown[MAXN+48],oplft[MAXN+48],oprght[MAXN+48];
int iopup[MAXN+48],iopdown[MAXN+48],ioplft[MAXN+48],ioprght[MAXN+48];

inline void gen(int rt[],int pre,int cur,int len)
{
    int nxt;
    for (register int i=1;i<=len;i++)
    {
        rt[i]=cur;nxt=go(pre,cur);
        pre=cur;cur=nxt;
    }
}

inline void gen_op(int a[],int A[],int opa[],int opA[],int len)
{
    for (register int i=1;i<=len;i++)
    {
        for (register int dir=0;dir<=3;dir++) if (link[a[i]][dir]==A[i]) opa[i]=dir;
        for (register int dir=0;dir<=3;dir++) if (link[A[i]][dir]==a[i]) opA[i]=dir;
    }
}

//row down first, then col rght
inline Pair getpt1(int dx,int dy)
{
    if (!dx) return mp((dy==1?S:n*n+n+dy-1),n*n+n+dy);
    if (dx==n+1) return mp((dy==1?Three:n*n+n+n+n+dy-1),n*n+n+n+n+dy);
    int pre=0,cur=n*n+dx,nxt;
    for (register int i=1;i<=dy;i++)
    {
        nxt=go(pre,cur);
        pre=cur;cur=nxt;
    }
    return mp(pre,cur);
}

//col rght first, then row down
inline Pair getpt2(int dx,int dy)
{
    if (!dy) return mp((dx==1?S:n*n+dx-1),n*n+dx);
    if (dy==n+1) return mp((dx==1?Two:n*n+n+n+dx-1),n*n+n+n+dx);
    int pre=0,cur=n*n+n+dy,nxt;
    for (register int i=1;i<=dx;i++)
    {
        nxt=go(pre,cur);
        pre=cur;cur=nxt;
    }
    return mp(pre,cur);
}

inline void connect(int id1,int id2,int op1,int op2)
{
    link[id1][op1]=id2;
    link[id2][op2]=id1;
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(q);int x,y,l;char op[5];
    S=n*n+n+n+n+n+1;Two=n*n+n+n+n+n+2;Three=n*n+n+n+n+n+3;Four=n*n+n+n+n+n+4;
    for (register int i=1;i<=n;i++)
    {
        link[n*n+i][2]=getind(i,1);
        link[n*n+i][0]=n*n+i-1;
        link[n*n+i][3]=n*n+i+1;
    }
    for (register int i=1;i<=n;i++)
    {
        link[n*n+n+i][3]=getind(1,i);
        link[n*n+n+i][1]=n*n+n+i-1;
        link[n*n+n+i][2]=n*n+n+i+1;
    }
    for (register int i=1;i<=n;i++)
    {
        link[n*n+n+n+i][1]=getind(i,n);
        link[n*n+n+n+i][0]=n*n+n+n+i-1;
        link[n*n+n+n+i][3]=n*n+n+n+i+1;
    }
    for (register int i=1;i<=n;i++)
    {
        link[n*n+n+n+n+i][0]=getind(n,i);
        link[n*n+n+n+n+i][1]=n*n+n+n+n+i-1;
        link[n*n+n+n+n+i][2]=n*n+n+n+n+i+1;
    }
    link[n*n+1][0]=S;link[n*n+n][3]=Three;
    link[n*n+n+1][1]=S;link[n*n+n+n][2]=Two;
    link[n*n+n+n+1][0]=Two;link[n*n+n+n+n][1]=Four;
    link[n*n+n+n+n+1][1]=Three;link[n*n+n+n+n+n][2]=Four;
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=n;j++)
        {
            if (j!=1) link[getind(i,j)][1]=getind(i,j-1); else link[getind(i,j)][1]=n*n+i;
            if (j!=n) link[getind(i,j)][2]=getind(i,j+1); else link[getind(i,j)][2]=n*n+n+n+i;
            if (i!=1) link[getind(i,j)][0]=getind(i-1,j); else link[getind(i,j)][0]=n*n+n+j;
            if (i!=n) link[getind(i,j)][3]=getind(i+1,j); else link[getind(i,j)][3]=n*n+n+n+n+j;
        }
    Pair res;
    while (q--)
    {
        io.getstring(op+1);io.Get(x);io.Get(y);io.Get(l);
        /* gen up,down,left,right */
        res=getpt1(x-1,y);gen(up,res.x,res.y,l);
        res=getpt1(x+l,y);gen(down,res.x,res.y,l);
        res=getpt2(x,y-1);gen(lft,res.x,res.y,l);
        res=getpt2(x,y+l);gen(rght,res.x,res.y,l);
        /* gen inner up,down,left,right */
        res=getpt1(x,y);gen(iup,res.x,res.y,l);
        res=getpt1(x+l-1,y);gen(idown,res.x,res.y,l);
        res=getpt2(x,y);gen(ilft,res.x,res.y,l);
        res=getpt2(x,y+l-1);gen(irght,res.x,res.y,l);
        /* gen operation of up,down,left,right and their inners*/
        gen_op(up,iup,opup,iopup,l);
        gen_op(down,idown,opdown,iopdown,l);
        gen_op(lft,ilft,oplft,ioplft,l);
        gen_op(rght,irght,oprght,ioprght,l);
        if (op[1]=='T')
        {
            for (register int i=1,j=l;i<=l;i++,j--) connect(up[i],ilft[j],opup[i],ioplft[j]);
            for (register int i=1;i<=l;i++) connect(lft[i],idown[i],oplft[i],iopdown[i]);
            for (register int i=l,j=1;i>=1;i--,j++) connect(down[i],irght[j],opdown[i],ioprght[j]);
            for (register int i=1;i<=l;i++) connect(rght[i],iup[i],oprght[i],iopup[i]);
        }
        else
        {
            for (register int i=1,j=l;i<=l;i++,j--) connect(up[i],irght[j],opup[i],ioprght[j]);
            for (register int i=1,j=l;i<=l;i++,j--) connect(rght[i],iup[j],oprght[i],iopup[j]);
            for (register int i=1,j=l;i<=l;i++,j--) connect(down[i],ilft[j],opdown[i],ioplft[j]);
            for (register int i=1,j=l;i<=l;i++,j--) connect(lft[i],idown[j],oplft[i],iopdown[j]);
        }
    }
    for (register int i=1;i<=n;i++)
    {
        int pre=n*n+i,cur=go(0,pre),nxt;
        gen(mat[i],pre,cur,n);
    }
    unsigned int ans=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            ans^=ans<<13;
            ans^=ans>>17;
            ans^=ans<<5;
            ans+=mat[i][j]+1234567;
        }
    io.Print(ans,'\n');
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}