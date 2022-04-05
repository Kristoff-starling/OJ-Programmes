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

char s[20][20];
int table[300];
int RMask[6][6][6],CMask[6][6][6];

inline char Get(int X,int Y,int x,int y)
{
	return s[(X-1)*4+x][(Y-1)*4+y];
}

int rM[6],cM[6];
inline void rotate(int x,int y,int ti)
{
	int i;
	if (ti==0)
	{
		for (i=1;i<=4;i++) rM[i]=RMask[x][y][i],cM[i]=CMask[x][y][i];
		return;
	}
	if (ti==1)
	{
		for (i=1;i<=4;i++) rM[i]=CMask[x][y][i],cM[i]=RMask[x][y][5-i];
		return;
	}
	if (ti==2)
	{
		for (i=1;i<=4;i++) rM[i]=RMask[x][y][5-i],cM[i]=CMask[x][y][5-i];
		return;
	}
	if (ti==3)
	{
		for (i=1;i<=4;i++) rM[i]=CMask[x][y][5-i],cM[i]=RMask[x][y][i];
		return;
	}
	return;
}

int ans;

inline void dfs(int X,int Y,int cnt,vector<int> rMask,vector<int> cMask)
{
	if (X==5) {ans=min(ans,cnt);return;}
	if (cnt>ans) return;
	vector<int> nrMask,ncMask;
	int i,j,nx=X,ny=Y+1;
	if (ny>4) nx++,ny=1;
	for (i=0;i<=3;i++)
	{
		rotate(X,Y,i);
		bool f=true;
		for (j=1;j<=4;j++)
		{
			if (rMask[(X-1)*4+j-1]&rM[j]) {f=false;break;}
			if (cMask[(Y-1)*4+j-1]&cM[j]) {f=false;break;}
		}
		if (!f) continue;
		nrMask=rMask;ncMask=cMask;
		for (j=1;j<=4;j++)
		{
			nrMask[(X-1)*4+j-1]|=rM[j];
			ncMask[(Y-1)*4+j-1]|=cM[j];
		}
		dfs(nx,ny,cnt+i,nrMask,ncMask);
	}
}

int main ()
{
	int i,j,k1,k2,ca;ca=getint();
	for (i=0;i<=9;i++) table['0'+i]=i;
	for (i=1;i<=6;i++) table['A'+i-1]=9+i;
	while (ca--)
	{
		for (i=1;i<=16;i++) scanf("%s",s[i]+1);
		memset(RMask,0,sizeof(RMask));memset(CMask,0,sizeof(CMask));
		for (i=1;i<=4;i++)
			for (j=1;j<=4;j++)
				for (k1=1;k1<=4;k1++)
					for (k2=1;k2<=4;k2++)
					{
						RMask[i][j][k1]|=(1<<(table[Get(i,j,k1,k2)]-1));
						CMask[i][j][k2]|=(1<<(table[Get(i,j,k1,k2)]-1));
					}
		vector<int> t1,t2;
		for (i=1;i<=16;i++) t1.pb(0),t2.pb(0);
		ans=INF;dfs(1,1,0,t1,t2);
		printf("%d\n",ans);
	}
	return 0;
}
