#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define mp make_pair
#define Pair pair<int,int>
#define x first
#define y second
using namespace std;

const int MAXN=2000;

int n,m,a[MAXN+48][MAXN+48],b[MAXN+48][MAXN+48];

int head,tail;Pair q[MAXN+48];

void check_max(int &x,int y) {x=max(x,y);}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
        rep(j,1,m) b[n][j]=1;
        REP(i,n-1,1) rep(j,1,m) if (a[i][j]<=a[i+1][j]) b[i][j]=b[i+1][j]+1; else b[i][j]=1;
        int ans=0;
        rep(i,1,n)
        {
            check_max(ans,b[i][1]);
            head=tail=1;q[1]=mp(1,b[i][1]);
            rep(j,2,m)
            {
                REP(k,tail,head) if (q[k].y>b[i][j]) q[k].y=b[i][j];
                while (head<tail && q[tail].y==q[tail-1].y) tail--;
                while (head<tail && q[head].y*(j-q[head].x+1)<q[head+1].y*(j-q[head+1].x+1)) head++;
                if (head>tail) check_max(ans,b[i][j]); else check_max(ans,q[head].y*(j-q[head].x+1));
                q[++tail]=mp(j,b[i][j]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}