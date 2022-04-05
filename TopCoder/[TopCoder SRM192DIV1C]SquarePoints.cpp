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
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline double myabs(double x)
{
	if (x>eps) return x;
	if (x<-eps) return -x;
	return double(0);
}

pii a[148];int n;
struct line
{
	pii dir;pii pt;
}L[148];
vector<pii> linept[148];
inline int gcd(int x,int y) {return !y?x:gcd(y,x%y);}
inline line GetLine(pii x,pii y)
{
	line res;
	res.dir=mp(y.x-x.x,y.y-x.y);res.pt=x;
	int gg=gcd(myabs(res.dir.x),myabs(res.dir.y));
	res.dir.x/=gg;res.dir.y/=gg;
	return res;
}
inline double getlen(pii vec) {return sqrt(vec.x*vec.x+vec.y*vec.y);}
inline double getpointdist(pii pt1,pii pt2) {return sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y));}
inline double getlinedist(line l,pii pt)
{
	pii dir2=mp(pt.x-l.pt.x,pt.y-l.pt.y);
	double res=l.dir.x*dir2.y-l.dir.y*dir2.x;
	return res/getlen(l.dir);
}
vector<pii> pos,neg;
inline bool cmpdist(pii x,pii y) {return myabs(getlinedist(L[1],x))-myabs(getlinedist(L[1],y))<-eps;}
inline bool cmpcor(pii x,pii y) {return x.x-y.x<-eps;}
inline line getparallel(line l,pii pt) {return line{l.dir,pt};}
inline line getprependicular(line l,pii pt) {pii dd=l.dir;swap(dd.x,dd.y);dd.y=-dd.y;return line{dd,pt};}
inline double linedist(line l1,line l2) {return myabs(getlinedist(l1,l2.pt));}
inline line Move(line l,double dist)
{
	pii mdir=l.dir;swap(mdir.x,mdir.y);mdir.y=-mdir.y;line res;res.dir=l.dir;
	if (mdir.x==0)
	{
		res.pt=l.pt;res.pt.y+=dist;
		return res;
	}
	double dd=myabs(dist);
	double dy=dd*sin(atan(mdir.y*1.0/mdir.x)),dx=dd*cos(atan(mdir.y*1.0/mdir.x));
	if (dd!=dist) dx=-dx,dy=-dy;
	res.pt=l.pt;res.pt.x+=dx;res.pt.y+=dy;
	return res;
}

inline bool check_equal(pii dir1,pii dir2)
{
	if (myabs(dir1.x)<eps) return myabs(dir2.x)<eps;
	if (myabs(dir1.y)<eps) return myabs(dir2.y)<eps;
	return dir2.x/dir1.x==dir2.y/dir1.y;
}

struct Square
{
	line l[10];
	inline bool operator == (const Square &x) const
	{
		int i,j;
		for (i=1;i<=4;i++)
		{
			bool f=false;
			for (j=1;j<=4;j++)
			{
				pii dir1=l[i].dir,dir2=x.l[j].dir,dir3=x.l[j].dir;dir3.x=-dir3.x;dir3.y=-dir3.y;
				if ((check_equal(dir1,dir2) || check_equal(dir1,dir3)) && myabs(getlinedist(l[i],x.l[j].pt))<eps) {f=true;break;}
			}
			if (!f) return false;
		}
		return true;
	}
}ss[148];int stot;

