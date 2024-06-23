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

int taboo[10][10][10],cnt[10][10];

int a[10][10];

void modify_taboo(int x,int y,int num,int delta)
{
    rep(i,1,9)
    {
        taboo[x][i][num]+=delta;
        if (taboo[x][i][num]==1 && delta==1) cnt[x][i]++;
        if (taboo[x][i][num]==0 && delta==-1) cnt[x][i]--;
    }
    rep(i,1,9)
    {
        taboo[i][y][num]+=delta;
        if (taboo[i][y][num]==1 && delta==1) cnt[i][y]++;
        if (taboo[i][y][num]==0 && delta==-1) cnt[i][y]--;
    }
    int belx=(x-1)/3+1,bely=(y-1)/3+1;
    rep(i,(belx-1)*3+1,belx*3) rep(j,(bely-1)*3+1,bely*3)
    {
        taboo[i][j][num]+=delta;
        if (taboo[i][j][num]==1 && delta==1) cnt[i][j]++;
        if (taboo[i][j][num]==0 && delta==-1) cnt[i][j]--;
    }
}

bool flag=false;

void dfs(int step)
{
    if (step==81) {flag=true;return;}
    int maxn=-1,cx,cy;
    rep(i,1,9) rep(j,1,9) if (!a[i][j] && cnt[i][j]>maxn) maxn=cnt[i][j],cx=i,cy=j;
    rep(i,1,9) if (!taboo[cx][cy][i])
    {
        modify_taboo(cx,cy,i,1);a[cx][cy]=i;
        dfs(step+1);
        if (flag) return;
        modify_taboo(cx,cy,i,-1);a[cx][cy]=0;
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    rep(i,1,9) rep(j,1,9) scanf("%d",&a[i][j]);
    int step=0;
    rep(i,1,9) rep(j,1,9) if (a[i][j]) modify_taboo(i,j,a[i][j],1),step++;
    dfs(step);
    rep(i,1,9)
    {
        rep(j,1,9) printf("%d ",a[i][j]);
        puts("");
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}