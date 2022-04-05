// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

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
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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

inline bool islarger(LD x,LD y) {return x-y>eps;}
inline bool issmaller(LD x,LD y) {return x-y<-eps;}
inline bool isequal(LD x,LD y) {return !islarger(x,y) && !issmaller(x,y);}

struct Point
{
	LD x,y;
	Point () {}
	inline Point (LD _x,LD _y) {x=_x;y=_y;}
	inline LD ang() {return atan2(y,x);}
	inline Point operator + (Point other) {return Point(x+other.x,y+other.y);}
	inline Point operator - (Point other) {return Point(x-other.x,y-other.y);}
	inline Point operator * (LD t) {return Point(x*t,y*t);}
	inline LD dot(Point other) {return x*other.x+y*other.y;}
	inline LD det(Point other) {return x*other.y-y*other.x;}
};

struct Line
{
	Point pt1,pt2;
	Line () {}
	inline Line (Point _p1,Point _p2) {pt1=_p1,pt2=_p2;}
	inline LD ang() {return (pt2-pt1).ang();}
	inline bool OntheLeft(Point pt) {return islarger((pt2-pt1).det(pt-pt2),0);}
	inline bool OntheLine(Point pt) {return isequal((pt-pt1).det(pt-pt2),0);}
	inline bool isparallel(Line other) {return isequal((pt2-pt1).ang(),(other.pt2-other.pt1).ang());}
	inline Point intersection(Line other) {return pt1+(pt2-pt1)*(((other.pt2-other.pt1).det(other.pt1-pt1))/((other.pt2-other.pt1).det(pt2-pt1)));}
}L[10048];int tot;

struct Polygon
{
	vector<Line> edge;
	Polygon () {}
	inline void init() {edge.clear();}
	inline LD Area()
	{
		LD res=0;
		for (register int i=0;i<int(edge.size());i++) res+=edge[i].pt1.det(edge[i].pt2);
		res/=2;if (issmaller(res,0)) res=-res;
		return res;
	}
};

inline bool cmp_ang(Line x,Line y) {return issmaller((x.pt2-x.pt1).ang(),(y.pt2-y.pt1).ang());}

Line q[10048];int head,tail;Point a[10048];
inline Polygon HalfPlaneIntersection(Line L[],int N)
{
	sort(L+1,L+N+1,cmp_ang);
	head=tail=1;q[1]=L[1];
	for (register int i=2;i<=N;i++)
	{
		while (head<tail && !L[i].OntheLeft(a[tail-1])) tail--;
		while (head<tail && !L[i].OntheLeft(a[head])) head++;
		q[++tail]=L[i];
		if (head<tail && q[tail].isparallel(q[tail-1]))
		{
			if (q[tail-1].OntheLeft(q[tail].pt1)) q[tail-1]=q[tail];
			tail--;
		}
		if (head<tail) a[tail-1]=q[tail-1].intersection(q[tail]);
	}
	while (head+1<tail && !q[head].OntheLeft(a[tail-1])) tail--;
	a[tail]=q[tail].intersection(q[head]);
	Polygon res;res.init();
	for (register int i=head;i<=tail-1;i++) res.edge.pb(Line(a[i],a[i+1]));res.edge.pb(Line(a[tail],a[head]));
	return res;
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.flush();int n,m;Point a[148];
	scanf("%d",&n);
	for (register int i=1;i<=n;i++)
	{
		scanf("%d",&m);
		for (register int i=1;i<=m;i++) scanf("%Lf%Lf",&a[i].x,&a[i].y);
		for (register int i=1;i<=m-1;i++) L[++tot]=Line(a[i],a[i+1]);L[++tot]=Line(a[m],a[1]);
	}
	Polygon res=HalfPlaneIntersection(L,tot);
	printf("%.3Lf\n",res.Area());
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
