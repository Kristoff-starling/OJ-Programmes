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
const int MOD=1e9+7;
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

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1000;

int n,m,k;
int ind[MAXN+48];
bool exist[MAXN+48];

inline LB myabs(LB x) {if (x>eps) return x;if (x-eps) return -x;return 0;}
inline bool islarger(LB x,LB y) {return x-y>eps;}
inline bool issmaller(LB x,LB y) {return x-y<-eps;}
inline bool isequal(LB x,LB y) {return myabs(x-y)<eps;}

struct Vector
{
	LB x,y;
	Vector () {}
	inline void input () {x=getint();y=getint();}
	inline Vector (LB xx,LB yy) {x=xx;y=yy;}
	inline LB calc_k()
	{
		if (isequal(x,0)) return islarger(y,0)?INF:-INF;
		return y/x;
	}
	inline Vector operator + (Vector other) {return Vector(x+other.x,y+other.y);}
	inline Vector operator - (Vector other) {return Vector(x-other.x,y-other.y);}
	inline Vector operator * (LB t) {return Vector(x*t,y*t);}
	inline LB dot(Vector other) {return x*other.x+y*other.y;}
	inline LB det(Vector other) {return x*other.y-y*other.x;}
	inline bool operator < (const Vector &other) const {return x<other.x;}
}a[MAXN+48],A[MAXN+48];int tot=0;
Vector conv[MAXN+48],sta[MAXN+48];int ctot,stot;

inline LL calc_area()
{
	sort(A+1,A+tot+1);
	stot=1;sta[1]=A[1];int i;
	//for (i=1;i<=tot;i++) cout<<A[i].x<<' '<<A[i].y<<endl;
	for (i=2;i<=tot;i++)
	{
		while (stot>1 && (sta[stot]-sta[stot-1]).calc_k()>=(A[i]-sta[stot]).calc_k()) stot--;
		sta[++stot]=A[i];
	}
	ctot=0;for (i=1;i<=stot;i++) conv[++ctot]=sta[i];
	stot=1;sta[1]=A[1];
	for (i=2;i<=tot;i++)
	{
		while (stot>1 && (sta[stot]-sta[stot-1]).calc_k()<=(A[i]-sta[stot]).calc_k()) stot--;
		sta[++stot]=A[i];
	}
	for (i=stot-1;i>=2;i--) conv[++ctot]=sta[i];
	LB ans=0;Vector curv=conv[2]-conv[1];
	for (i=3;i<=ctot;i++) ans=ans+myabs(curv.det(conv[i]-conv[1])),curv=conv[i]-conv[1];
	LL res=(LL)(ans+0.5);
	return res;
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int i,x;LL lastans=-1;n=getint();m=getint();
	for (i=1;i<=n;i++) a[i].input();
	while (m--)
	{
		memset(exist,true,sizeof(exist));
		k=getint();for (i=1;i<=k;i++) x=getint(),x=(lastans+x)%n+1,exist[x]=false;
		tot=0;for (i=1;i<=n;i++) if (exist[i]) A[++tot]=a[i];
		lastans=calc_area();
		printf("%lld\n",lastans);
	}
	return 0;
}
