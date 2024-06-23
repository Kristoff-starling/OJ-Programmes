#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

char ss[400048],s[400048];
int RL[400048];

int Manacher(int len)
{
    int maxright=0,pos=0,ans=0;
    rep(i,1,len)
    {
        if (i<maxright)
		RL[i]=min(RL[2*pos-i],maxright-i);
        else
            RL[i]=1;
        while (i-RL[i]>=1 && i+RL[i]<=len && s[i-RL[i]]==s[i+RL[i]]) RL[i]++;
        ans=max(ans,RL[i]-1);
        if (i+RL[i]>maxright)
        {
            maxright=i+RL[i];
            pos=i;
        }
    }
    return ans;
}

int main ()
{
    scanf("%s",ss+1);int len=strlen(ss+1);int n=0;
    rep(i,1,len) s[++n]='#',s[++n]=ss[i];s[++n]='#';
    printf("%d\n",Manacher(n));return 0;
}