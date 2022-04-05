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
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-12;
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

class BalancingAct
{
	int n,m;
	int a1[48],a2[48],b[48],a1tot,a2tot;
	int valid1[100048],valid2[100048],v1tot,v2tot;
	int coef[148][10],lft[148],rght[148],cnum;
	const int delta=20;int rl[48],rr[48],add[48],rv[48];
	inline void getrange(int val)
	{
		int i,pt1=v2tot,pt2=1;	
		rght[cnum]=INF;lft[cnum]=-INF;
		for (i=1;i<=v1tot;i++)
		{
			while (pt1>1 && valid1[i]+valid2[pt1]>=val) pt1--;
			if (valid1[i]+valid2[pt1]<val) pt1++;
			if (pt1<=v2tot) rght[cnum]=min(rght[cnum],valid1[i]+valid2[pt1]); else pt1=v2tot;
			/*while (pt2<v2tot && valid1[i]+valid2[pt2]<=val) pt2++;
			if (valid1[i]+valid2[pt2]>val) pt2--;
			if (pt2>=1) lft[cnum]=max(lft[cnum],valid1[i]+valid2[pt2]); else pt2=1;
			if (val==-228977426 && i==1) cout<<pt2<<' '<<lft[cnum]<<"^^"<<endl;*/
		}
		for (i=v1tot;i>=1;i--)
		{
			while (pt2<v2tot && valid1[i]+valid2[pt2]<=val) pt2++;
			if (valid1[i]+valid2[pt2]>val) pt2--;
			if (pt2>=1) lft[cnum]=max(lft[cnum],valid1[i]+valid2[pt2]); else pt2=1;
		}
	}
	inline bool check()
	{
		int i,j,sum;
		for (i=1;i<=m;i++) if (rv[i]<=0 || rv[i]>1e8) return false;
		for (i=1;i<=cnum;i++)
		{
			sum=0;
			for (j=1;j<=m;j++)
				sum+=coef[i][j]*rv[j];
			if (lft[i]==rght[i] && sum!=lft[i]) return false;
			if (lft[i]!=rght[i] && (sum<=lft[i] || sum>=rght[i])) return false;
		}
		return true;
	}
	inline void dfs(int step)
	{
		int i;
		if (step==m+1)
		{
			for (i=1;i<=m;i++) rv[i]=b[i]+add[i];
			if (check())
				for (i=1;i<=m;i++) rl[i]=min(rl[i],rv[i]),rr[i]=max(rr[i],rv[i]);
			return;
		}
		for (i=-delta;i<=delta;i++) add[step]=i,dfs(step+1);
	}
	public:
		inline vector<string> recover(vector<int> labeled,vector<int> unlabeled)
		{
			n=int(labeled.size());m=int(unlabeled.size());int i,Mask,sub,sum;
			a1tot=n/2;a2tot=n-a1tot;
			for (i=1;i<=a1tot;i++) a1[i]=labeled[i-1];
			for (i=1;i<=a2tot;i++) a2[i]=labeled[a1tot-1+i];
			for (i=1;i<=m;i++) b[i]=unlabeled[i-1];
			v1tot=v2tot=0;
			for (Mask=0;Mask<=(1<<a1tot)-1;Mask++)
				for (sub=Mask;;sub=(sub-1)&Mask)
				{
					sum=0;
					for (i=1;i<=a1tot;i++)
						if (Mask&(1<<(i-1)))
							if (sub&(1<<(i-1))) sum+=a1[i]; else sum-=a1[i];
					valid1[++v1tot]=sum;
					if (!sub) break;
				}
			for (Mask=0;Mask<=(1<<a2tot)-1;Mask++)
				for (sub=Mask;;sub=(sub-1)&Mask)
				{
					sum=0;
					for (i=1;i<=a2tot;i++)
						if (Mask&(1<<(i-1)))
							if (sub&(1<<(i-1))) sum+=a2[i]; else sum-=a2[i];
					valid2[++v2tot]=sum;
					if (!sub) break;
				}
			sort(valid1+1,valid1+v1tot+1);sort(valid2+1,valid2+v2tot+1);
			cnum=0;
			for (Mask=1;Mask<=(1<<m)-1;Mask++)
				for (sub=Mask;;sub=(sub-1)&Mask)
				{
					sum=0;cnum++;
					for (i=1;i<=m;i++)
					{
						if (Mask&(1<<(i-1)))
						{if (sub&(1<<(i-1))) sum+=b[i],coef[cnum][i]=1; else sum-=b[i],coef[cnum][i]=-1;}
						else
							coef[cnum][i]=0;
					}
					getrange(sum);
					if (!sub) break;
				}
			for (i=1;i<=m;i++) rl[i]=rr[i]=b[i];
			dfs(1);
			vector<string> res;res.clear();
			for (i=1;i<=m;i++) if (rl[i]==rr[i]) res.pb("yes"); else res.pb("no");
			return res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn,mm;
	BalancingAct A;
	while (scanf("%d%d",&nn,&mm)!=EOF)
	{
		vector<int> xx,yy;int x;
		while (nn--) x=getint(),xx.pb(x);
		while (mm--) x=getint(),yy.pb(x);
		vector<string> Res=A.recover(xx,yy);
		for (int i=0;i<int(Res.size());i++) cout<<Res[i]<<' ';
		cout<<endl;
	}
	return 0;
}
*/
/*
15 4
{31415926,5358979,32384626,43383279,50288419,
71693993,75105820,9749445,92307816,40628620,
89986280,34825342,11706798,21480865,13282306}
{64709384,46095505,82231725,35940812}
*/
