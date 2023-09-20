#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;

char s[4][48];
int n,num[200];
bool used[48];

void print()
{
    for (char ch='A';ch<='A'+n-1;ch++)
        printf("%d ",num[ch]);
    puts("");
}

int check_valid(int row,int col,int last)
{
    if (row!=3) return last;
    if (num[s[1][col]]==-1 || num[s[2][col]]==-1 || num[s[3][col]]==-1) return 0;
    if ((num[s[1][col]]+num[s[2][col]]+last)%n!=num[s[3][col]]) return -1;
    return (num[s[1][col]]+num[s[2][col]]+last)/n;
}

void dfs(int col,int row,int last)
{
    if (col==0 && last==0) {print();exit(0);}
    rep(i,1,col) if (check_valid(3,i,0)==-1 && check_valid(3,i,1)==-1) return;
    if (num[s[row][col]]!=-1)
    {
        int nlast=check_valid(row,col,last);
        if (nlast==-1) return;
        if (row!=3) dfs(col,row+1,nlast); else dfs(col-1,1,nlast);
        return;
    }
    rep(i,0,n-1) if (!used[i])
    {
        num[s[row][col]]=i;used[i]=true;
        int nlast=check_valid(row,col,last);
        if (nlast==-1) {used[i]=false;continue;}
        if (row!=3) dfs(col,row+1,nlast); else dfs(col-1,1,nlast);
        used[i]=false;
    }
    num[s[row][col]]=-1;
}

int main ()
{
    scanf("%d%s%s%s",&n,s[1]+1,s[2]+1,s[3]+1);
    memset(num,0xff,sizeof(num));memset(used,false,sizeof(used));
    dfs(n,1,0); exit(1);
}