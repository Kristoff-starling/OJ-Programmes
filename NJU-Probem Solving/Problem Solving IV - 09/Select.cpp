#include <bits/stdc++.h>
#define Pair pair<int,int>
#define x first
#define y second
#define mp make_pair
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=1e5;

int n,m;
int a[MAXN+48],ans[MAXN+48];

struct node
{
    int op,pos,id;
    bool operator < (const node &other) const {return pos>other.pos;}
}q[MAXN+48];

set<Pair> s;

int main ()
{
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%d",a+i);
    rep(i,1,m) scanf("%d%d",&q[i].op,&q[i].pos),q[i].id=i;
    sort(q+1,q+m+1);int ptr=n;
    rep(i,1,m)
    {
        while (ptr>q[i].pos)
        {
            set<Pair>::iterator iter=s.lower_bound(mp(a[ptr],ptr));
            if (iter!=s.end() && iter->x==a[ptr]) s.erase(iter);
            s.insert(mp(a[ptr],ptr));ptr--;
        }
        set<Pair>::iterator iter=s.lower_bound(mp(a[q[i].pos],q[i].pos));
        if (q[i].op==0)
        {
            if (iter!=s.end()) ans[q[i].id]=iter->y;
            else ans[q[i].id]=-1;
        }
        else
        {
            if (iter!=s.end() && iter->x==a[q[i].pos]) ans[q[i].id]=iter->y;
            else if (iter==s.begin()) ans[q[i].id]=-1;
            else
            {
                --iter;
                ans[q[i].id]=iter->y;
            }
        }
    }
    rep(i,1,m) printf("%d\n",ans[i]);
    return 0;
}