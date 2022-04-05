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

inline LL getLL()
{
	char ch;LL res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return res;
}

int dp[50048][148];
int nxt[500048][16];

int n,m;
string a[20],b[500048];
int pos[20];
int val[50048][20];vector<int> avai[50048];
queue<int> q;
inline int count(int Mask,int pos)
{
	int i,res=0;
	for (i=n;i>=pos+1;i--)
		if (Mask&(1<<(i-1))) res++;
	return res;
}

inline void init_val()
{
	int Mask,i;
	for (Mask=0;Mask<=(1<<n)-1;Mask++)
	{
		avai[Mask].clear();
		for (i=1;i<=n;i++)
			if (!(Mask&(1<<(i-1))))
			{
				avai[Mask].pb(i);
				val[Mask][i]=count(Mask,i);
			}
	}
}

int main ()
{
	int i,j,ncase,Mask,cnt,curmin=INF,minnum;
	cin>>n;
	for (i=1;i<=n;i++) cin>>a[i];
	ncase=getint();
	for (int ca=1;ca<=ncase;ca++)
	{
		cin>>m;
		for (i=1;i<=m;i++) cin>>b[i];	
		for (i=1;i<=n;i++) pos[i]=-1;
		for (i=m;i>=0;i--)
		{
			for (j=1;j<=n;j++) nxt[i][j]=pos[j];
			for (j=1;j<=n;j++)
				if (b[i]==a[j]) {pos[j]=i;break;}
		}
		for (Mask=0;Mask<=(1<<n)-1;Mask++)
			for (cnt=0;cnt<=n*(n-1)>>1;cnt++)
				dp[Mask][cnt]=m+1;
		dp[0][0]=0;
		init_val();q.push(0);q.push(0);
		while (!q.empty())
		{
			Mask=q.front();q.pop();cnt=q.front();q.pop();
			for (i=1;i<=n;i++)
				if (!(Mask&(1<<(i-1))) && nxt[dp[Mask][cnt]][i]!=-1)
				{
					if (nxt[dp[Mask][cnt]][i]<dp[Mask|(1<<(i-1))][cnt+val[Mask][i]])
					{
						dp[Mask|(1<<(i-1))][cnt+val[Mask][i]]=nxt[dp[Mask][cnt]][i];
						q.push(Mask|(1<<(i-1)));q.push(cnt+val[Mask][i]);
					}
				}
		}
		for (i=0;i<=n*(n-1)/2;i++)
			if (dp[(1<<n)-1][i]<=m)
			{
				if (i<curmin) curmin=i,minnum=ca;
				break;
			}
	}
	if (curmin>=INF)
	{
		printf("Brand new problem!\n");
		return 0;
	}
	printf("%d\n",minnum);
	printf("[:");
	for (i=1;i<=n*(n-1)/2-curmin+1;i++) printf("|");
	printf(":]\n");
	return 0;
}
