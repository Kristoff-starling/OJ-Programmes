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

int n;

int num[58][48][2],tot;

char s[58][48];int len[58],c[58];

vector<Pair> v[100048];

inline void addedge(int x,int y,int c)
{
    v[x].pb(mp(y,c));
}

inline bool ispalindrome(int x,int l,int p)
{
    int L,R;bool f=true;
    if (p==0) L=1,R=l; else L=len[x]-l+1,R=len[x];
    while (L<=R)
    {
        if (s[x][L]!=s[x][R]) {f=false;break;}
        L++;R--;
    }
    return f;
}

inline bool Match(int num1,int num2,int le,int Le,int sta)
{
    if (sta==0)
    {
        int pt1=1,pt2=Le;bool f=true;
        rep(i,1,le)
        {
            if (s[num1][pt2]!=s[num2][pt1]) {f=false;break;}
            pt1++;pt2--;
        }
        return f;
    }
    else
    {
        int pt1=len[num1]-Le+1,pt2=len[num2];bool f=true;
        rep(i,1,le)
        {
            if (s[num1][pt1]!=s[num2][pt2]) {f=false;break;}
            pt1++;pt2--;
        }
        return f;
    }
}

LL dist[100048];
priority_queue<pLL> q;

inline void dijkstra()
{
    rep(i,0,tot) dist[i]=LINF;
    dist[0]=0;q.push(mp(0,0));
    while (!q.empty())
    {
        int x=q.top().y;LL dd=-q.top().x;q.pop();
        if (dd>dist[x]) continue;
        for (int i=0;i<int(v[x].size());i++)
        {
            int to=v[x][i].x;
            if (dist[x]+v[x][i].y<dist[to])
            {
                dist[to]=dist[x]+v[x][i].y;
                q.push(mp(-dist[to],to));
            }
        }
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
    scanf("%d",&n);
    rep(i,1,n) scanf("%s%d",s[i]+1,c+i),len[i]=strlen(s[i]+1);
    tot=0;rep(i,1,n) rep(j,1,len[i]) rep(k,0,1) num[i][j][k]=++tot;
    tot++;
    rep(i,1,n) addedge(0,num[i][len[i]][1],c[i]);
    rep(i,1,n) rep(j,1,len[i]) rep(k,0,1) if (ispalindrome(i,j,k)) addedge(num[i][j][k],tot,0);
    rep(i,1,n) rep(j,1,len[i])
    {
        //status 0: prefix
        rep(k,1,n) if (Match(i,k,min(j,len[k]),j,0))
        {
            if (len[k]<j) addedge(num[i][j][0],num[i][j-len[k]][0],c[k]);
            else if (len[k]==j) addedge(num[i][j][0],tot,c[k]);
            else addedge(num[i][j][0],num[k][len[k]-j][1],c[k]);
        }
        //status 1: suffix
        rep(k,1,n) if (Match(i,k,min(j,len[k]),j,1))
        {
            if (len[k]<j) addedge(num[i][j][1],num[i][j-len[k]][1],c[k]);
            else if (len[k]==j) addedge(num[i][j][1],tot,c[k]);
            else addedge(num[i][j][1],num[k][len[k]-j][0],c[k]);
        }
    }
    dijkstra();
    if (dist[tot]>=LINF) puts("-1"); else printf("%lld\n",dist[tot]);
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}