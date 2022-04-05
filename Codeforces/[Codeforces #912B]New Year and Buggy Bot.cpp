#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <cctype>
#define LL long long
#define LB long double
#define mp make_pair
#define pb push_back
#define pf push_front 
#define Pair pair<int,int>
#define x first
#define y second
#define LOWBIT(X) x & (-x)
using namespace std;

const int MOD=1e6;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;bool f;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;bool f;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int move[5][3];
int n,m;
int a[148][148];
char s[148];
int sx,sy,ex,ey;
int mm[10];
string seq;

bool check()
{
	int x=sx,y=sy;
	int i;
	for (i=0;i<=seq.size()-1;i++)
	{
		x+=move[mm[seq[i]-'0']][1];y+=move[mm[seq[i]-'0']][2];
		if (!a[x][y] || !(1<=x && x<=n && 1<=y && y<=m)) return false;
		if (x==ex && y==ey) return true;
	}
	return false;
}

int main ()
{
	move[1][1]=-1;move[1][2]=0;
	move[2][1]=0;move[2][2]=1;
	move[3][1]=1;move[3][2]=0;
	move[4][1]=0;move[4][2]=-1;
	int i,j;
	cin>>n>>m;
	for (i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for (j=1;j<=m;j++)
		{
			if (s[j]=='#') a[i][j]=0; else a[i][j]=1;
			if (s[j]=='S') sx=i,sy=j;
			if (s[j]=='E') ex=i,ey=j;
		}
	}
	cin>>seq;
	int cnt=0;
	for (i=0;i<=3;i++) mm[i]=i+1;
	do
	{
		if (check()) cnt++;
	}
	while (next_permutation(mm,mm+4));
	cout<<cnt<<endl;
	return 0;
}