class SquarePoints
{
	public:
		inline bool specialjudge()
		{
			line another=getprependicular(L[1],pos[0]);
			int i;
			for (i=0;i<int(pos.size());i++) if (myabs(getlinedist(another,pos[i]))>eps) return false;
			int ppos=0,nneg=0;
			for (i=0;i<int(linept[1].size());i++)
			{
				double di=getlinedist(another,linept[1][i]);
				if (di>eps) ppos++;if (di<-eps) nneg++;
			}
			if (ppos && nneg) return false;
			return true;
		}
		line another1,another2;
		inline bool specialjudge2()
		{
			another1=L[1];another2=L[1];int cnt=0,i;
			linept[2].clear();linept[3].clear();
			for (i=0;i<int(pos.size());i++)
			{
				if (myabs(getlinedist(another1,pos[i]))<eps) {linept[2].pb(pos[i]);continue;}
				if (myabs(getlinedist(another2,pos[i]))<eps) {linept[3].pb(pos[i]);continue;}
				if (!cnt) {another1=getprependicular(L[1],pos[i]);cnt++;linept[2].pb(pos[i]);continue;}
				if (cnt==1) {another2=getprependicular(L[1],pos[i]);cnt++;linept[3].pb(pos[i]);continue;}
				return false;
			}
			if (cnt<2) return false;
			int ppos=0,nneg=0;
			for (i=0;i<int(linept[1].size());i++)
			{
				double di=getlinedist(another1,linept[1][i]);
				if (di>eps) ppos++;if (di<-eps) nneg++;
			}
			for (i=0;i<int(linept[3].size());i++)
			{
				double di=getlinedist(another1,linept[3][i]);
				if (di>eps) ppos++;if (di<-eps) nneg++;
			}
			if (ppos && nneg) return false;
			ppos=0;nneg=0;
			for (i=0;i<int(linept[1].size());i++)
			{
				double di=getlinedist(another2,linept[1][i]);
				if (di>eps) ppos++;if (di<-eps) nneg++;
			}
			for (i=0;i<int(linept[2].size());i++)
			{
				double di=getlinedist(another2,linept[2][i]);
				if (di>eps) ppos++;if (di<-eps) nneg++;
			}
			if (ppos && nneg) return false;
			double cdist=linedist(another1,another2);
			for (i=0;i<int(pos.size());i++)
				if (myabs(getlinedist(L[1],pos[i]))-cdist>eps) return false;
			return true;
		}
		inline string determine(vector<int> X,vector<int> Y)
		{
			n=int(X.size());int i,j,k;stot=0;
			for (i=1;i<=n;i++) a[i]=mp(X[i-1],Y[i-1]);
			for (i=1;i<=n-1;i++)
				for (j=i+1;j<=n;j++)
				{
					L[1]=GetLine(a[i],a[j]);linept[1].clear();
					linept[1].pb(a[i]);linept[1].pb(a[j]);
					pos.clear();neg.clear();
					for (k=1;k<=n;k++)
						if (k!=i && k!=j)
						{
							double di=getlinedist(L[1],a[k]);
							if (myabs(di)<eps) {linept[1].pb(a[k]);continue;}
							if (di>eps) pos.pb(a[k]); else neg.pb(a[k]);
						}
					if (int(pos.size()) && int(neg.size())) continue;
					while (int(neg.size())) pos.pb(neg.back()),neg.pop_back();
					if (!int(pos.size())) return "ambiguous";
					if (specialjudge()) return "ambiguous";
					if (specialjudge2())
					{
						Square ins;ins.l[1]=L[1];ins.l[3]=another1;ins.l[4]=another2;
						double mdist=linedist(another1,another2);
						line l1=Move(L[1],mdist),l2=Move(L[1],-mdist);
						if (myabs(myabs(getlinedist(L[1],linept[2][0]))+myabs(getlinedist(l1,linept[2][0]))-mdist)<eps) ins.l[2]=l1; else ins.l[2]=l2;
						if (!stot) {ss[++stot]=ins;continue;}
						if (stot==1 && !(ins==ss[1])) return "ambiguous";
					}
					sort(pos.begin(),pos.end(),cmpdist);
					L[2]=getparallel(L[1],pos.back());linept[2].clear();linept[2].pb(pos.back());
					pos.pop_back();double cmpdd=getlinedist(L[2],linept[2][0]);
					while (int(pos.size()) && myabs(getlinedist(L[2],pos.back())-cmpdd)<eps) linept[2].pb(pos.back()),pos.pop_back();
					line posmost=getprependicular(L[1],linept[1][0]),negmost=getprependicular(L[1],linept[1][0]);
					for (k=1;k<int(linept[1].size());k++)
					{
						if (getlinedist(posmost,linept[1][k])>eps) posmost=getprependicular(L[1],linept[1][k]);
						if (getlinedist(negmost,linept[1][k])<-eps) negmost=getprependicular(L[1],linept[1][k]);
					}
					for (k=0;k<int(linept[2].size());k++)
					{
						if (getlinedist(posmost,linept[2][k])>eps) posmost=getprependicular(L[1],linept[2][k]);
						if (getlinedist(negmost,linept[2][k])<-eps) negmost=getprependicular(L[1],linept[2][k]);
					}
					if (!int(pos.size()))
					{
						if (linedist(L[1],L[2])-linedist(posmost,negmost)>eps) return "ambiguous";
						if (linedist(L[1],L[2])-linedist(posmost,negmost)<-eps) continue;
						Square ins;ins.l[1]=L[1];ins.l[2]=L[2];ins.l[3]=posmost;ins.l[4]=negmost;
						if (!stot) {ss[++stot]=ins;continue;}
						if (stot==1 && !(ins==ss[1])) return "ambiguous";
					}
					for (k=0;k<int(pos.size());k++)
					{
						if (getlinedist(posmost,pos[k])>eps) posmost=getprependicular(L[1],pos[k]);
						if (getlinedist(negmost,pos[k])<-eps) negmost=getprependicular(L[1],pos[k]);
					}
					bool f=true;
					for (k=0;k<int(pos.size());k++)
						if (myabs(getlinedist(posmost,pos[k]))>eps && myabs(getlinedist(negmost,pos[k]))>eps) {f=false;break;}
					if (!f) continue;
					int cnt1=0,cnt2=0;
					for (k=0;k<int(pos.size());k++)
					{
						if (myabs(getlinedist(posmost,pos[k]))<eps) cnt1++;
						if (myabs(getlinedist(negmost,pos[k]))<eps) cnt2++;
					}
					if (!cnt1 || !cnt2)
					{
						if (linedist(L[1],L[2])-linedist(posmost,negmost)<-eps) continue;
						double delta=linedist(L[1],L[2])-linedist(posmost,negmost);
						if (cnt1)
						{
							line l1=Move(negmost,delta),l2=Move(negmost,-delta);
							if (myabs(linedist(L[1],L[2])-linedist(posmost,l1))<eps) negmost=l1; else negmost=l2;
						}
						else
						{
							line l1=Move(posmost,delta),l2=Move(posmost,-delta);
							if (myabs(linedist(L[1],L[2])-linedist(negmost,l1))<eps) posmost=l1; else posmost=l2;
						}
						Square ins;ins.l[1]=L[1];ins.l[2]=L[2];ins.l[3]=posmost;ins.l[4]=negmost;
						if (!stot) {ss[++stot]=ins;continue;}
						if (stot==1 && !(ins==ss[1])) return "ambiguous";
					}
					if (myabs(linedist(L[1],L[2])-linedist(posmost,negmost))>eps) continue;
					Square ins;ins.l[1]=L[1];ins.l[2]=L[2];ins.l[3]=posmost;ins.l[4]=negmost;
					if (!stot) {ss[++stot]=ins;continue;}
					if (stot==1 && !(ins==ss[1])) return "ambiguous";
				}
			if (stot) return "consistent"; else return "inconsistent";
		}
};

