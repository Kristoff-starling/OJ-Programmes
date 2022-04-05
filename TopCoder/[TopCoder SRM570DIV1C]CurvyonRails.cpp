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

namespace flow
{
    const int flow_maxn=1e5;
    int head[flow_maxn+48],cur[flow_maxn+48],to[flow_maxn+48],nxt[flow_maxn+48],f[flow_maxn+48],cost[flow_maxn+48],tot,t,mincost,maxflow;
    bool visited[flow_maxn+48];int D[flow_maxn+48];
    inline void init() {tot=1;memset(head,0,sizeof(head));memset(D,0,sizeof(D));mincost=maxflow;}
    inline void addedge(int s,int t,int cap,int cc)
    {
        to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
        to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
    }
    inline int aug(int x,int maxf)
    {
        if (x==t) {mincost+=(-D[0])*maxf;maxflow+=maxf;return maxf;}
        visited[x]=true;
        int y,minf,now,ans=0;
        for (register int &i=cur[x];i;i=nxt[i])
        {
            y=to[i];
            if (f[i] && !visited[y] && D[x]+cost[i]-D[y]==0)
            {
                minf=min(maxf-ans,f[i]);
                now=aug(y,minf);
                f[i]-=now;f[i^1]+=now;ans+=now;
            }
            if (ans>=maxf) return ans;
        }
        return ans;
    }
    inline bool relabel()
    {
        int d=INF;
        for (register int cur=0;cur<=t;cur++)
            if (visited[cur])
                for (register int i=head[cur];i;i=nxt[i])
                {
                    int y=to[i];
                    if (!visited[y] && f[i]) check_min(d,D[cur]+cost[i]-D[y]);
                }
        if (d>=INF) return false;
        for (register int cur=0;cur<=t;cur++) if (visited[cur]) D[cur]-=d;
        return true;
    }
    inline Pair zkw()
    {
        mincost=0;maxflow=0;
        do
        {
            for (register int i=0;i<=t;i++) cur[i]=head[i];
            do
                for (register int i=0;i<=t;i++) visited[i]=false;
            while (aug(0,INF));
        }
        while (relabel());
        return mp(maxflow,mincost);
    }
}

class CurvyonRails
{
    int n,m;
    inline int getind(int x,int y) {return (x-1)*m+y;}
    inline int getrow(int x,int y) {return n*m*3+(x-1)*m+y;}
    inline int getcol(int x,int y) {return n*m*4+(x-1)*m+y;}
    public:
        inline int getmin(vector<string> field)
        {
            n=int(field.size());m=int(field[0].size());
            flow::init();flow::t=n*m*5+1;int cnt1=0,cnt2=0;
            for (register int i=1;i<=n;i++)
                for (register int j=1;j<=m;j++)
                    if (field[i-1][j-1]!='w')
                        if ((i+j)&1)
                        {
                            cnt1++;
                            flow::addedge(0,getind(i,j),2,0);
                            int tc=(field[i-1][j-1]=='C'?1:0);
                            flow::addedge(getind(i,j),n*m+getind(i,j),1,0);
                            flow::addedge(getind(i,j),n*m+getind(i,j),1,tc);
                            flow::addedge(getind(i,j),n*m*2+getind(i,j),1,0);
                            flow::addedge(getind(i,j),n*m*2+getind(i,j),1,tc);
                            if (j!=1) flow::addedge(n*m+getind(i,j),getrow(i,j-1),1,0);
                            if (j!=m) flow::addedge(n*m+getind(i,j),getrow(i,j),1,0);
                            if (i!=1) flow::addedge(n*m*2+getind(i,j),getcol(i-1,j),1,0);
                            if (i!=n) flow::addedge(n*m*2+getind(i,j),getcol(i,j),1,0);
                        }
                        else
                        {
                            cnt2++;
                            flow::addedge(getind(i,j),flow::t,2,0);
                            int tc=(field[i-1][j-1]=='C'?1:0);
                            flow::addedge(n*m+getind(i,j),getind(i,j),1,0);
                            flow::addedge(n*m+getind(i,j),getind(i,j),1,tc);
                            flow::addedge(n*m*2+getind(i,j),getind(i,j),1,0);
                            flow::addedge(n*m*2+getind(i,j),getind(i,j),1,tc);
                            if (j!=1) flow::addedge(getrow(i,j-1),n*m+getind(i,j),1,0);
                            if (j!=m) flow::addedge(getrow(i,j),n*m+getind(i,j),1,0);
                            if (i!=1) flow::addedge(getcol(i-1,j),n*m*2+getind(i,j),1,0);
                            if (i!=n) flow::addedge(getcol(i,j),n*m*2+getind(i,j),1,0);
                        }
            if (cnt1!=cnt2) return -1;
            Pair res=flow::zkw();
            if (res.x!=cnt1*2) return -1;
            return res.y;
        }
};

#ifdef LOCAL
int main ()
{
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
    CurvyonRails A;vector<string> ss;string s;int n;
    while (cin>>n)
    {
        ss.clear();
        for (register int i=1;i<=n;i++) cin>>s,ss.pb(s);
        cout<<A.getmin(ss)<<endl;
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
#endif