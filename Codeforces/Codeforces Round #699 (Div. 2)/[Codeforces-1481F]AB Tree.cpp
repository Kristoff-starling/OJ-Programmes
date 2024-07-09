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
const int MAGIC=548;
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

const int MAXN=1e5;

int n,X,D;
vector<int> level[MAXN+48],v[MAXN+48];
bool isleaf[MAXN+48];int depth[MAXN+48],cd[MAXN+48];
int val[MAXN+48],vcnt[MAXN+48],tot;
vector<int> dd[MAXN+48];
int dp[MAGIC][MAXN+48];
int ans[MAXN+48];

void dfs(int cur)
{
    cd[depth[cur]]++;level[depth[cur]].pb(cur);check_max(D,depth[cur]);
    for (auto y : v[cur]) depth[y]=depth[cur]+1,dfs(y);
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&X);int p;
    memset(isleaf,true,sizeof(isleaf));
    rep(i,2,n) scanf("%d",&p),isleaf[p]=false,v[p].pb(i);
    depth[1]=1;dfs(1);
    tot=0;rep(i,1,n) if (cd[i]) val[++tot]=cd[i];
    sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
    rep(i,1,n) if (cd[i])
    {
        int id=lower_bound(val+1,val+tot+1,cd[i])-val;
        vcnt[id]++;dd[id].pb(i);
    }
    rep(i,0,tot) rep(j,0,X) dp[i][j]=-1;dp[0][0]=0;
    rep(i,1,tot)
    {
        dp[i][0]=0;
        rep(j,1,X)
        {
            if (dp[i-1][j]!=-1) dp[i][j]=0;
            else if (j-val[i]>=0 && dp[i][j-val[i]]!=-1 && dp[i][j-val[i]]<vcnt[i]) dp[i][j]=dp[i][j-val[i]]+1;
        }
    }
    if (dp[tot][X]!=-1)
    {
        printf("%d\n",D);int cur=tot,rem=X;
        while (rem)
        {
            int need=dp[cur][rem];
            for (int i=0;i<need;i++)
                for (auto node : level[dd[cur][i]]) ans[node]=1;
            rem-=need*val[cur];cur--;
        }
        rep(i,1,n) printf(ans[i]==1?"a":"b");puts("");
    }
    else
    {
        printf("%d\n",D+1);int rema=X,remb=n-X;
        rep(i,1,D)
            if (rema>=cd[i])
            {
                for (auto node : level[i]) ans[node]=2;
                rema-=cd[i];
            }
            else if (remb>=cd[i])
            {
                for (auto node : level[i]) ans[node]=1;
                remb-=cd[i];
            }
            else
            {
                int col=(rema>=remb?2:1),lim=(col==2?rema:remb),cc=0;
                for (auto node : level[i]) if (!isleaf[node]) ans[node]=col,cc++;
                for (auto node : level[i]) if (isleaf[node]) {ans[node]=col;cc++;if (cc==lim) break;}
                rep(j,1,n) if (!ans[j]) ans[j]=3-col;
                break;
            }
        rep(i,1,n) printf(ans[i]==2?"a":"b");puts("");
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}