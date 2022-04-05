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

class IslandFerries
{
	public:
		int price[48][48];Pair route[48][48];int num[48];
		int dp[48][1048];queue<int> q;bool inq[48][1048];
		int n,m;
		inline int STRING_TO_INT(string s)
		{
			int res=0,len=int(s.size()),i;
			for (i=0;i<=len-1;i++) res=res*10+s[i]-'0';
			return res;
		}
		inline void doit_price(int ind,string s)
		{
			s+=" ";
			int i,pos,pos1,len=int(s.size());
			for (i=1,pos=0;i<=m && pos<=len-1;i++,pos=pos1+1)
			{
				pos1=s.find(' ',pos);
				price[ind][i]=STRING_TO_INT(s.substr(pos,pos1-pos));
			}
		}
		inline void doit_leg(int ind,string s)
		{
			s+=" ";string ss;
			int i,pos,pos1,len=int(s.size()),pp1,pp2;
			num[ind]=0;
			for (i=1,pos=0;pos<=len-1;pos=pos1+1)
			{
				pos1=s.find(" ",pos);
				ss=s.substr(pos,pos1-pos);
				pp1=ss.find('-');
				route[ind][++num[ind]].x=STRING_TO_INT(ss.substr(0,pp1))+1;
				route[ind][num[ind]].y=STRING_TO_INT(ss.substr(pp1+1,int(ss.size())-pp1))+1;
			}
		}
		inline vector<int> costs(vector<string> legs,vector<string> prices)
		{
			int i,j,k,cur,Mask,to,toMask,cnt;
			m=int(legs.size());n=int(prices.size());
			for (i=1;i<=n;i++) doit_price(i,prices[i-1]);
			for (i=1;i<=m;i++) doit_leg(i,legs[i-1]);
			for (i=1;i<=n;i++)
				for (Mask=0;Mask<=(1<<m)-1;Mask++)
					dp[i][Mask]=INF;
			dp[1][0]=0;q.push(1);q.push(0);
			memset(inq,false,sizeof(inq));inq[1][0]=true;
			while (!q.empty())
			{
				cur=q.front();q.pop();Mask=q.front();q.pop();inq[cur][Mask]=false;
				cnt=__builtin_popcount(Mask);
				for (i=1;i<=m;i++)
					if (Mask&(1<<(i-1)))
					{
						for (j=1;j<=num[i];j++)
							if (route[i][j].x==cur)
							{
								to=route[i][j].y;toMask=(Mask^(1<<(i-1)));
								if (dp[to][toMask]>dp[cur][Mask])
								{
									dp[to][toMask]=dp[cur][Mask];
									if (!inq[to][toMask]) inq[to][toMask]=true,q.push(to),q.push(toMask);
								}
							}
					}
					else
					{
						if (cnt>=3) continue;
						to=cur;toMask=(Mask|(1<<(i-1)));
						if (dp[to][toMask]>dp[cur][Mask]+price[cur][i])
						{
							dp[to][toMask]=dp[cur][Mask]+price[cur][i];
							if (!inq[to][toMask]) inq[to][toMask]=true,q.push(to),q.push(toMask);
						}
					}
			}
			vector<int> res;
			for (i=2;i<=n;i++) if (dp[i][0]>=INF) res.pb(-1); else res.pb(dp[i][0]);
			return res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn,mm;
	IslandFerries A;
	while (scanf("%d%d",&nn,&mm)!=EOF)
	{
		vector<string> aa,bb;
		int i;string s;getchar();
		for (i=1;i<=mm;i++) getline(cin,s),aa.pb(s);
		for (i=1;i<=nn;i++) getline(cin,s),bb.pb(s);
		vector<int> ans=A.costs(aa,bb);
		for (i=0;i<int(ans.size());i++) cout<<ans[i]<<endl;
	}
	return 0;
}
*/
