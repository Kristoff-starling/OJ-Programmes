#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline char Getchar()
{
	bool f;char ch;
	while (!(isalpha(ch=getchar()) || isdigit(ch))) {}
	return ch;
}

bool exist[148];

int n,m;
int table[148],ntable[48],stable[48];

struct node
{
	char num,suit;
	node () {}
	inline node (char nu,char su) {num=nu;suit=su;}
	inline void input() {num=Getchar();suit=Getchar();}
	inline void print() {cout<<num<<suit;}
}a[20][20];

inline int getind(node cur) {return (table[cur.suit]-1)*13+table[cur.num];}
inline node getcard(int ind) {int su=(ind-1)/13+1,nu=ind-(su-1)*13;return node(ntable[nu],stable[su]);}

inline void init_table()
{
	table['A']=1;
	for (register int i=2;i<=9;i++) table['0'+i]=i;
	table['T']=10;table['J']=11;table['Q']=12;table['K']=13;
	table['C']=1;table['D']=2;table['H']=3;table['S']=4;
	ntable[1]='A';
	for (register int i=2;i<=9;i++) ntable[i]='0'+i;
	ntable[10]='T';ntable[11]='J';ntable[12]='Q';ntable[13]='K';
	stable[1]='C';stable[2]='D';stable[3]='H';stable[4]='S';
}

Pair jpos[5];int cnt;
int type[5];

Pair b[148];int tot;

inline bool check(int sx,int sy)
{
	int i,j;bool f=true;
	for (i=sx;i<=sx+2;i++)
	{
		for (j=sy;j<=sy+2;j++)
			if (a[i][j].suit!=a[sx][sy].suit) {f=false;break;}
		if (!f) break;
	}
	if (f) return true;
	int vs[14];memset(vs,0,sizeof(vs));
	for (i=sx;i<=sx+2;i++)
		for (j=sy;j<=sy+2;j++)
			vs[table[a[i][j].num]]++;
	for (i=1;i<=13;i++) if (vs[i]>1) return false;
	return true;
}

inline bool overlapping(Pair pt1,Pair pt2)
{
	if (pt1.x-2<=pt2.x && pt2.x<=pt1.x+2 && pt1.y-2<=pt2.y && pt2.y<=pt1.y+2) return true;
	return false;
}

int main ()
{
	init_table();
	int i,j;n=getint();m=getint();cnt=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
		{
			a[i][j].input();
			if (isdigit(a[i][j].suit)) jpos[++cnt]=mp(i,j),type[cnt]=a[i][j].suit-'0'; else exist[getind(a[i][j])]=true;
		}
	if (cnt==2 && a[jpos[1].x][jpos[1].y].suit=='2') swap(jpos[1],jpos[2]);
	if (!cnt)
	{
		for (i=1;i<=n-2;i++)
			for (j=1;j<=m-2;j++)
				if (check(i,j)) b[++tot]=mp(i,j);
		int ans1=0,ans2=0;
		for (i=1;i<=tot-1;i++)
		{
			for (j=i+1;j<=tot;j++)
				if (!overlapping(b[i],b[j])) {ans1=i;ans2=j;break;}
			if (ans1) break;
		}
		if (!ans1)
			puts("No solution.");
		else
		{
			puts("Solution exists.");
			puts("There are no jokers.");
			printf("Put the first square to (%d, %d).\n",b[ans1].x,b[ans1].y);
			printf("Put the second square to (%d, %d).\n",b[ans2].x,b[ans2].y);
		}
		return 0;
	}
	if (cnt==1)
	{
//		cout<<jpos[1].x<<' '<<jpos[1].y<<endl;
		for (register int r=1;r<=52;r++)
			if (!exist[r])
			{
				a[jpos[1].x][jpos[1].y]=getcard(r);
//				if (r==28) cout<<a[jpos[1].x][jpos[1].y].num<<a[jpos[1].x][jpos[1].y].suit<<endl;
				tot=0;
				for (i=1;i<=n-2;i++)
					for (j=1;j<=m-2;j++)
//					{
						if (check(i,j)) b[++tot]=mp(i,j);
//						if (r==28 && i==1 && j==1) cout<<"1"<<endl;
//						if (r==28 && j==2 && j==4) cout<<"2"<<endl;
//					}
				int ans1=0,ans2=0;
				for (i=1;i<=tot-1;i++)
				{
					for (j=i+1;j<=tot;j++)
						if (!overlapping(b[i],b[j])) {ans1=i;ans2=j;break;}
					if (ans1) break;
				}
				if (!ans1) continue;
				else
				{
					puts("Solution exists.");
					printf("Replace J%d with ",type[1]);getcard(r).print();puts(".");
					printf("Put the first square to (%d, %d).\n",b[ans1].x,b[ans1].y);
					printf("Put the second square to (%d, %d).\n",b[ans2].x,b[ans2].y);
					return 0;
				}
			}
		puts("No solution.");
		return 0;
	}
	for (register int r1=1;r1<=52;r1++)
		if (!exist[r1])
			for (register int r2=1;r2<=52;r2++)
				if (r1!=r2 && !exist[r2])
				{
					a[jpos[1].x][jpos[1].y]=getcard(r1);
					a[jpos[2].x][jpos[2].y]=getcard(r2);
					tot=0;
					for (i=1;i<=n-2;i++)
						for (j=1;j<=m-2;j++)
							if (check(i,j)) b[++tot]=mp(i,j);
					int ans1=0,ans2=0;
					for (i=1;i<=tot-1;i++)
					{
						for (j=i+1;j<=tot;j++)
							if (!overlapping(b[i],b[j])) {ans1=i;ans2=j;break;}
						if (ans1) break;
					}
					if (!ans1) continue;
					else
					{
						puts("Solution exists.");
						printf("Replace J1 with ");getcard(r1).print();
						printf(" and J2 with ");getcard(r2).print();puts(".");
						printf("Put the first square to (%d, %d).\n",b[ans1].x,b[ans1].y);
						printf("Put the second square to (%d, %d).\n",b[ans2].x,b[ans2].y);
						return 0;
					}
				}
	puts("No solution.");
	return 0;
}
/*
4 6
J2 3S 4S 7S 8S AS
5H 6H 7H J1 TC AC
8H 9H TH 7C 8C 9C
2D 2C 3C 4C 5C 6C
*/
