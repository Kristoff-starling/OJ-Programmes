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
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const int magic=348;
const LL LINF=2e16;
const double eps=1e-10;

inline int gcd(int x,int y)
{
	return y==0?x:gcd(y,x%y);
}

inline int getint()
{
	char ch;
	while (((ch=getchar())<'0' || ch>'9') && ch!='-') {}
	int res,mark;
	if (ch>='0' && ch<='9')
	{
		mark=1;
		res=ch-'0';
	}
	else
	{
		mark=-1;
		res=0;
	}
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res*mark;
}

inline LL getLL()
{
	char ch;
	while (((ch=getchar())<'0' || ch>'9') && ch!='-') {}
	LL res,mark;
	if (ch>='0' && ch<='9')
	{
		mark=1;
		res=ch-'0';
	}
	else
	{
		mark=-1;
		res=0;
	}
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res*mark;
}

int n;
LL a[50];
map<LL,int> m[50];
LL full[50];
bool used[50];
int tt;
//map<LL,bool>::iterator iter;
bool superf=false;
int path[50];

bool check(int step,LL cmp)
{
	//map<LL,int>::iterator iter;
	
	if (cmp==0) return false;
	if (step==1) return true;
	if (step!=n)
	{//for (iter=m[step-1].begin();iter!=m[step-1].end();iter++) //cout<<iter->first<<' '<<"!!!";
	//cout<<step<<" "<<cmp<<' '<<"shit"<<endl;
		if ((m[step-1][-cmp]==10) || (full[step-1]==-cmp))
		{
			//for (iter=m[step-1].begin();iter!=m[step-1].end();iter++) //cout<<iter->first<<' '<<iter->second<<"!!!";
	//cout<<"end1"<<endl;
			return false;
			}else
			{
			//	for (iter=m[step-1].begin();iter!=m[step-1].end();iter++) //cout<<iter->first<<' '<<iter->second<<"!!!";
	//cout<<"end2"<<endl;
				return true;
			}
	}
	else
	{
		if (m[step-1][-cmp]==10) return false; else return true;
	}
}

void dfs(int step)
{
	map<LL,int>::iterator iter;
	//cout<<step<<endl;
//	for (int i=1;i<=step-1;i++) //cout<<path[i]<<' ';
	//cout<<endl;
	//for (int i=1;i<=n;i++) if (used[i]) //cout<<a[i]<<' ';
	//cout<<endl;
//	for (iter=m[step-1].begin();iter!=m[step-1].end();iter++) //cout<<iter->first<<' '<<")";
	//cout<<full[step-1]<<"@"<<endl;
	//cout<<endl;
	if (step==n+1)
	{
		superf=true;
		for (int i=1;i<=n;i++) printf("%d ",path[i]);
		return;
	}
	int i;
	for (i=1;i<=n;i++)
		if (!used[i] && check(step,a[i]-a[step]))
		{
			//for (iter=m[step-1].begin();iter!=m[step-1].end();iter++) //cout<<iter->first<<' '<<")";
			tt++;
			if (tt>=200000000) exit(0);
			used[i]=true;
			path[step]=a[i];
			if (step==1)
			{
				full[1]=a[i]-a[step];
				m[1].erase(m[1].begin(),m[1].end());
				//cout<<"&"<<endl;
				//for (iter=m[1].begin();iter!=m[1].end();iter++) //cout<<iter->first<<"$"<<endl;
				//m[1][a[i]-a[step]]=true;
			}
			else
			{
				//m[step].clear();
				if (step==2 && path[1]==5)
				{
					//cout<<step<<"("<<endl;
					//for (iter=m[step-1].begin();iter!=m[step-1].end();iter++) //cout<<iter->first<<"^"<<endl;
				}
				////cout<<a[i]-a[step]<<"*"<<' '<<path[1]<<endl;
				m[step][a[i]-a[step]]=10;
				for (iter=m[step-1].begin();iter!=m[step-1].end();iter++)
				{
					if (iter->second==0) break;
					//cout<<"#"<<endl;
					m[step][iter->first]=10;
					m[step][iter->first+a[i]-a[step]]=10;
				}
				m[step][full[step-1]]=10;
				full[step]=full[step-1]+a[i]-a[step];
			}
			dfs(step+1);
			if (superf) return;
			used[i]=false;
			m[step].erase(m[step].begin(),m[step].end());
		}
}

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;i++) a[i]=getLL();
	dfs(1);
	if (!superf) printf("-1\n");
	return 0;
}
