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
#define pii pair<double,double>
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

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int val[300];

struct Card
{
	char type;char num;
	inline bool operator == (const Card &other) const {return num==other.num;}
	inline bool operator < (const Card &other) const {return val[num]<val[other.num];}
	inline bool operator > (const Card &other) const {return val[num]>val[other.num];}
}my[10],oppo[10],all[10],other[10],seven[10];

struct Hand
{
	Card a[10];
}mybest,oppobest;

inline bool isRoyalStraight(Hand cur)
{
	int i,j;
	for (i=1;i<=4;i++)
		for (j=i+1;j<=5;j++)
			if (cur.a[i]==cur.a[j]) return false;
	for (i=1;i<=5;i++)
		if (!(cur.a[i].num=='T' || cur.a[i].num=='J' || cur.a[i].num=='Q' || cur.a[i].num=='K' || cur.a[i].num=='A')) return false;
	return true;
}

inline bool isminStraight(Hand cur)
{
	int i,j;
	for (i=1;i<=4;i++)
		for (j=i+1;j<=5;j++)
			if (cur.a[i]==cur.a[j]) return false;
	for (i=1;i<=5;i++)
		if (!(cur.a[i].num=='A' || ('2'<=cur.a[i].num && cur.a[i].num<='5'))) return false;
	return true;
}

inline bool isStraight(Hand cur)
{
	if (isminStraight(cur) || isRoyalStraight(cur)) return true;
	for (register int i=1;i<=4;i++) if (val[cur.a[i+1].num]!=val[cur.a[i].num]+1) return false;
	return true;
}

inline bool isFlush(Hand cur)
{
	for (register int i=2;i<=5;i++) if (cur.a[1].type!=cur.a[i].type) return false;
	return true;
}

inline bool isStraightFlush(Hand cur) {return (isStraight(cur) && isFlush(cur));}

inline bool isBomb(Hand cur)
{
	if (cur.a[1]==cur.a[2] && cur.a[1]==cur.a[3] && cur.a[1]==cur.a[4]) return true;
	if (cur.a[2]==cur.a[3] && cur.a[2]==cur.a[4] && cur.a[2]==cur.a[5]) return true;
	return false;
}

inline bool isFullHouse(Hand cur)
{
	if (cur.a[1]==cur.a[2] && cur.a[1]==cur.a[3] && cur.a[4]==cur.a[5]) return true;
	if (cur.a[1]==cur.a[2] && cur.a[3]==cur.a[4] && cur.a[3]==cur.a[5]) return true;
	return false;
}

inline bool isThree(Hand cur)
{
	if (cur.a[1]==cur.a[2] && cur.a[1]==cur.a[3]) return true;
	if (cur.a[2]==cur.a[3] && cur.a[3]==cur.a[4]) return true;
	if (cur.a[3]==cur.a[4] && cur.a[4]==cur.a[5]) return true;
	return false;
}

inline bool isTwoPairs(Hand cur)
{
	if (cur.a[1]==cur.a[2] && cur.a[3]==cur.a[4]) return true;
	if (cur.a[1]==cur.a[2] && cur.a[4]==cur.a[5]) return true;
	if (cur.a[2]==cur.a[3] && cur.a[4]==cur.a[5]) return true;
	return false;
}

inline bool isPair(Hand cur)
{
	int i,j;
	for (i=1;i<=4;i++)
		for (j=i+1;j<=5;j++)
			if (cur.a[i]==cur.a[j]) return true;
	return false;
}

inline int judgetype(Hand cur)
{
	if (isStraightFlush(cur)) return 1;
	if (isBomb(cur)) return 2;
	if (isFullHouse(cur)) return 3;
	if (isFlush(cur)) return 4;
	if (isStraight(cur)) return 5;
	if (isThree(cur)) return 6;
	if (isTwoPairs(cur)) return 7;
	if (isPair(cur)) return 8;
	return 9;
}

inline bool Same(Card cur)
{
	int i;
	for (i=1;i<=2;i++) if (my[i]==cur && my[i].type==cur.type) return true;
	for (i=1;i<=2;i++) if (oppo[i]==cur && oppo[i].type==cur.type) return true;
	for (i=1;i<=3;i++) if (all[i]==cur && all[i].type==cur.type) return true;
	return false;
}

