#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n;
int d[148];
vector<int> v[148];
int a[148],b[148];
queue<int> q;

int main ()
{
    int ca,s;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);s=0;
        rep(i,1,n) v[i].clear(),d[i]=0;
        rep(i,1,n) scanf("%d%d",a+i,b+i),s+=b[i];
        rep(i,1,n) rep(j,1,n)
            if (i!=j)
            {
                int tmpa=a[i],tmpb=a[j];
                tmpa+=s-b[i];
                if (n==2) tmpb+=b[i];
                if (tmpa>tmpb) v[i].push_back(j),d[j]++;
            }
        rep(i,1,n) if (!d[i]) q.push(i);
        int cnt=0;
        while (!q.empty())
        {
            int x=q.front();q.pop();cnt++;
            for (auto y : v[x])
            {
                d[y]--;
                if (!d[y]) q.push(y);
            }
        }
        puts((cnt==n)?"Yes":"No");
    }
    return 0;
}