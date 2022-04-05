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

char s[48][48];
int n=9;

int main ()
{
	int i,j,x,y;
	for (i=1;i<=9;i++)
		for (j=1;j<=3;j++)
			scanf("%s",s[i]+(j-1)*3+1);
	x=getint();y=getint();
	int num1=(x-1)/3+1,num2=(y-1)/3+1;
	x=x-(num1-1)*3;y=y-(num2-1)*3;
	bool f=false;
	for (i=(x-1)*3+1;i<=x*3;i++)
		for (j=(y-1)*3+1;j<=y*3;j++)
			if (s[i][j]=='.')
			{
				f=true;
				break;
			}
	if (!f)
	{
		for (i=1;i<=9;i++)
		{
			for (j=1;j<=9;j++)
			{
				if (s[i][j]!='.') cout<<s[i][j]; else cout<<"!";
				if (j%3==0) cout<<' ';
			}
			cout<<endl;
			if (i%3==0) cout<<endl;
		}
	}
	else
	{
		for (i=(x-1)*3+1;i<=x*3;i++)
			for (j=(y-1)*3+1;j<=y*3;j++)
				if (s[i][j]=='.') s[i][j]='!';
		for (i=1;i<=9;i++)
		{
			for (j=1;j<=9;j++)
			{
				cout<<s[i][j];
				if (j%3==0) cout<<' ';
			}
			cout<<endl;
			if (i%3==0) cout<<endl;
		}
	}
	return 0;
}