inline int compare_hand(Hand x,Hand y)
{
	int t1=judgetype(x),t2=judgetype(y);
	if (t1!=t2)
		if (t1>t2) return 0; else return 1;
	if (t1==1 || t1==5)
	{
		if (isminStraight(x))
		{
			Card tmp=x.a[5];
			for (register int i=4;i>=1;i--) x.a[i+1]=x.a[i];
			x.a[1]=tmp;
		}
		if (isminStraight(y))
		{
			Card tmp=y.a[5];
			for (register int i=4;i>=1;i--) y.a[i+1]=y.a[i];
			y.a[1]=tmp;
		}
		if (x.a[5]>y.a[5]) return 1;
		if (x.a[5]<y.a[5]) return 0;
		return 2;
	}
	if (t1==2)
	{
		int xv1,xv2,yv1,yv2,V1,V2;
		if (x.a[1]==x.a[2]) xv1=val[x.a[1].num],xv2=val[x.a[5].num]; else xv1=val[x.a[2].num],xv2=val[x.a[1].num];
		if (y.a[1]==y.a[2]) yv1=val[y.a[1].num],yv2=val[y.a[5].num]; else yv1=val[y.a[2].num],yv2=val[y.a[1].num];
		V1=xv1*10000+xv2;V2=yv1*10000+yv2;
		if (V1>V2) return 1;
		if (V1<V2) return 0;
		return 2;
	}
	if (t1==3)
	{
		int xv1,xv2,yv1,yv2,V1,V2;
		if (x.a[1]==x.a[2] && x.a[1]==x.a[3]) xv1=val[x.a[1].num],xv2=val[x.a[4].num]; else xv1=val[x.a[3].num],xv2=val[x.a[1].num];
		if (y.a[1]==y.a[2] && y.a[1]==y.a[3]) yv1=val[y.a[1].num],yv2=val[y.a[4].num]; else yv1=val[y.a[3].num],yv2=val[y.a[1].num];
		V1=xv1*10000+xv2;V2=yv1*10000+yv2;
		if (V1>V2) return 1;
		if (V1<V2) return 0;
		return 2;
	}
	if (t1==4 || t1==9)
	{
		for (register int i=5;i>=1;i--)
		{
			if (x.a[i]>y.a[i]) return 1;
			if (x.a[i]<y.a[i]) return 0;
		}
		return 2;
	}
	if (t1==6)
	{
		int xv1,xv2,xv3,yv1,yv2,yv3,V1,V2;
		if (x.a[1]==x.a[2] && x.a[2]==x.a[3]) xv1=val[x.a[1].num],xv2=val[x.a[5].num],xv3=val[x.a[4].num];
		if (x.a[2]==x.a[3] && x.a[3]==x.a[4]) xv1=val[x.a[2].num],xv2=val[x.a[5].num],xv3=val[x.a[1].num];
		if (x.a[3]==x.a[4] && x.a[4]==x.a[5]) xv1=val[x.a[3].num],xv2=val[x.a[2].num],xv3=val[x.a[1].num];
		if (y.a[1]==y.a[2] && y.a[2]==y.a[3]) yv1=val[y.a[1].num],yv2=val[y.a[5].num],yv3=val[y.a[4].num];
		if (y.a[2]==y.a[3] && y.a[3]==y.a[4]) yv1=val[y.a[2].num],yv2=val[y.a[5].num],yv3=val[y.a[1].num];
		if (y.a[3]==y.a[4] && y.a[4]==y.a[5]) yv1=val[y.a[3].num],yv2=val[y.a[2].num],yv3=val[y.a[1].num];
		V1=xv1*10000+xv2*100+xv3;V2=yv1*10000+yv2*100+yv3;
		if (V1>V2) return 1;if (V1<V2) return 0;
		return 2;
	}
	if (t1==7)
	{
		int xv1,xv2,xv3,yv1,yv2,yv3,V1,V2;
		if (x.a[1]==x.a[2] && x.a[3]==x.a[4]) xv1=val[x.a[3].num],xv2=val[x.a[1].num],xv3=val[x.a[5].num];
		if (x.a[1]==x.a[2] && x.a[4]==x.a[5]) xv1=val[x.a[4].num],xv2=val[x.a[1].num],xv3=val[x.a[3].num];
		if (x.a[2]==x.a[3] && x.a[4]==x.a[5]) xv1=val[x.a[4].num],xv2=val[x.a[2].num],xv3=val[x.a[1].num];
		if (y.a[1]==y.a[2] && y.a[3]==y.a[4]) yv1=val[y.a[3].num],yv2=val[y.a[1].num],yv3=val[y.a[5].num];
		if (y.a[1]==y.a[2] && y.a[4]==y.a[5]) yv1=val[y.a[4].num],yv2=val[y.a[1].num],yv3=val[y.a[3].num];
		if (y.a[2]==y.a[3] && y.a[4]==y.a[5]) yv1=val[y.a[4].num],yv2=val[y.a[2].num],yv3=val[y.a[1].num];
		V1=xv1*10000+xv2*100+xv3;V2=yv1*10000+yv2*100+yv3;
		if (V1>V2) return 1;if (V1<V2) return 0;
		return 2;
	}
	if (t1==8)
	{
		int xv1,xv2,xv3,xv4,yv1,yv2,yv3,yv4,V1,V2;
		if (x.a[1]==x.a[2]) xv1=val[x.a[1].num],xv2=val[x.a[5].num],xv3=val[x.a[4].num],xv4=val[x.a[3].num];
		if (x.a[2]==x.a[3]) xv1=val[x.a[2].num],xv2=val[x.a[5].num],xv3=val[x.a[4].num],xv4=val[x.a[1].num];
		if (x.a[3]==x.a[4]) xv1=val[x.a[3].num],xv2=val[x.a[5].num],xv3=val[x.a[2].num],xv4=val[x.a[1].num];
		if (x.a[4]==x.a[5]) xv1=val[x.a[4].num],xv2=val[x.a[3].num],xv3=val[x.a[2].num],xv4=val[x.a[1].num];
		if (y.a[1]==y.a[2]) yv1=val[y.a[1].num],yv2=val[y.a[5].num],yv3=val[y.a[4].num],yv4=val[y.a[3].num];
		if (y.a[2]==y.a[3]) yv1=val[y.a[2].num],yv2=val[y.a[5].num],yv3=val[y.a[4].num],yv4=val[y.a[1].num];
		if (y.a[3]==y.a[4]) yv1=val[y.a[3].num],yv2=val[y.a[5].num],yv3=val[y.a[2].num],yv4=val[y.a[1].num];
		if (y.a[4]==y.a[5]) yv1=val[y.a[4].num],yv2=val[y.a[3].num],yv3=val[y.a[2].num],yv4=val[y.a[1].num];
		V1=xv1*1000000+xv2*10000+xv3*100+xv4;V2=yv1*1000000+yv2*10000+yv3*100+yv4;
		if (V1>V2) return 1;if (V1<V2) return 0;
		return 2;
	}
}

