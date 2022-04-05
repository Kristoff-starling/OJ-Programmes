#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#include <ctime>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=10007;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

class ConstructPolyline
{
	const int T=100;
	const double Tmin=1e-8;
	const double delta=0.999;
	int sta[148];int n;
	struct Vector
	{
		LL x,y,z;
		Vector () {}
		inline Vector(LL xx,LL yy,LL zz) {x=xx;y=yy;z=zz;}
		inline Vector operator + (const Vector other) {return Vector(x+other.x,y+other.y,z+other.z);}
		inline Vector operator - (const Vector other) {return Vector(x-other.x,y-other.y,z-other.z);}
		inline LL calc_dist() {return x*x+y*y+z*z;}
		inline LL dot(Vector other) {return x*other.x+y*other.y+z*other.z;}
	}a[148];
	public:
		inline LL maximizeLength(vector<int> x,vector<int> y,vector<int> z)
		{
			srand(time(NULL));
			int i;n=int(x.size());
			for (i=1;i<=n;i++) a[i]=Vector(x[i-1],y[i-1],z[i-1]);
			LL fans=0;
			/*for (register int tt=1;tt<=400;tt++)
			{
				random_shuffle(a+1,a+n+1);
				sta[1]=1;
				for (i=2;i<=n;i++) if (a[1].dot(a[i])>=0) sta[i]=1; else sta[i]=0;
				//for (i=1;i<=n;i++) cout<<sta[i]<<' ';
				//cout<<endl;
				Vector cur=Vector(0,0,0);
				for (i=1;i<=n;i++) if (sta[i]) cur=cur+a[i]; else cur=cur-a[i];
				LL ans=cur.calc_dist();Vector bv=cur;fans=max(fans,ans);
				double t=T;int pos;
				while (t>Tmin)
				{
					for (i=1;i<=5;i++)
					{
						pos=rand()%n+1;
						cur=bv;if (sta[pos]) cur=cur-a[pos],cur=cur-a[pos]; else cur=cur+a[pos],cur=cur+a[pos];
						if (cur.calc_dist()>ans)
						{
							ans=cur.calc_dist();
							bv=cur;sta[pos]^=1;
							fans=max(fans,ans);
						}
						else
						{
							double p=exp(double(cur.calc_dist()-ans)*1.0/t);
							if (double(rand())*1.0/RAND_MAX<p)
							{
								ans=cur.calc_dist();
								bv=cur;sta[pos]^=1;
							}
						}
					}
					t*=delta;
				}
			}*/
			for (register int tt=1;tt<=100000;tt++)
			{
				for (i=1;i<=n;i++) sta[i]=rand()%2;
				Vector cur=Vector(0,0,0);
				for (i=1;i<=n;i++) if (sta[i]) cur=cur+a[i]; else cur=cur-a[i];
				fans=max(fans,cur.calc_dist());
				for (i=1;i<=n;i++)
					if (a[i].dot(cur)>0) sta[i]=1; else sta[i]=0;
				cur=Vector(0,0,0);
				for (i=1;i<=n;i++) if (sta[i]) cur=cur+a[i]; else cur=cur-a[i];
				fans=max(fans,cur.calc_dist());
			}
			return fans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn,x,y,z;
	vector<int> xx,yy,zz;
	ConstructPolyline A;
	while (cin>>nn)
	{
		xx.clear();yy.clear();zz.clear();
		int i;
		for (i=1;i<=nn;i++) x=getint(),xx.pb(x);
		for (i=1;i<=nn;i++) y=getint(),yy.pb(y);
		for (i=1;i<=nn;i++) z=getint(),zz.pb(z);
		cout<<A.maximizeLength(xx,yy,zz)<<endl;
	}
	return 0;
}
*/
