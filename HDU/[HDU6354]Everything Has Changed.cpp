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
const double eps=1e-15;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=100;

inline LB myabs(LB x) {if (x>eps) return x;if (x<-eps) return -x;return 0;}
inline bool islarger(LB x,LB y) {return x-y>eps;}
inline bool issmaller(LB x,LB y) {return x-y<-eps;}
inline bool isequal(LB x,LB y) {return myabs(x-y)<eps;}

LB R,r;int n;

struct Vector
{
	LB x,y;
	Vector () {}
	inline Vector (LB xx,LB yy) {x=xx;y=yy;}
	inline LB calc_len() {return sqrt(x*x+y*y);}
	inline Vector operator + (Vector other) {return Vector(x+other.x,y+other.y);}
	inline Vector operator - (Vector other) {return Vector(x-other.x,y-other.y);}
	inline Vector operator * (double t) {return Vector(x*t,y*t);}
	inline LB dot (Vector other) {return x*other.x+y*other.y;}
	inline LB det (Vector other) {return x*other.y-y*other.x;} 
}big,cur;
pair<Vector,LB> a[MAXN+48];

LB C;
bool visited[MAXN+48],vv[MAXN+48];

inline bool isin()
{
	return issmaller((cur-big).calc_len()+r,R);
}

inline bool isout()
{
	return !islarger(R+r,(cur-big).calc_len());
}

inline void Clear()
{
	memset(visited,false,sizeof(visited));
	memset(vv,false,sizeof(vv));
}

inline bool isqie(int ind1,int ind2)
{
	return isequal((a[ind1].x-a[ind2].x).calc_len(),a[ind1].y+a[ind2].y);
}

int q[MAXN+48],head,tail;
inline void spfa()
{
	head=1;tail=0;int i;
	for (i=1;i<=n;i++) if (visited[i]) q[++tail]=i;
	while (head<=tail)
	{
		int cc=q[head++];
		for (i=1;i<=n;i++)
			if (!visited[i] && !vv[i] && isqie(cc,i))
			{
				vv[i]=true;
				q[++tail]=i;
			}
	}
	for (i=1;i<=n;i++)
		if (vv[i]) C+=pi*2*a[i].y;
}

int main ()
{
	int ca;ca=getint();
	while (ca--)
	{
		int i;
		n=getint();R=getint();big=Vector(0,0);
		C=pi*2*R;
		//Clear();
		for (register int u=1;u<=n;u++)
		{
			cur.x=getint();cur.y=getint();r=getint();
			a[u]=mp(cur,r);
			if (isin()) continue;
			if (isout()) continue;
			visited[u]=true;
			LB Len=(cur-big).calc_len();
			LB COS=(R*R+Len*Len-r*r)/(R*Len*2);
			LB ang=acos(COS)*2;
			C-=R*ang;
			COS=(r*r+Len*Len-R*R)/(r*Len*2);
			ang=acos(COS)*2;
			C+=r*ang;
		}
		//spfa();
		double ans=C;
		printf("%.20lf\n",ans);
	}
	return 0;
}
