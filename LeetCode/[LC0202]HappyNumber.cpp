class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    vector<int> v[1001];bool h[1001];
    int f(int x)
    {
        int res=0;
        while (x) res+=(x%10)*(x%10),x/=10;
        return res;
    }
    void dfs(int cur)
    {
        h[cur]=true;
        for (auto y : v[cur]) if (!h[y]) dfs(y);
    }
public:
    bool isHappy(int n) {
        rep(i,2,1000) v[f(i)].push_back(i);
        dfs(1);
        return h[f(n)];
    }
};