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

bool visited[66000][17][7];

int n,k,d,lim;
char s[48][48];

vector<int> trans[17][17][7];int Trans[17][17][7];
int p[48];

char S[48];bool exist[48];
char tmp[10];int Id[10];
inline void Getstring(int id)
{
    memset(exist,false,sizeof(exist));
    for (register int i=k;i>=1;i--) S[k-i+1]=s[id][i],exist[s[id][i]-'A'+1]=true;
    int pt=0;
    for (register int i=1;i<=n;i++) if (!exist[i]) tmp[++pt]='A'+i-1;
    pt=k;for (register int i=1;i<=d;i++) S[++pt]=tmp[p[i]];
}

inline bool Go(int id)
{
    int pt=1;memset(exist,false,sizeof(exist));
    for (register int i=1;i<=k;i++)
    {
        while (pt<=n && S[pt]!=s[id][i]) pt++;
        if (pt>n) return false;
        exist[pt]=true;
    }
    return true;
}

inline int getid()
{
    int pt=0;
    for (register int i=1;i<=n;i++) if (!exist[i]) tmp[++pt]=S[i];
    memset(Id,0,sizeof(Id));
    for (register int i=1;i<=d;i++)
        for (register int j=1;j<=d;j++)
            Id[i]+=(tmp[i]>=tmp[j]);
    if (d==1) return 1;
    if (d==2) return Id[1]>Id[2]?2:1;
    return (Id[1]-1)*2+1+(Id[2]>Id[3]);
}

queue<int> q;int table[100048];
inline void bfs()
{
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=lim;j++)
        {
            visited[(1<<n)-1][i][j]=true;
            q.push((1<<n)-1);q.push(i);q.push(j);
        }
    while (!q.empty())
    {
        int Mask=q.front();q.pop();int to=q.front();q.pop();int toid=q.front();q.pop();
        for (register int cur=Mask^(1<<(to-1));cur;cur^=LOWBIT(cur))
        {
            int from=table[LOWBIT(cur)];
            for (auto id : trans[from][to][toid])
            {
                int toMask=Mask^(1<<(to-1));
                if (!visited[toMask][from][id])
                {
                    visited[toMask][from][id]=true;
                    q.push(toMask);q.push(from);q.push(id);
                }
            }
        }
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
    io.Get(n);io.Get(k);d=n-k;
    for (register int i=1;i<=n;i++) table[1<<(i-1)]=i;
    lim=1;for (register int i=1;i<=d;i++) lim*=i;
    for (register int i=1;i<=n;i++) io.getstring(s[i]+1);
    for (register int from=1;from<=n;from++)
        for (register int to=1;to<=n;to++)
            if (from!=to)
            {
                for (register int i=1;i<=d;i++) p[i]=i;int id=0;
                do
                {
                    id++;Getstring(from);bool sta=Go(to);
                    if (sta)
                    {
                        int toid=getid();
                        trans[from][to][toid].pb(id);
                        Trans[from][to][id]=toid;
                    }
                }
                while (next_permutation(p+1,p+d+1));
            }
    bfs();
    char ans[48];int Mask=0;
    for (register int i=1;i<=n;i++)
    {
        bool f=false;
        for (register int id=1;id<=lim;id++)
            if (visited[1<<(i-1)][i][id])
            {
                ans[1]='A'+i-1;Mask=(1<<(i-1));
                f=true;break;
            }
        if (f) break;
    }
    for (register int i=2;i<=n;i++)
    {
        for (register int j=1;j<=n;j++)
            if (!(Mask&(1<<(j-1))))
            {
                int toMask=Mask|(1<<(j-1));bool f=false;
                for (register int id=1;id<=lim;id++)
                    if (visited[Mask][ans[i-1]-'A'+1][id])
                    {
                        int toid=Trans[ans[i-1]-'A'+1][j][id];
                        if (visited[toMask][j][toid])
                        {
                            ans[i]='A'+j-1;Mask=toMask;
                            f=true;break;
                        }
                    }
                if (f) break;
            }
    }
    for (register int i=1;i<=n;i++) printf("%c",ans[i]);
    printf("\n");
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