/*---Debug Part---*/
/*
int main ()
{
	SquarePoints A;
	vector<int> xx,yy;int nn;
	while (scanf("%d",&nn)!=EOF)
	{
		xx.clear();yy.clear();
		for (register int i=1;i<=nn;i++)
		{
			int x=getint();
			xx.pb(x);
		}
		for (register int i=1;i<=nn;i++)
		{
			int x=getint();
			yy.pb(x);
		}
		cout<<A.determine(xx,yy)<<endl;
	}
	return 0;
}
*/
/*
5
{0,0,10,10,4}
{0,10,0,10,5}
8
{2,3,0,0,5,5,3,2}
{0,0,2,3,3,2,5,5}
48
{1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,4,5,6,7,8,9,10,11,12,13,13,13,13,13,13,13,13,13,13,13,13,13,12,11,10,9,8,7,6,5,4,3,2}
{1,2,3,4,5,6,7,8,9,10,11,12,13,13,13,13,13,13,13,13,13,13,13,13,13,12,11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1}
6
{0,4,8,-5,-1,3}
{0,3,6,15,18,21}
7
{0,4,8,-5,-1,3,16}
{0,3,6,15,18,21,12}
5
{0,4,8,-5,-1}
{0,3,6,15,18}
5
{0,1,2,0,100}
{0,0,0,1,140}
5
{0,0,0,1,1}
{0,1,2,2,0}
6
{0,1,2,0,2,0}
{0,0,0,2,2,3}
5
1 2 3 0 0
0 0 0 1 2
*/
