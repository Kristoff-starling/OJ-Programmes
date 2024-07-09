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

int n;
string type;
string s;
int alpha[48];
int cc=0,cnt=0;
pair<string,string> a[100048];
char correct[48];
bool cur[48];

bool judge()
{
	int i,ccc=0;
	for (i=1;i<=26;i++) if (alpha[i]==2) ccc++;
	if (ccc==1) return true;
	if (ccc>1) return false;
	for (i=1;i<=26;i++) if (alpha[i]==1) ccc++;
	if (ccc==25) return true;
	return false;
}

int main ()
{
	//ios::sync_with_stdio(false);
	n=getint();
	int i,j;bool fff=false;
	for (i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	for (i=1;i<=n;i++)
	{
		if (a[i].x=="!") cnt++;
		if (a[i].x=="?" && i!=n) cnt++;
		if (a[i].x=="!")
		{
			memset(cur,false,sizeof(cur));
			for (j=0;j<a[i].y.size();j++) cur[a[i].y[j]-'a'+1]=true;
			for (j=1;j<=26;j++) if (cur[j] && alpha[j]!=1) alpha[j]=2; else alpha[j]=1;
		}
		if (a[i].x==".")
			for (j=0;j<a[i].y.size();j++) alpha[a[i].y[j]-'a'+1]=1;
		if (a[i].x=="?")
			alpha[a[i].y[0]-'a'+1]=1;
		//for (j=1;j<=26;j++) cout<<alpha[j]<<' ';
		//cout<<endl;
		if (judge() && !fff) cc=cnt,fff=true;
	}
	//cout<<cnt<<' '<<cc<<endl;
	if (!fff) cout<<0<<endl; else cout<<cnt-cc<<endl;
	return 0;
}
