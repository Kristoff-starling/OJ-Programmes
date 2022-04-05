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

class KingdomMap
{
    static const int MAXN=500;
    Pair edge[MAXN+48];
    vector<int> v[MAXN+48];int n,m;
    inline int string_to_int(string s)
    {
        int res=0;
        for (register int i=0;i<int(s.size());i++) res=res*10+s[i]-'0';
        return res;
    }
    inline void addedge(string s,int id)
    {
        int pt=0;
        while (s[pt]!=' ') pt++;
        int x=string_to_int(s.substr(0,pt)),y=string_to_int(s.substr(pt+1,int(s.size())-pt-1));
        x++;y++;
        edge[id]=mp(x,y);v[x].pb(id);v[y].pb(id);
    }
    inline void doit_roads(vector<string> roads)
    {
        if (!int(roads.size())) return;
        string s="";for (register int i=0;i<int(roads.size());i++) s+=roads[i];
        s=","+s+",";int pt1=0,pt2;m=0;
        while (pt1!=int(s.size())-1)
        {
            pt2=pt1+1;
            while (s[pt2]!=',') pt2++;
            addedge(s.substr(pt1+1,pt2-pt1-1),++m);
            pt1=pt2;
        }
    }
    bool visited[MAXN+48];
    int dp[MAXN+48][3][2][2];int taboo[MAXN+48];
    inline void dfs(int cur,int father)
    {
        visited[cur]=true;
        int dp2[2][10][10][10];int cc=0,nxt=1;
        memset(dp2,0x3f,sizeof(dp2));
        dp2[0][0][0][0]=0;
        for (register int i=0;i<int(v[cur].size());i++)
        {
            int y=((edge[v[cur][i]].x==cur)?edge[v[cur][i]].y:edge[v[cur][i]].x);
            if (taboo[v[cur][i]]) continue;
            if (y!=father) 
            {
                dfs(y,cur);
                memset(dp2[nxt],0x3f,sizeof(dp2[nxt]));
                for (register int pbs=0;pbs<=2;pbs++)
                    for (register int psz=0;psz<=1;psz++)
                        for (register int psta=0;psta<=1;psta++)
                            if (dp2[cc][pbs][psz][psta]<INF)
                                for (register int cbs=0;cbs<=2;cbs++)
                                    for (register int csz=0;csz<=1;csz++)
                                        for (register int csta=0;csta<=1;csta++)
                                            if (dp[y][cbs][csz][csta]<INF)
                                            {
                                                assert(dp[y][cbs][csz][csta]>=0);
                                                // cut this edge
                                                check_min(dp2[nxt][pbs][psz][psta],dp2[cc][pbs][psz][psta]+dp[y][cbs][csz][csta]+1);
                                                // preserve this edge
                                                if (cbs==2 && psz) continue;
                                                if (pbs==2 && csz) continue;
                                                if (psta) continue;
                                                if (csta) continue;
                                                check_min(dp2[nxt][pbs+csz][1][cbs==2],dp2[cc][pbs][psz][psta]+dp[y][cbs][csz][csta]);
                                            }
                cc^=1;nxt^=1;
            }
        }
        for (register int pbs=0;pbs<=2;pbs++)
            for (register int psz=0;psz<=1;psz++)
                for (register int psta=0;psta<=1;psta++)
                    check_min(dp[cur][pbs][psz][psta],dp2[cc][pbs][psz][psta]);
    }
    inline int solve()
    {
        memset(visited,false,sizeof(visited));
        memset(dp,0x3f,sizeof(dp));
        int ans=0;
        for (register int i=1;i<=n;i++)
            if (!visited[i])
            {
                dfs(i,-1);int curans=INF;
                for (register int j=0;j<=2;j++)
                    for (register int k=0;k<=1;k++)
                        for (register int l=0;l<=1;l++)
                            check_min(curans,dp[i][j][k][l]);
                ans+=curans;
            }
        return ans;
    }
    vector<int> Res;
    public:
        inline vector<int> getRoadsToRemove(int N,vector<string> roads)
        {
            for (register int i=1;i<=N;i++) v[i].clear();
            n=N;doit_roads(roads);
            memset(taboo,0,sizeof(taboo));
            int base=solve();int cnt=0;Res.clear();
            for (register int i=1;i<=m;i++)
            {
                taboo[i]=1;cnt++;
                if (cnt+solve()>base) taboo[i]=0,cnt--;
                else Res.pb(i-1);
                if (cnt==base) break;
            }
            return Res;
        }
};

#ifdef LOCAL
int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    vector<string> aa;int nn,mm;
    KingdomMap A;
    while (cin>>nn>>mm)
    {
        string ss;getchar();
        for (register int i=1;i<=mm;i++) getline(cin,ss),aa.pb(ss);
        vector<int> res=A.getRoadsToRemove(nn,aa);
        for (auto item : res) cout<<item<<' ';
        cout<<endl;
        aa.clear();
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
#endif