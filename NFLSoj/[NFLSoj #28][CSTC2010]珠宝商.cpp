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

const int MAXN=5e4;

int n,m,MAGIC;LL ans;
vector<int> v[MAXN+48];
char a[MAXN+48],s[2][MAXN+48];

bool visited[MAXN+48];int sz[MAXN+48];

struct SAM
{
    int maxn[MAXN*2],par[MAXN*2],nxt[MAXN*2][27],to[MAXN*2][27],root,last,tot;
    int mark[MAXN*2],sz[MAXN*2],ind[MAXN*2],pos[MAXN*2];Pair ord[MAXN*2];
    inline int Create()
    {
        ++tot;
        maxn[tot]=par[tot]=mark[tot]=sz[tot]=ind[tot]=0;
        memset(nxt[tot],0,sizeof(nxt[tot]));
        return tot;
    }
    inline void init() {tot=0;root=last=Create();}
    inline void extend(char ch,int id)
    {
        int p=last,np=Create();maxn[np]=maxn[p]+1;sz[np]=1;ind[np]=id;pos[id]=np;
        int w=ch-'a'+1;
        while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
        if (!p) {par[np]=root;last=np;return;}
        int q=nxt[p][w];
        if (maxn[q]==maxn[p]+1) {par[np]=q;last=np;return;}
        int nq=Create();maxn[nq]=maxn[p]+1;memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
        par[nq]=par[q];par[np]=nq;par[q]=nq;
        while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
        last=np;
    }
    inline int go(int cur,int w) {return nxt[cur][w]?nxt[cur][w]:-1;}
    inline void build(char s[])
    {
        for (register int i=1;i<=tot;i++) ord[i]=mp(maxn[i],i);
        sort(ord+1,ord+tot+1);
        for (register int i=tot;i>=1;i--)
        {
            int x=ord[i].y;
            ind[par[x]]=ind[x];sz[par[x]]+=sz[x];
            to[par[x]][s[ind[par[x]]-maxn[par[x]]]-'a'+1]=x;
        }
    }
    inline void pushdown()
    {
        for (register int i=1;i<=tot;i++)
        {
            int x=ord[i].y;
            if (par[x]) mark[x]+=mark[par[x]];
        }
    }
    inline void clear_mark() {for (register int i=1;i<=tot;i++) mark[i]=0;}
}sam[2];

inline void getsz(int cur,int father)
{
    sz[cur]=1;
    for (auto y : v[cur]) if (!visited[y] && y!=father) getsz(y,cur),sz[cur]+=sz[y];
}

inline void dfs(int cur,int scur,int father,int op)
{
    scur=sam[op].go(scur,a[cur]-'a'+1);if (scur==-1) return;
    if (!op || father!=-1) ans+=sam[op].sz[scur];
    for (auto y : v[cur]) if (y!=father && !visited[y]) dfs(y,scur,cur,op);
}

inline void swork(int cur,int father)
{
    dfs(cur,sam[0].root,-1,0);
    for (auto y : v[cur]) if (!visited[y] && y!=father) swork(y,cur);
}

inline int getrt(int cur,int father,int Sz)
{
    for (auto y : v[cur])
        if (y!=father && !visited[y] && sz[y]>=Sz/2) return getrt(y,cur,Sz);
    return cur;
}

inline Pair trans(Pair tmp,int op,int x)
{
    int cur=tmp.x,cnt=tmp.y;
    if (cnt<sam[op].maxn[cur])
    {
        if (s[op][sam[op].ind[cur]-cnt]!=a[x]) return mp(-1,-1);
    }
    else
    {
        if (!sam[op].to[cur][a[x]-'a'+1]) return mp(-1,-1);
        cur=sam[op].to[cur][a[x]-'a'+1];
    }
    return mp(cur,cnt+1);
}

inline void dfs_sam(int cur,int father,Pair scur,int op)
{
    scur=trans(scur,op,cur);
    if (scur.x==-1) return;
    sam[op].mark[scur.x]++;
    for (auto y : v[cur]) if (y!=father && !visited[y]) dfs_sam(y,cur,scur,op);
}

vector<int> tree_list,List;int fa[MAXN+48],depth[MAXN+48];
inline void dfs_small(int cur,int father)
{
    tree_list.pb(cur);fa[cur]=father;
    for (auto y : v[cur]) if (y!=father && !visited[y]) depth[y]=depth[cur]+1,dfs_small(y,cur);
}

inline int getlca(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    while (depth[u]>depth[v]) u=fa[u];
    if (u==v) return u;
    while (u!=v) u=fa[u],v=fa[v];
    return u;
}

inline void solve(int cur)
{
    getsz(cur,-1);
    if (sz[cur]<=MAGIC) {swork(cur,-1);return;}
    int rt=getrt(cur,-1,sz[cur]);getsz(rt,-1);visited[rt]=true;
    for (auto y : v[rt])
        if (!visited[y])
        {
            if (sz[y]>=MAGIC)
            {
                dfs_sam(y,rt,mp(1,0),0);dfs_sam(y,rt,trans(mp(1,0),1,rt),1);
                sam[0].pushdown();sam[1].pushdown();
                for (register int i=2;i<=m;i++) ans-=1ll*sam[0].mark[sam[0].pos[i-1]]*sam[1].mark[sam[1].pos[m+1-i]];
                sam[0].clear_mark();sam[1].clear_mark();
            }
            else
            {
                tree_list.clear();depth[y]=1;dfs_small(y,-1);
                for (register int i=0;i<int(tree_list.size());i++)
                    for (register int j=0;j<int(tree_list.size());j++)
                    {
                        int pt1=tree_list[i],pt2=tree_list[j];
                        int LCA=getlca(pt1,pt2);int scur=sam[0].root;
                        while (pt1!=LCA)
                        {
                            scur=sam[0].go(scur,a[pt1]-'a'+1);
                            if (scur==-1) break;
                            pt1=fa[pt1];
                        }
                        if (scur==-1) continue;
                        List.clear();
                        do
                        {
                            List.pb(pt1);
                            if (pt1==y) break;
                            pt1=fa[pt1];
                        }
                        while (true);
                        for (auto pt : List)
                        {
                            scur=sam[0].go(scur,a[pt]-'a'+1);
                            if (scur==-1) break;
                        }
                        if (scur==-1) continue;
                        reverse(List.begin(),List.end());
                        scur=sam[0].go(scur,a[rt]-'a'+1);
                        if (scur==-1) continue;
                        for (auto pt : List)
                        {
                            scur=sam[0].go(scur,a[pt]-'a'+1);
                            if (scur==-1) break;
                        }
                        if (scur==-1) continue;
                        List.clear();while (pt2!=LCA) List.pb(pt2),pt2=fa[pt2];
                        reverse(List.begin(),List.end());
                        for (auto pt : List) 
                        {
                            scur=sam[0].go(scur,a[pt]-'a'+1);
                            if (scur==-1) break;
                        }
                        if (scur==-1) continue;
                        ans-=sam[0].sz[scur];
                    }
            }
        }
    for (auto y : v[rt])
        if (!visited[y])
            dfs_sam(y,rt,mp(1,0),0),dfs_sam(y,rt,trans(mp(1,0),1,rt),1);
    sam[0].pushdown();sam[1].pushdown();
    for (register int i=2;i<=m;i++) ans+=1ll*sam[0].mark[sam[0].pos[i-1]]*sam[1].mark[sam[1].pos[m-i+1]];
    sam[0].clear_mark();sam[1].clear_mark();
    dfs(rt,sam[0].root,-1,0);dfs(rt,sam[1].root,-1,1);
    vector<int> sonlist;sonlist.clear();
    for (auto y : v[rt]) if (!visited[y]) sonlist.pb(y);
    for (auto y : sonlist) solve(y);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&m);int x,y;
    for (register int i=1;i<=n-1;i++) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    scanf("%s%s",a+1,s[0]+1);
    for (register int i=1;i<=m;i++) s[1][i]=s[0][m-i+1];
    for (register int op=0;op<=1;op++)
    {
        sam[op].init();
        for (register int i=1;i<=m;i++) sam[op].extend(s[op][i],i);
        sam[op].build(s[op]);
    }
    for (MAGIC=0;1ll*MAGIC*MAGIC<=m;MAGIC++);
    ans=0;solve(1);
    printf("%lld\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}