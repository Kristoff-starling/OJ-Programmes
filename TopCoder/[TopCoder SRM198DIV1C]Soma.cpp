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
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int n,m;

struct Matrix
{
	int b[4][4];
	Matrix () {memset(b,0,sizeof(b));}
	inline void clear() {memset(b,0,sizeof(b));}
	inline Matrix (int x,int y,int z) {memset(b,0,sizeof(b));b[1][1]=x;b[1][2]=y;b[1][3]=z;}
	inline void init_I() {for (register int i=1;i<=3;i++) b[i][i]=1;}
	inline bool operator < (const Matrix &other) const
	{
		if (b[1][3]!=other.b[1][3]) return b[1][3]<other.b[1][3];
		if (b[1][1]!=other.b[1][1]) return b[1][1]<other.b[1][1];
		return b[1][2]<other.b[1][2];
	}
	inline bool operator == (const Matrix &other) const
	{
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				if (b[i][j]!=other.b[i][j]) return false;
		return true;
	}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				res.b[i][j]=b[i][j]+ma.b[i][j];
		return res;
	}
	inline Matrix operator - (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				res.b[i][j]=b[i][j]-ma.b[i][j];
		return res;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=3;i++)
			for (register int j=1;j<=3;j++)
				for (register int k=1;k<=3;k++)
					res.b[i][j]+=b[i][k]*ma.b[k][j];
		return res;
	}
}rx,ry,rz;

inline Matrix quick_pow(Matrix x,int y)
{
	Matrix res;res.clear();res.init_I();
	while (y)
	{
		if (y&1) res=res*x;
		x=x*x;y>>=1;
	}
	return res;
}

typedef vector<Matrix> soma;

struct somapos
{
	int x,y,z;
	somapos () {}
	inline somapos(int xx,int yy,int zz) {x=xx;y=yy;z=zz;}
	inline bool operator < (const somapos &other) const
	{
		if (z!=other.z) return z<other.z;
		if (x!=other.x) return x<other.x;
		return y<other.y;
	}
}P[48];int tot=0;

soma base[48];
vector<soma> candidate[48];
int Cx[48][48][5],Cy[48][48][5],Cz[48][48][5];int ctot[48],wtot[48];

inline soma Move(soma ori,Matrix pos,somapos topos)
{
	Matrix delta;delta.clear();
	for (register int i=1;i<=3;i++) delta.b[1][i]=-pos.b[1][i];
	delta.b[1][1]+=topos.x;delta.b[1][2]+=topos.y;delta.b[1][3]+=topos.z;
	for (register int i=0;i<int(ori.size());i++) ori[i]=ori[i]+delta;
	return ori;
}

inline soma getsoma(soma ori,int dx,int dy,int dz)
{
	for (register int k=0;k<int(ori.size());k++)
	for (register int i=2;i<=3;i++)
		for (register int j=1;j<=3;j++)
			assert(ori[k].b[i][j]==0);
	for (register int i=0;i<int(ori.size());i++)
	{
		ori[i]=ori[i]*quick_pow(rx,dx);
		ori[i]=ori[i]*quick_pow(ry,dy);
		ori[i]=ori[i]*quick_pow(rz,dz);
	}
	sort(ori.begin(),ori.end());
	return ori;
}

inline bool issame(soma x,soma y)
{
	Matrix cmp=x[0]-y[0];
	for (register int i=1;i<int(x.size());i++)
		if (!(x[i]-y[i]==cmp)) return false;
	return true;
}

