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

int dpx[1648][848],sumx[1648][848];
int dpy[1648][848],sumy[1648][848];
int dpb[1648][848];
int DP[1648][1648];

class FoxJumping
{
	inline int mod(int x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}
	public:
		inline int getCount(int tx,int ty,int mx,int my,int r,vector<int> bad)
		{
			int i,j,k;
			memset(dpx,0,sizeof(dpx));memset(sumx,0,sizeof(sumx));
			dpx[0][0]=1;
			for (j=0;j<=tx;j++) sumx[0][j]=1;
			for (i=1;i<=r;i++)
				for (j=0;j<=tx;j++)
				{
					dpx[i][j]=sumx[i-1][j];if (j-mx>=1) dpx[i][j]=mod(dpx[i][j]-sumx[i-1][j-mx-1]);
					sumx[i][j]=(j==0?dpx[i][j]:mod(sumx[i][j-1]+dpx[i][j]));
				}
			memset(dpy,0,sizeof(dpy));memset(sumy,0,sizeof(sumy));
			dpy[0][0]=1;
			for (j=0;j<=ty;j++) sumy[0][j]=1;
			for (i=1;i<=r;i++)
				for (j=0;j<=ty;j++)
				{
					dpy[i][j]=sumy[i-1][j];if (j-my>=1) dpy[i][j]=mod(dpy[i][j]-sumy[i-1][j-my-1]);
					sumy[i][j]=(j==0?dpy[i][j]:mod(sumy[i][j-1]+dpy[i][j]));
				}
			bad.pb(0);
			memset(dpb,0,sizeof(dpb));
			dpb[0][0]=1;
			for (i=1;i<=r;i++)
				for (j=0;j<=min(tx,ty);j++)
					for (k=0;k<int(bad.size());k++)
						if (j-bad[k]>=0) dpb[i][j]=mod(dpb[i][j]+dpb[i-1][j-bad[k]]);
			memset(DP,0,sizeof(DP));
			DP[0][0]=1;
			for (i=0;i<=r;i++)
				for (j=0;j<=r-i;j++)
				{
					if (i) DP[i][j]=mod(DP[i][j]+DP[i-1][j]);
					if (j) DP[i][j]=mod(DP[i][j]+DP[i][j-1]);
				}
			int ans=0,curans,xl,yl;
			for (i=0;i<=r;i++)
				for (j=0;j<=min(tx,ty);j++)
				{
					curans=dpb[i][j];
					xl=tx-j;yl=ty-j;
					curans=(((curans*dpx[r-i][xl])%MOD*dpy[r-i][yl])%MOD*DP[i][r-i])%MOD;
					//cout<<i<<' '<<j<<' '<<curans<<endl;
					if (i%2==0) ans=mod(ans+curans); else ans=mod(ans-curans);
				}
			return ans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	FoxJumping A;
	int ttx,tty,mmx,mmy,rr,bn,x;
	vector<int> bb;
	while (cin>>ttx>>tty>>mmx>>mmy>>rr>>bn)
	{
		bb.clear();
		while (bn--) cin>>x,bb.pb(x);
		cout<<A.getCount(ttx,tty,mmx,mmy,rr,bb)<<endl;
	}
	return 0;
}
*/
