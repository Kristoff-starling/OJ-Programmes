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

int n,m,W,sx,sy;

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

char s[48][48],S[148];

short dist[21][21][20048];
bool isdanger[200048];
queue<int> q;

int tot;
namespace AC_Automaton
{
    struct node
    {
        int nxt[27],fail;
    }trie[200048];
    inline int Create()
    {
        ++tot;
        trie[tot].fail=0;memset(trie[tot].nxt,0,sizeof(trie[tot].nxt));
        isdanger[tot]=false;
        return tot;
    }
    inline void init() {tot=0;Create();}
    inline void insert(char s[])
    {
        int len=strlen(s+1),cur=1;
        for (register int i=1;i<=len;i++)
        {
            int w=s[i]-'A'+1;
            if (!trie[cur].nxt[w]) trie[cur].nxt[w]=Create();
            cur=trie[cur].nxt[w];
        }
        isdanger[cur]=true;
    }
    int head,tail,q[200048];
    inline void construct_fail()
    {
        head=1;tail=1;q[1]=1;
        while (head<=tail)
        {
            int cur=q[head++];
            for (register int i=1;i<=26;i++)
                if (trie[cur].nxt[i])
                {
                    int tmp=trie[cur].fail;
                    while (tmp && !trie[tmp].nxt[i]) tmp=trie[tmp].fail;
                    trie[trie[cur].nxt[i]].fail=(tmp?trie[tmp].nxt[i]:1);
                    q[++tail]=trie[cur].nxt[i];
                }
                else
                    trie[cur].nxt[i]=(cur==1?1:trie[trie[cur].fail].nxt[i]);
        }
    }
    inline int go(int x,char ch)
    {
        return trie[x].nxt[ch-'A'+1];
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
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);
        for (register int i=1;i<=n;i++)
        {
            scanf("%s",s[i]+1);
            for (register int j=1;j<=m;j++)
                if (s[i][j]=='@') sx=i,sy=j;
        }
        scanf("%d",&W);AC_Automaton::init();
        for (register int i=1;i<=W;i++)
        {
            scanf("%s",S+1);
            AC_Automaton::insert(S);
        }
        AC_Automaton::construct_fail();
        for (register int i=1;i<=n;i++)
            for (register int j=1;j<=m;j++)
                for (register int k=1;k<=tot;k++)
                    dist[i][j][k]=-1;
        while (!q.empty()) q.pop();
        dist[sx][sy][1]=0;q.push(sx);q.push(sy);q.push(1);
        bool f=false;
        while (!q.empty())
        {
            int cx=q.front();q.pop();
            int cy=q.front();q.pop();
            int pos=q.front();q.pop();
            if (isdanger[pos]) {cout<<dist[cx][cy][pos]<<endl;f=true;break;}
            int tod=dist[cx][cy][pos]+1,xx,yy,tp;
            for (register int dir=0;dir<=3;dir++)
            {
                xx=cx+dx[dir];yy=cy+dy[dir];
                if (1<=xx && xx<=n && 1<=yy && yy<=m && s[xx][yy]!='#')
                {
                    tp=pos;if ('A'<=s[xx][yy] && s[xx][yy]<='Z') tp=AC_Automaton::go(tp,s[xx][yy]);
                    while (dist[xx][yy][tp]==-1)
                    {
                        dist[xx][yy][tp]=tod;
                        q.push(xx);q.push(yy);q.push(tp);
                        if ('A'<=s[xx][yy] && s[xx][yy]<='Z') tp=AC_Automaton::go(tp,s[xx][yy]);
                    }
                }
            }
        }
        if (!f) puts("-1");
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}