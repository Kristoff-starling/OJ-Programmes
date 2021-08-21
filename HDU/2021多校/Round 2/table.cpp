#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
using namespace std;
int read() {
	int tot=0,fh=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') fh=-1;c=getchar();}
	while (c>='0'&&c<='9') {tot=tot*10+c-'0';c=getchar();}
	return tot*fh;
}
int b[100];
bool prime(int x) {
	for (int i=2;i<=sqrt(x)+1;i++)
		if (x%i==0) return false;
	return true;
} 
int main() {
	for (int n=3;n<=100;n++) if (prime(n)) {
		cout<<n<<":"<<endl;
		for (int a=1;a<n;a++) {
			for (int i=1;i<n;i++) b[i]=a*i%n;
			int ans=0;
			for (int i=1;i<n;i++)
				for (int j=i+1;j<n;j++)
					if (b[i]>b[j]) ans++;
			cout<<ans%2;
		}
		cout<<endl;
	}
	return 0;
}