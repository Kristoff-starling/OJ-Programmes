#include <bits/stdc++.h>
#define LL long long
#define pii pair<int,int>
#define pll pair<LL,LL>
#define rep(i,j,k) for (int i=j;i<=k;i++)
using namespace std;

const int maxn=2e5;

int tot, n, m, t, r, k, cnt;
int mp[48][48];
double f[48];
int num[maxn];

int read() {
	int tot=0,fh=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') fh=-1;c=getchar();}
	while (c>='0'&&c<='9') {tot=tot*10+c-'0';c=getchar();}
	return tot*fh;
}

void getstr(char *a) {
	char c=getchar();int len=0;
	while (!((c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9'))) c=getchar();
	while ((c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9')) {a[++len]=c;c=getchar();}
}

struct compass {
	int nxt, dat, len;
} p[maxn * 2];

int head[maxn], dis[maxn];
double q[maxn];
priority_queue<pii> S;
// set<pii> S;
int inS[maxn];

void connect(int x, int y, int z) {
	tot++;
	p[tot].nxt = head[x];
	p[tot].dat = y;
	p[tot].len = z;
	head[x] = tot;
}

void Renew(int x, int l) {
	if (dis[x] == -1 || dis[x] > l) {
		dis[x] = l;
        S.push(make_pair(-dis[x], x));
		// S.insert(make_pair(dis[x], x));
	}
}

void Dijkstra(int s) {
	for (int i = 1;i <= n; i++) dis[i] = -1;
	for (int i = 1;i <= n; i++) inS[i] = 0;
	dis[s] = 0;
	inS[s] = 1;
	for (int i = head[s]; i; i = p[i].nxt) 
		Renew(p[i].dat, dis[s] + p[i].len);
	while (!S.empty()) {
		// set<pii>::iterator it = S.begin();
		// int x = (*it).second;
		// S.erase(it);
        int x = S.top().second; S.pop();
		if (inS[x] == 0) {
			inS[x] = 1;
			for (int i = head[x]; i; i = p[i].nxt)
				Renew(p[i].dat, dis[x] + p[i].len);
		}
	}
}

double dp[1100048][23];

double solve()
{
	/*
    if (cur == cnt) return 0;
    if (dp[cur][Mask] >= 0) return dp[cur][Mask];
    dp[cur][Mask] = f[cur] * mp[cur][cnt] / r;
    double minn = 1e18;
	for (int i = 1; i <= cnt; i++)
        if ((Mask & (1<<(i-1))) == 0 && mp[cur][i] != -1)
            minn = min(minn, solve(i, Mask | (1<<(i-1))) + (double)(mp[cur][i]) / t);
    dp[cur][Mask] += (1.0 - f[cur]) * minn;
    return dp[cur][Mask];
	*/
	for (int Mask = (1<<cnt)-1; Mask >= 0; Mask--)
		for (int cur = 1; cur <= cnt; cur++)
		{
			if ((Mask & (1<<(cur-1))) == 0) continue;
			if (cur == cnt) {dp[Mask][cur] = 0; continue;}
			dp[Mask][cur] = f[cur] * mp[cur][cnt] / r;
			double minn = 1e18;
			for (int i = 1; i <= cnt; i++)
				if ((Mask & (1<<(i-1))) == 0 && mp[cur][i] != -1)
					minn = min(minn, dp[Mask|(1<<(i-1))][i] + (double)(mp[cur][i]) / t);
			dp[Mask][cur] += (1.0 - f[cur]) * minn;
		}
	return dp[1][1];
}

int main() {
	t = read(), r = read();
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read(), z = read();
		connect(x, y, z);
		connect(y, x, z);
	}
	k = read();
	for (int i = 1; i <= k; i++) {
		int x = read(), y = read();
		q[x] = q[x] + (1.0 - q[x]) * (100 - y) / 100;
	}
	num[cnt = 1] = 1;
	for (int i = 2; i < n; i++)
		if (q[i]) num[++cnt] = i;
	num[++cnt] = n;

	for (int i = 1; i <= cnt; i++) {
		f[i] = q[num[i]];
		Dijkstra(num[i]);
		for (int j = 1; j <= cnt; j++)
			mp[i][j] = dis[num[j]];
	}

    assert(cnt <= 20);
	if (mp[1][cnt] == -1) puts("-1");
	else printf("%.6lf\n", solve());
	return 0;
}