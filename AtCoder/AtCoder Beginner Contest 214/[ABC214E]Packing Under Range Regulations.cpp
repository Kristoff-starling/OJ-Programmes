#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=2e5;

int n;

struct node
{
    int l,r;
    void input() {scanf("%d%d",&l,&r);}
    bool operator < (const node &other) const {return l<other.l;}
}a[MAXN+48];

priority_queue<int> q;

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) a[i].input();
        sort(a+1,a+n+1);while (!q.empty()) q.pop();bool f=true;
        a[n+1].l=1e9+1;int cur;
        rep(i,1,n)
        {
            q.push(-a[i].r);cur=a[i].l;
            while (cur<a[i+1].l && !q.empty())
            {
                int sm=-q.top();q.pop();
                if (cur>sm) {f=false;break;}
                cur++;
            }
            if (!f) break;
        }
        if (cur>1e9 && !q.empty()) f=false;
        if (!f) puts("No"); else puts("Yes");
    }
    return 0;
}