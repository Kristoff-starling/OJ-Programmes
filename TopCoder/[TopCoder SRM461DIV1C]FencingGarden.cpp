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

class FencingGarden
{
	LL sum,csum,llim,rlim;
	int a[48],b[48],atot,btot,n;
	set<LL> s;set<LL>::iterator iter;
	LB maxarea,curarea;
	LL maxlen,curlen;
	inline void check_max(LB curarea,LL curlen)
	{
		if (!curarea || !curlen) return;
		if (curarea>maxarea) {maxarea=curarea;maxlen=curlen;return;}
		if (curarea==maxarea) {maxlen=max(maxlen,curlen);}
	}
	inline void Clear()
	{
		atot=btot=0;
		sum=0;maxlen=maxarea=0;s.clear();
	}
	public:
		inline LL computeWidth(vector<int> segment)
		{
			int i,Mask;n=int(segment.size());Clear();
			for (i=0;i<int(segment.size());i++) sum+=segment[i];
			for (i=0;i<=n-1;i++) if (i<=n/2-1) a[++atot]=segment[i]; else b[++btot]=segment[i];
			for (Mask=0;Mask<=(1<<atot)-1;Mask++)
			{
				csum=0;
				for (i=1;i<=atot;i++) if (Mask&(1<<(i-1))) csum+=a[i];
				s.insert(csum);
			}
			if (sum%2==1) llim=sum/2,rlim=sum/2+1; else llim=rlim=sum/2;
			for (Mask=0;Mask<=(1<<btot)-1;Mask++)
			{
				csum=0;
				for (i=1;i<=btot;i++) if (Mask&(1<<(i-1))) csum+=b[i];
				LL nsum=llim-csum;iter=s.lower_bound(nsum);
				if (iter!=s.end() && (*iter)==nsum) {curlen=csum+(*iter);check_max((LB)(-(LB)curlen*curlen+(LB)sum*curlen)*1.0/2,curlen);}
				else if (iter!=s.begin()) {curlen=csum+(*(--iter));check_max((LB)(-(LB)curlen*curlen+(LB)sum*curlen)*1.0/2,curlen);}
				nsum=rlim-csum;iter=s.lower_bound(nsum);
				if (iter!=s.end())
				{
					curlen=csum+(*iter);check_max((LB)(-(LB)curlen*curlen+(LB)sum*curlen)*1.0/2,curlen);
				}
			}
			if (sum%4==0) llim=rlim=sum/4; else llim=sum/4,rlim=sum/4+1;
			for (Mask=0;Mask<=(1<<btot)-1;Mask++)
			{
				csum=0;
				for (i=1;i<=btot;i++) if (Mask&(1<<(i-1))) csum+=b[i];
				LL nsum=llim-csum;iter=s.lower_bound(nsum);
				if (iter!=s.end() && (*iter)==nsum) {curlen=csum+(*iter);check_max((LB)(-2)*curlen*curlen+(LB)sum*curlen,sum-2*curlen);}
				else if (iter!=s.begin()) {curlen=csum+(*(--iter));check_max((LB)(-2)*curlen*curlen+(LB)sum*curlen,sum-2*curlen);}
				nsum=rlim-csum;iter=s.lower_bound(nsum);
				if (iter!=s.end())
				{
					curlen=csum+(*iter);check_max((LB)(-2)*curlen*curlen+(LB)sum*curlen,sum-2*curlen);
				}
			}
			return maxlen;
		}
};

/*---Debug Part---*/
/*int main ()
{
	FencingGarden A;
	int nn;
	while (scanf("%d",&nn)!=EOF)
	{
		vector<int> vv;int x;
		while (nn--) x=getint(),vv.pb(x);
		cout<<A.computeWidth(vv)<<endl;
	}
	return 0;
}*/
