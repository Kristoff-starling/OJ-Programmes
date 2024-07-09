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

inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

bool judge(int x,int y)
{
	if (x<=y && 2*x>=y) return true; else return false;
}

int main ()
{
	int v1,v2,v3,vm;
	v1=getint();v2=getint();v3=getint();vm=getint();
	int i,j,k;
	for (k=1;k<=200;k++)
		for (j=k+1;j<=200;j++)
			for (i=j+1;i<=200;i++)
			{
				if (judge(v1,i) && judge(v2,j) && judge(v3,k) && !judge(vm,i) && !judge(vm,j) && judge(vm,k))
				{
					cout<<i<<' '<<j<<' '<<k<<endl;
					return 0;
				}
			}
	cout<<-1<<endl;
	return 0;
}
