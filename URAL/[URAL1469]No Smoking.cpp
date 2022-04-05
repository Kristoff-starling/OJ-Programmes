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
const double eps=1e-9;
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

const int MAXN=1e5;

int n;

inline bool islarger(double x,double y) {return x-y>eps;}
inline bool issmaller(double x,double y) {return x-y<-eps;}
inline bool isequal(double x,double y) {return (!islarger(x,y)) && (!issmaller(x,y));}

struct Vector
{
    double x,y;
    Vector () {}
    inline void input() {scanf("%lf%lf",&x,&y);}
    inline Vector (double _x,double _y) {x=_x;y=_y;}
    inline Vector operator + (Vector other) {return Vector(x+other.x,y+other.y);}
    inline Vector operator - (Vector other) {return Vector(x-other.x,y-other.y);}
    inline Vector operator * (int t) {return Vector(x*t,y*t);}
    inline double dot(Vector other) {return x*other.x+y*other.y;}
    inline double det(Vector other) {return x*other.y-y*other.x;}
};

struct Seg
{
    Vector pt1,pt2;
    inline void input() {pt1.input();pt2.input();if (pt1.x>pt2.x) swap(pt1,pt2);}
    inline bool on_seg(Vector pt) {return isequal((pt-pt1).det(pt-pt2),0) && (!islarger((pt-pt1).dot(pt-pt2),0));}
}a[MAXN+48];

inline bool isintersect(int id1,int id2)
{
    Seg s1=a[id1],s2=a[id2];
    if (s1.on_seg(s2.pt1) || s1.on_seg(s2.pt2) || s2.on_seg(s1.pt1) || s2.on_seg(s1.pt2)) return true;
    return (issmaller((s1.pt2-s1.pt1).det(s2.pt1-s1.pt1)*(s1.pt2-s1.pt1).det(s2.pt2-s1.pt1),0)) && (issmaller((s2.pt2-s2.pt1).det(s1.pt1-s2.pt1)*(s2.pt2-s2.pt1).det(s1.pt2-s2.pt1),0));
}

struct event
{
    int pos,ind,type;
    event () {}
    inline event(int _p,int _i,int _t) {pos=_p;ind=_i;type=_t;}
    inline bool operator < (const event &other) const
    {
        if (pos!=other.pos) return pos<other.pos;
        return type<other.type;
    }
}ele[MAXN*2+48];int tot;

int X;

inline double getpos(int id)
{
    if (a[id].pt1.x==a[id].pt2.x) return min(a[id].pt1.y,a[id].pt2.y);
    double delta=a[id].pt2.y-a[id].pt1.y;
    delta/=(a[id].pt2.x-a[id].pt1.x);
    delta*=(X-a[id].pt1.x);
    return a[id].pt1.y+delta;
}

inline void print(int x,int y)
{
    puts("YES");
    if (x>y) swap(x,y);
    printf("%d %d\n",x,y);
}

struct node
{
    int ind;
    node () {}
    inline node(int _i) {ind=_i;}
    inline bool operator < (const node &other) const {return issmaller(getpos(ind),getpos(other.ind));}
};set<node> s;

const int base=10000;
vector<int> hori[100048];

inline bool cmp(int x,int y) {return min(a[x].pt1.y,a[x].pt2.y)<min(a[y].pt1.y,a[y].pt2.y);}

inline bool check_hori()
{
    for (register int i=0;i<=base*2;i++)
        if (int(hori[i].size())>=2)
        {
            sort(hori[i].begin(),hori[i].end(),cmp);
            for (register int j=0;j<int(hori[i].size())-1;j++)
                if (isintersect(hori[i][j],hori[i][j+1])) {print(hori[i][j],hori[i][j+1]);return true;}
        }
    return false;
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d",&n);
    for (register int i=1;i<=n;i++)
    {
        a[i].input();
        if (a[i].pt1.x!=a[i].pt2.x) ele[++tot]=event(a[i].pt1.x,i,0),ele[++tot]=event(a[i].pt2.x,i,2);
        else ele[++tot]=event(a[i].pt1.x,i,1);
        if (a[i].pt1.x==a[i].pt2.x) hori[int(base+a[i].pt1.x)].pb(i);
    }
    if (check_hori()) return 0;
    sort(ele+1,ele+tot+1);
    for (register int i=1;i<=tot;i++)
    {
        X=ele[i].pos;
        if (ele[i].type==0)
        {
            set<node>::iterator iter=s.lower_bound(node(ele[i].ind));
            if (iter!=s.end() && isintersect(ele[i].ind,iter->ind)) {print(ele[i].ind,iter->ind);return 0;}
            if (iter!=s.begin())
            {
                --iter;
                if (isintersect(ele[i].ind,iter->ind)) {print(ele[i].ind,iter->ind);return 0;}
            }
            s.insert(node(ele[i].ind));
        }
        else if (ele[i].type==1)
        {
            set<node>::iterator iter=s.lower_bound(node(ele[i].ind));
            if (iter!=s.end() && isintersect(ele[i].ind,iter->ind)) {print(ele[i].ind,iter->ind);return 0;}
        }
        else
        {
            set<node>::iterator iter=s.lower_bound(node(ele[i].ind));
            if (iter!=(--s.end()) && iter!=s.begin())
            {
                set<node>::iterator iter1,iter2;
                iter1=iter;--iter1;iter2=iter;++iter2;
                if (isintersect(iter1->ind,iter2->ind)) {print(iter1->ind,iter2->ind);return 0;}
            }
            s.erase(iter);
        }
    }
    puts("NO");
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}