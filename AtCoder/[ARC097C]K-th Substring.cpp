#include <bits/stdc++.h>
using namespace std;

set<string> ss;
string a[200048],s;
int tot=0,k;

int main ()
{
	cin>>s>>k;
	int i,j,n=int(s.size());
	for (i=0;i<=n-1;i++)
		for (j=1;j<=5;j++)
		{
			if (i+j-1>=n) continue;
			ss.insert(s.substr(i,j));
		}
	for (i=1;i<=k-1;i++) ss.erase(ss.begin());
	cout<<(*(ss.begin()))<<endl;
	return 0;
}