inline void init_soma()
{
	for (register int i=1;i<=7;i++) base[i].clear(),candidate[i].clear();
	
	base[1].pb(Matrix(1,1,1));base[1].pb(Matrix(2,1,1));base[1].pb(Matrix(3,1,1));base[1].pb(Matrix(1,2,1));
	base[2].pb(Matrix(1,1,1));base[2].pb(Matrix(2,1,1));base[2].pb(Matrix(3,1,1));base[2].pb(Matrix(2,2,1));
	base[3].pb(Matrix(2,1,1));base[3].pb(Matrix(3,1,1));base[3].pb(Matrix(1,2,1));base[3].pb(Matrix(2,2,1));
	base[4].pb(Matrix(1,1,1));base[4].pb(Matrix(2,1,1));base[4].pb(Matrix(1,2,1));
	base[5].pb(Matrix(2,1,1));base[5].pb(Matrix(2,1,2));base[5].pb(Matrix(1,2,1));base[5].pb(Matrix(2,2,1));
	base[6].pb(Matrix(1,1,1));base[6].pb(Matrix(1,1,2));base[6].pb(Matrix(1,2,1));base[6].pb(Matrix(2,2,1));
	base[7].pb(Matrix(1,1,1));base[7].pb(Matrix(2,1,1));base[7].pb(Matrix(2,1,2));base[7].pb(Matrix(2,2,1));

	rx.clear();ry.clear();rz.clear();
	rx.b[1][1]=1;rx.b[2][3]=1;rx.b[3][2]=-1;
	ry.b[1][3]=-1;ry.b[2][2]=1;ry.b[3][1]=1;
	rz.b[1][2]=1;rz.b[2][1]=-1;rz.b[3][3]=1;
	
	for (register int i=1;i<=7;i++) sort(base[i].begin(),base[i].end());
	for (register int i=1;i<=7;i++)
		for (register int dx=0;dx<=3;dx++)
			for (register int dy=0;dy<=3;dy++)
				for (register int dz=0;dz<=3;dz++)
				{
					soma ns=getsoma(base[i],dx,dy,dz);bool f=true;
					for (register int j=0;j<int(candidate[i].size());j++)
						if (issame(candidate[i][j],ns)) {f=false;break;}
					if (f) candidate[i].pb(ns);
				}
}

bool exist[48][48][48];

class Soma
{
	int ans;
	int a[48][48];
	inline int dfs(int used)
	{
		int res=0;
		if (used==127) return 1;
		int tox,toy,toz;
		for (register int i=1;i<=27;i++)
			if (exist[P[i].x][P[i].y][P[i].z]) {tox=P[i].x;toy=P[i].y;toz=P[i].z;break;}
		for (register int i=1;i<=7;i++)
			if (!(used&(1<<(i-1))))
			{
				for (register int j=1;j<=ctot[i];j++)
				{
					int deltax=tox-Cx[i][j][1],deltay=toy-Cy[i][j][1],deltaz=toz-Cz[i][j][1];
					bool valid=true;
					for (register int k=2;k<=wtot[i];k++)
					{
						int xx=Cx[i][j][k]+deltax,yy=Cy[i][j][k]+deltay,zz=Cz[i][j][k]+deltaz;
						if (!exist[xx][yy][zz]) {valid=false;break;}
					}
					if (valid)
					{
						for (register int k=1;k<=wtot[i];k++)
						{
							int xx=Cx[i][j][k]+deltax,yy=Cy[i][j][k]+deltay,zz=Cz[i][j][k]+deltaz;
							exist[xx][yy][zz]=false;
						}
						used|=(1<<(i-1));
						res+=dfs(used);
						for (register int k=1;k<=wtot[i];k++)
						{
							int xx=Cx[i][j][k]+deltax,yy=Cy[i][j][k]+deltay,zz=Cz[i][j][k]+deltaz;
							exist[xx][yy][zz]=true;
						}
						used^=(1<<(i-1));
					}
				}
			}
		return res;
	}
	inline void toarray()
	{
		for (register int i=1;i<=7;i++)
		{
			ctot[i]=int(candidate[i].size());
			wtot[i]=((i==4)?3:4);
			for (register int j=1;j<=ctot[i];j++)
				for (register int k=1;k<=wtot[i];k++)
				{
					Cx[i][j][k]=candidate[i][j-1][k-1].b[1][1];
					Cy[i][j][k]=candidate[i][j-1][k-1].b[1][2];
					Cz[i][j][k]=candidate[i][j-1][k-1].b[1][3];
				}
		}
	}
	public:
		inline int letMeCountTheWays(vector<string> pattern)
		{
			n=int(pattern.size());m=int(pattern[0].size());
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=m;j++)
					a[i][j]=pattern[i-1][j-1]-'0';
			init_soma();toarray();
			tot=0;memset(exist,false,sizeof(exist));
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=m;j++)
					for (register int k=1;k<=a[i][j];k++)
					{
						P[++tot]=somapos(i,j,k);
						exist[i][j][k]=true;
					}
			sort(P+1,P+tot+1);
			for (register int i=1;i<=27;i++) ind[P[i].x][P[i].y][P[i].z]=i;
			return dfs(0);
		}
};

#ifdef LOCAL
int main ()
{
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
	int nn;vector<string> vv;string ss;
	Soma A;
	while (cin>>nn)
	{
		vv.clear();
		for (register int i=1;i<=nn;i++) cin>>ss,vv.pb(ss);
		double t=clock();
		cout<<A.letMeCountTheWays(vv)<<endl;
		cerr<<"Time: "<<(clock()-t)/CLOCKS_PER_SEC<<endl;
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif