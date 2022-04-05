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
const LB eps=1e-10;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
int a[100048];
int cnt1,cnt2,cnt4;

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n;i++)
	{
		if (a[i]%4==0) {cnt4++;continue;}
		if (a[i]%2==0) {cnt2++;continue;}
		cnt1++;
	}
	if (cnt2==0)
	{
		if (cnt4>=cnt1-1) cout<<"Yes"<<endl; else cout<<"No"<<endl;
		return 0;
	}
	if (cnt4>=cnt1) cout<<"Yes"<<endl; else cout<<"No"<<endl;
	return 0;
}
