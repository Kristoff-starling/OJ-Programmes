#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define pf push_front
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=1e9+7;
const int INF=2e9;
const int magic=348;
const LL LINF=2e16;
const double eps=1e-10;
const int Ni=500000004;
 
inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}
 
struct node
{
	LL x,y,z;
};
 
vector<int> v[200048];
vector<node> q[200048];
int deq_num[200048],tot=0;
int n;
 
bool cmp(int x,int y)
{
	return q[deq_num[x]].size()<q[deq_num[y]].size();
}
 
void dfs(int cur)
{
	node ins;int sz=v[cur].size();
	if (sz==0)
	{
		deq_num[cur]=++tot;
		ins.x=ins.y=Ni;ins.z=0;
		q[tot].pb(ins);
		return;
	}
	int i,j,j1,j2,num1,num2,xx,yy,zz;
	for (i=0;i<sz;i++) dfs(v[cur][i]);
	//sort(v[cur].begin(),v[cur].end(),cmp);
	for (i=1;i<sz;i++) if (!cmp(v[cur][i-1],v[cur][i])) swap(v[cur][i-1],v[cur][i]);
	for (i=0;i<=sz-2;i++)
	{
		num1=deq_num[v[cur][i]];num2=deq_num[v[cur][sz-1]];
		for (j=0;j<q[num1].size();j++)
		{
			j1=q[num1].size()-1-j;j2=q[num2].size()-1-j;
			xx=q[num2][j2].x;yy=q[num2][j2].y;zz=q[num2][j2].z;
			q[num2][j2].x=(xx*q[num1][j1].x)%MOD;
			q[num2][j2].y=((xx*q[num1][j1].y)%MOD+(yy*q[num1][j1].x)%MOD)%MOD;
			q[num2][j2].z=((xx*q[num1][j1].z)%MOD+(yy*q[num1][j1].y)%MOD+(yy*q[num1][j1].z)%MOD+(zz*q[num1][j1].x)%MOD+(zz*q[num1][j1].y)%MOD+(zz*q[num1][j1].z))%MOD;
		}
	}
	deq_num[cur]=deq_num[v[cur][sz-1]];int Num=deq_num[cur];
	for (i=0;i<q[Num].size();i++)
	{
		q[Num][i].x=(q[Num][i].x+q[Num][i].z)%MOD;
		q[Num][i].z=0;
	}
	ins.x=ins.y=Ni;ins.z=0;
	q[Num].pb(ins);
}
 
int mypow()
{
	LL res=1;int i;
	for (i=1;i<=n+1;i++) res=(res*2)%MOD;
	return int(res);
}
 
int main ()
{
	int i,x;
	n=getint();
	for (i=1;i<=n;i++)
	{
		x=getint();
		v[x].pb(i);
	}
	dfs(0);
	int Num=deq_num[0];LL ans=0;
	for (i=0;i<q[Num].size();i++) ans=(ans+q[Num][i].y)%MOD;
	ans=(ans*mypow())%MOD;
	cout<<ans<<endl;
	return 0;
}
