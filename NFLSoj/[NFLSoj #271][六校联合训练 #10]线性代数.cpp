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

const int MAXN=50;

int n;
int a[148][148];
vector<int> List;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int X,Y;

bool taboo[148][148];

inline void Up() {List.pb(0);swap(a[X][Y],a[X-1][Y]);X--;}
inline void Down() {List.pb(2);swap(a[X][Y],a[X+1][Y]);X++;}
inline void Left() {List.pb(3);swap(a[X][Y],a[X][Y-1]);Y--;}
inline void Right() {List.pb(1);swap(a[X][Y],a[X][Y+1]);Y++;}

inline int getind(int x,int y) {return (x-1)*n+y;}

queue<int> q;
bool visited[148][148];
Pair vlist[10048];int vtot;
Pair pre[148][148];int ope[148][148];

inline void getpath(int x,int y,int op)
{
    int px=pre[x][y].x,py=pre[x][y].y;
    if (px) getpath(px,py,ope[x][y]);
    if (op>=0)
    {
        if (op==0) Up();
        if (op==1) Right();
        if (op==2) Down();
        if (op==3) Left();
    }
}

inline void Move_white(int tx,int ty)
{
    vtot=0;
    q.push(X);q.push(Y);pre[X][Y]=mp(0,0);visited[X][Y]=true;
    vlist[++vtot]=mp(X,Y);
    while (!q.empty())
    {
        int x=q.front();q.pop();int y=q.front();q.pop();
        if (x==tx && y==ty) break;
        for (register int dir=0;dir<=3;dir++)
        {
            int xx=x+dx[dir],yy=y+dy[dir];
            if (1<=xx && xx<=n && 1<=yy && yy<=n && !taboo[xx][yy] && !visited[xx][yy])
            {
                pre[xx][yy]=mp(x,y);ope[xx][yy]=dir;visited[xx][yy]=true;
                q.push(xx);q.push(yy);vlist[++vtot]=mp(xx,yy);
            }
        }
    }
    getpath(tx,ty,-1);
    for (register int i=1;i<=vtot;i++)
    {
        int x=vlist[i].x,y=vlist[i].y;
        pre[x][y]=mp(0,0);ope[x][y]=-1;visited[x][y]=false;
    }
    while (!q.empty()) q.pop();
}

inline void Move(int vv,int tx,int ty)
{
    int x,y;
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=n;j++)
            if (a[i][j]==vv) {x=i;y=j;break;}
    while (x>tx) taboo[x][y]=true,Move_white(x-1,y),taboo[x][y]=false,Down(),x--;
    while (y>ty) taboo[x][y]=true,Move_white(x,y-1),taboo[x][y]=false,Right(),y--;
    while (x<tx) taboo[x][y]=true,Move_white(x+1,y),taboo[x][y]=false,Up(),x++;
    while (y<ty) taboo[x][y]=true,Move_white(x,y+1),taboo[x][y]=false,Left(),y++;
}

inline void Falun_row()
{
    Right();Down();Left();Left();
    Up();Right();Down();Right();Up();
}

inline void Falun_col()
{
    Down();Right();Up();Up();
    Left();Down();Right();Down();Left();
}

inline void doit_row(int id)
{
    for (register int j=id;j>=2;j--)
    {
        if (a[id][j]==(id-1)*n+(j-1)) {taboo[id][j]=true;continue;}
        Move((id-1)*n+(j-1),id,j);
        assert(a[id][j]==(id-1)*n+(j-1));
        taboo[id][j]=true;
    }
    taboo[id][1]=true;
    if (a[id][1]!=(id-1)*n)
    {
        if (!a[id][1] && a[id-1][1]==(id-1)*n) Up();
        else
        {
            Move((id-1)*n,id-1,1);
            taboo[id-1][1]=true;Move_white(id-1,2);taboo[id-1][1]=false;
            Falun_row();
        }
    }
}

inline void doit_col(int id)
{
    for (register int i=id-1;i>=2;i--)
    {
        if (a[i][id]==(i-1)*n+(id-1)) {taboo[i][id]=true;continue;}
        Move((i-1)*n+(id-1),i,id);
        assert(a[i][id]==(i-1)*n+(id-1));
        taboo[i][id]=true;
    }
    taboo[1][id]=true;
    if (a[1][id]!=id-1)
    {
        if (!a[1][id] && a[1][id-1]==id-1) Left();
        else
        {
            Move(id-1,1,id-1);
            taboo[1][id-1]=true;Move_white(2,id-1);taboo[1][id-1]=false;
            Falun_col();
        }
    }
}

int table[10048];

int aa[48][48];
inline void dns(int Mask)
{
    for (register int i=min(n,3);i>=1;i--) aa[2][i]=Mask%7,Mask/=7;
    for (register int i=min(n,3);i>=1;i--) aa[1][i]=Mask%7,Mask/=7;
    for (register int i=1;i<=2;i++)
        for (register int j=1;j<=min(n,3);j++)
            if (aa[i][j]==1) X=i,Y=j;
}

inline int idns()
{
    int res=0;
    for (register int i=1;i<=2;i++)
        for (register int j=1;j<=min(n,3);j++)
            res=res*7+aa[i][j];
    return res;
}

bool vv[2000048];string Ope[2000048];
queue<int> Q;
inline void extend(int Mask)
{
    Q.push(Mask);vv[Mask]=true;
    while (!Q.empty())
    {
        Mask=Q.front();Q.pop();
        dns(Mask);
        for (register int dir=0;dir<=3;dir++)
        {
            int xx=X+dx[dir],yy=Y+dy[dir];
            if (1<=xx && xx<=2 && 1<=yy && yy<=min(n,3))
            {
                swap(aa[X][Y],aa[xx][yy]);
                int toMask=idns();
                if (!vv[toMask])
                {
                    vv[toMask]=true;
                    Ope[toMask]=Ope[Mask];
                    if (dir==0) Ope[toMask]+="2";
                    if (dir==1) Ope[toMask]+="3";
                    if (dir==2) Ope[toMask]+="0";
                    if (dir==3) Ope[toMask]+="1";
                    Q.push(toMask);
                }
                swap(aa[X][Y],aa[xx][yy]);
            }
        }
    }
}

inline void init_sta()
{
    int l[48];
    for (register int i=1;i<=min(n,3);i++) l[i]=a[1][i],l[min(n,3)+i]=a[2][i];
    sort(l+1,l+min(n*n+1,7));for (register int i=1;i<=min(n*n,6);i++) table[l[i]]=i;
    int Mask=0;for (register int i=1;i<=min(n*n,6);i++) Mask=Mask*7+i;
    extend(Mask);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=n;j++)
        {
            io.Get(a[i][j]);
            if (!a[i][j]) X=i,Y=j;
        }
    memset(ope,-1,sizeof(ope));
    for (register int i=n;i>=4;i--) {doit_row(i);doit_col(i);}
    if (n>=3) doit_row(3);
    init_sta();
    int Mask=0;
    for (register int i=1;i<=2;i++)
        for (register int j=1;j<=min(n,3);j++)
            Mask=Mask*7+table[a[i][j]];
    if (!vv[Mask]) {printf("Impossible\n");return 0;}
    for (auto item : List)
    {
        if (item==0) printf("U");
        if (item==1) printf("R");
        if (item==2) printf("D");
        if (item==3) printf("L");
    }
    for (register int i=int(Ope[Mask].size())-1;i>=0;i--)
    {
        int w=Ope[Mask][i]-'0';
        if (w==0) printf("U");
        if (w==1) printf("R");
        if (w==2) printf("D");
        if (w==3) printf("L");
    }
    printf("\n");
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