inline void getmybest()
{
	bool exist=false;int Mask,i,pt;Hand cur;
	for (Mask=0;Mask<=(1<<7)-1;Mask++)
		if (__builtin_popcount(Mask)==5)
		{
			pt=0;
			for (i=1;i<=7;i++)
				if (Mask&(1<<(i-1))) cur.a[++pt]=seven[i];
			sort(cur.a+1,cur.a+6);
			if (!exist)
			{
				exist=true;
				mybest=cur;
			}
			else
			{
				int res=compare_hand(mybest,cur);
				if (!res) mybest=cur;
			}
		}
}

inline void getoppobest()
{
	bool exist=false;int Mask,i,pt;Hand cur;
	for (Mask=0;Mask<=(1<<7)-1;Mask++)
		if (__builtin_popcount(Mask)==5)
		{
			pt=0;
			for (i=1;i<=7;i++)
				if (Mask&(1<<(i-1))) cur.a[++pt]=seven[i];
			sort(cur.a+1,cur.a+6);
			if (!exist)
			{
				exist=true;
				oppobest=cur;
			}
			else
			{
				int res=compare_hand(oppobest,cur);
				if (!res) oppobest=cur;
			}
		}
}

inline Card getCard(int ind)
{
	Card res;
	int type=(ind-1)/13+1,num=ind-(type-1)*13;
	if (type==1) res.type='S';
	if (type==2) res.type='H';
	if (type==3) res.type='D';
	if (type==4) res.type='C';
	if (num==1) res.num='A';
	if (num==10) res.num='T';
	if (num==11) res.num='J';
	if (num==12) res.num='Q';
	if (num==13) res.num='K';
	if (2<=num && num<=9) res.num='0'+num;
	return res;
}

char s[10];

int main ()
{
	int i,j,k;
	for (i=2;i<=9;i++) val['0'+i]=i;
	val['T']=10;val['J']=11;val['Q']=12;val['K']=13;val['A']=14;
	while (scanf("%s",s+1)!=EOF && s[1]!='#')
	{
		my[1].type=s[1];my[1].num=s[2];
		scanf("%s",s+1);my[2].type=s[1];my[2].num=s[2];
		for (i=1;i<=2;i++)
		{
			scanf("%s",s+1);
			oppo[i].type=s[1];oppo[i].num=s[2];
		}
		for (i=1;i<=3;i++)
		{
			scanf("%s",s+1);
			all[i].type=s[1];all[i].num=s[2];
		}
		int cnt=0,wcnt=0;
		for (i=1;i<=51;i++)
			for (j=i+1;j<=52;j++)
			{
				other[1]=getCard(i);other[2]=getCard(j);
				if (Same(other[1]) || Same(other[2])) continue;
				cnt++;
				for (k=1;k<=2;k++) seven[k]=my[k];
				for (k=1;k<=3;k++) seven[2+k]=all[k];
				for (k=1;k<=2;k++) seven[5+k]=other[k];
				getmybest();
				for (k=1;k<=2;k++) seven[k]=oppo[k];
				getoppobest();
				int res=compare_hand(mybest,oppobest);
				if (res==1) wcnt++;
			}
		double ans=wcnt*1.0/cnt;
		printf("%.20lf\n",ans);
	}
	return 0;
}
