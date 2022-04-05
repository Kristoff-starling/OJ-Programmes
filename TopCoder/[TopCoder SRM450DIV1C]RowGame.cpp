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
const double pi=acos(-1);

LL sum[148];int n;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

class RowGame
{
	int n,N,a[148];LL sum[148];
	int left[148];LL maxsum[148],maxn;
	LL dp1[148],dp2[148];
	inline void check_max(int cur,int last,LL t)
	{
		if (dp1[cur]==-1 || dp1[cur]>dp1[last]+t+1) 
		{
			dp1[cur]=dp1[last]+t+1;
			dp2[cur]=dp2[last]+t*maxsum[last]+sum[cur]-sum[left[last]-1];
		}
		else if (dp1[cur]==dp1[last]+t+1)
		{
			dp2[cur]=max(dp2[cur],dp2[last]+t*maxsum[last]+sum[cur]-sum[left[last]-1]);
		}
	}
	public:
		inline LL score(vector<int> board,int k)
		{
			n=int(board.size());int i,j;
			memset(sum,0,sizeof(sum));
			for (i=1;i<=n;i++) a[i]=board[i-1],sum[i]=sum[i-1]+a[i];
			memset(left,-1,sizeof(left));memset(maxsum,-1,sizeof(maxsum));
			for (i=1;i<=n;i++)
				for (j=1;j<=i;j++)
					if (sum[i]-sum[j-1]>maxsum[i]) maxsum[i]=sum[i]-sum[j-1],left[i]=j;
			maxn=-1;
			for (i=1;i<=n;i++) if (maxsum[i]>maxn) maxn=maxsum[i],N=i;
			if (maxn==-1) return 0;
			memset(dp1,-1,sizeof(dp1));
			for (i=1;i<=N;i++)
			{
				if (left[i]==-1) continue;
				if (sum[i]>=0) {dp1[i]=1;dp2[i]=sum[i];continue;}
				for (j=1;j<=i-1;j++)
					if (dp1[j]!=-1 && left[j]!=-1)
					{
						LL cursum=dp2[j],add=sum[i]-sum[left[j]-1],delta=cursum+add;
						LL tt=0;
						if (delta<0) {if (!maxsum[j]) continue;tt=((-delta)%maxsum[j]==0?(-delta)/maxsum[j]:(-delta)/maxsum[j]+1);}
						if (tt%2==0) tt++;
						check_max(i,j,tt);
					}			
			}
			LL res=0;
			for (i=1;i<=N;i++)
				if (dp1[i]!=-1 && dp1[i]<k)
				{
					int lft=k-dp1[i];
					res=max(res,dp2[i]+maxsum[i]*lft);
				}
			return res;
		}
};
/*---Debug Part---*/
/*
int main ()
{
	RowGame A;int nn;
	while (scanf("%d",&nn)!=EOF)
	{
		int x;vector<int> vv;
		while (nn--)
		{
			x=getint();
			vv.pb(x);
		}
		x=getint();
		cout<<A.score(vv,x)<<endl;
	}
	return 0;
}*/
