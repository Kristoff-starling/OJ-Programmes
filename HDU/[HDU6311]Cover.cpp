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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
    bool f;char ch;int res;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

const int MAXN=1e5;
const int hashmod=299991;

inline int myabs(int x) {return x>=0?x:-x;}

struct Hash
{
    int head[hashmod+48],nxt[MAXN*4+48],f[MAXN*4+48];LL to[MAXN*4+48];int tot;
    inline void clear() {memset(head,0,sizeof(head));tot=0;}
    inline void add(int s,LL t,int cap)
    {
        to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
    }
    inline void Set(LL pos,int val)
    {
        int hpos=pos%hashmod,i;
        for (i=head[hpos];i;i=nxt[i])
            if (to[i]==pos) {f[i]=val;return;}
        add(hpos,pos,val);
    }
    inline int query(LL pos)
    {
        int hpos=pos%hashmod,i;
        for (i=head[hpos];i;i=nxt[i])
            if (to[i]==pos) return f[i];
        return 0;
    }
}Mppos,Mpneg,exist;

int n,m;
vector<Pair> v[MAXN+48];
int head[MAXN+48],cc[MAXN+48],to[MAXN*4+48],nxt[MAXN*4+48],f[MAXN*4+48],tt=0;
inline void addedge(int s,int t,int cap)
{
    assert(s<=n && t<=n);
    to[++tt]=t;nxt[tt]=head[s];head[s]=tt;f[tt]=cap;
}
vector<int> ans[MAXN+48];int tot;
bool visited[MAXN*2+48],vv[MAXN+48];
int d[MAXN+48];

inline LL getind(int x,int y)
{
    return 1ll*x*(MAXN+48)+y;
}

int seq[MAXN+48],stot,odd[MAXN+48],otot;
inline void Dfs(int cur)
{
    vv[cur]=true;seq[++stot]=cur;
    int i,y;
    for (i=head[cur];i;i=nxt[i])
    {
        y=to[i];
        if (!vv[y]) Dfs(y);
    }
}

stack<int> s;
int path[MAXN*4+48],ptot;
int ccc=0;
inline void fluery(int cur)
{
//    cerr<<cur<<endl;
    s.push(cur);int y,num;
    for (int &i=cc[cur];i;i=nxt[i])
    {
        y=to[i];num=myabs(f[i]);
//        cerr<<num<<endl;
        assert(y<=n);
        if (visited[num]) continue;
        visited[num]=true;fluery(y);
    }
    path[++ptot]=s.top();s.pop();
}

inline void Clear()
{
    Mppos.clear();Mpneg.clear();exist.clear();
    for (register int i=1;i<=tot;i++) ans[i].clear();tot=0;
    memset(head,0,sizeof(head));tt=0;
    memset(visited,false,sizeof(visited));
    memset(vv,false,sizeof(vv));
    memset(d,0,sizeof(d));
}

int main ()
{
//    freopen ("1003.in","r",stdin);
//    freopen ("a.out","w",stdout);
    int i,j,x,y,mm;
    while (~scanf("%d%d",&n,&m))
    {
//        cerr<<"("<<endl;
        Clear();mm=m;
        for (i=1;i<=m;i++)
        {
            x=getint();y=getint();
            addedge(x,y,i);addedge(y,x,-i);
            Mppos.Set(getind(x,y),i);Mpneg.Set(getind(y,x),-i);
            d[x]++;d[y]++;
        }
        for (i=1;i<=n;i++)
            if (!vv[i])
            {
//                cerr<<"*"<<endl;
                stot=0;Dfs(i);
                if (stot==1) continue;
                otot=0;for (j=1;j<=stot;j++) if (d[seq[j]]%2==1) odd[++otot]=seq[j];
                for (j=1;j<=otot-1;j+=2)
                {
                    addedge(odd[j],odd[j+1],++m);addedge(odd[j+1],odd[j],m);
                    if (!Mppos.query(getind(odd[j],odd[j+1])))
                    {
                        Mppos.Set(getind(odd[j],odd[j+1]),m);
                        Mpneg.Set(getind(odd[j+1],odd[j]),m);
                    }
                }
//                cerr<<stot<<' '<<otot<<endl;
//                cerr<<"*"<<endl;
                for (j=1;j<=n;j++) cc[j]=head[j];
                ptot=0;fluery(i);
//                for (j=1;j<=ptot;j++) cout<<path[j]<<' ';
//                cout<<endl;
//                cerr<<"!"<<endl;
                memcpy(path+ptot+1,path+2,(ptot-1)*sizeof(int));int st;
                for (st=ptot-1;!(myabs(Mppos.query(getind(path[st],path[st+1])))>mm || exist.query(getind(path[st],path[st+1]))) && st;st--)
                {
                    exist.Set(getind(path[st],path[st+1]),1);
                    exist.Set(getind(path[st+1],path[st]),1);
                }
                st++;
//                cerr<<st<<endl;
//                for (j=1;j<=ptot;j++) cerr<<path[j]<<' ';
//                cerr<<endl;
                ++tot;
                for (j=st;j<=st+ptot-2;j++)
                {
//                    cerr<<path[j]<<' '<<path[j+1]<<"*"<<endl;
                    if ((Mppos.query(getind(path[j],path[j+1]))>mm || !Mppos.query(getind(path[j],path[j+1]))) && (Mpneg.query(getind(path[j],path[j+1]))>mm || !Mpneg.query(getind(path[j],path[j+1]))))
                    {if (int(ans[tot].size())) ++tot;continue;}
                    int num;
                    if (Mppos.query(getind(path[j],path[j+1]))) num=Mppos.query(getind(path[j],path[j+1])); else num=Mpneg.query(getind(path[j],path[j+1]));
                    ans[tot].pb(num);
                    Mppos.Set(getind(path[j],path[j+1]),0);
                    Mppos.Set(getind(path[j+1],path[j]),0);
                    Mpneg.Set(getind(path[j],path[j+1]),0);
                    Mpneg.Set(getind(path[j+1],path[j]),0);
//                    Mppos[getind(path[j],path[j+1])]=Mpneg[getind(path[j],path[j+1])]=Mppos[getind(path[j+1],path[j])]=Mpneg[getind(path[j+1],path[j])]=0;
                }
                if (!int(ans[tot].size())) tot--;
            }
//        cerr<<")"<<endl;
//        cerr<<"*"<<endl;
        printf("%d\n",tot);
        for (i=1;i<=tot;i++)
        {
            printf("%d ",int(ans[i].size()));
            assert(int(ans[i].size()));
            for (j=0;j<int(ans[i].size());j++) printf("%d ",ans[i][j]);
            puts("");
        }
    }
    return 0;
}
