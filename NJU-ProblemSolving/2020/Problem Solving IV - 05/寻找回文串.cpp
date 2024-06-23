#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

unordered_map<int,int> pos;

int main ()
{
    int ca,n,x;scanf("%d",&ca);
    while (ca--)
    {
        pos.clear();scanf("%d",&n);bool flag=false;
        rep(i,1,n)
        {
            scanf("%d",&x);
            if (pos.find(x)!=pos.end()) flag|=(pos[x]!=i-1); else pos[x]=i;
        }
        puts(flag?"YES":"NO");
    }
    return 0;
}