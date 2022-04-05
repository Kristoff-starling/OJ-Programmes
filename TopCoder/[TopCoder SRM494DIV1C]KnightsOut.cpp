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

const int MOD=123456789;
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

inline int quick_pow(LL x,LL y)
{
	x%=MOD;LL res=1;
	while (y)
	{
		if (y&1) res=(res*x)%MOD,y--;
		x=(x*x)%MOD;y>>=1;
	}
	return int(res);
}

int n,m;

typedef bitset<488> bs;
bs ele[200][200];
int dx[]={-2,-1,1,2,2,1,-1,-2},dy[]={1,2,2,1,-1,-2,-2,-1};
bs equ[1048];int tot=0,res[1048];
bs base[1048];int Res[1048];
bool exist[1048];

int ind[200][200],Ind;

inline void Insert(int ii)
{
	int i;
	for (i=1;i<=Ind;i++)
		if (equ[ii][i]==1)
		{
			if (!exist[i])
			{
				exist[i]=true;
				base[i]=equ[ii];
				Res[i]=res[ii];
				return;
			}
			else
			{
				equ[ii]^=base[i];
				res[ii]^=Res[i];
			}
		}
}

class KnightsOut
{
	public:
		inline int count(int N,int M)
		{
			n=N;m=M;
			if (n<=2 && m<=2) return 1;
			if (n==1 || m==1) return 1;
			int i,j,dir,x,y;Ind=0;
			for (i=1;i<=2;i++)
				for (j=1;j<=m;j++)
					ind[i][j]=++Ind;
			for (i=3;i<=n;i++)
				ind[i][1]=++Ind;
			for (i=1;i<=2;i++)
				for (j=1;j<=m;j++)
					ele[i][j][ind[i][j]]=1;
			for (i=1;i<=n;i++)
				ele[i][1][ind[i][1]]=1;
			for (i=1;i<=n-2;i++)
				for (j=1;j<=m-1;j++)
				{
					ele[i+dx[3]][j+dy[3]]=0;
					for (dir=0;dir<=7;dir++)
					{
						if (dir==3) continue;
						x=i+dx[dir];y=j+dy[dir];
						if (1<=x && x<=n && 1<=y && y<=m) ele[i+dx[3]][j+dy[3]]^=ele[x][y];
					}
					ele[i+dx[3]][j+dy[3]]^=ele[i][j];
					ele[i+dx[3]][j+dy[3]][Ind+1]=1-ele[i+dx[3]][j+dy[3]][Ind+1];
				}
			tot=0;
			for (i=n-1;i<=n;i++)
				for (j=1;j<=m;j++)
				{
					++tot;equ[tot]=0;
					for (dir=0;dir<=7;dir++)
					{
						x=i+dx[dir];y=j+dy[dir];
						if (1<=x && x<=n && 1<=y && y<=m) equ[tot]^=ele[x][y];
					}
					equ[tot]^=ele[i][j];
					if (equ[tot][Ind+1]==1) res[tot]=0; else res[tot]=1;
				}
			for (i=1;i<=n-2;i++)
			{
				++tot;equ[tot]=0;
				for (dir=0;dir<=7;dir++)
				{
					x=i+dx[dir];y=m+dy[dir];
					if (1<=x && x<=n && 1<=y && y<=m) equ[tot]^=ele[x][y];
				}
				equ[tot]^=ele[i][m];
				if (equ[tot][Ind+1]==1) res[tot]=0; else res[tot]=1;
			}
			memset(exist,false,sizeof(exist));
			for (i=1;i<=Ind;i++) base[i]=0,Res[i]=0;
			for (i=1;i<=tot;i++) Insert(i);
			int cnt=0;
			for (i=1;i<=Ind;i++) if (!exist[i]) cnt++;
			return quick_pow(2,cnt);
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn,mm;
	KnightsOut A;
	while (cin>>nn>>mm)
		cout<<A.count(nn,mm)<<endl;
	return 0;
}
*/
