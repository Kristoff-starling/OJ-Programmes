int d[1000];
bool cmp(int x,int y) {return d[x]>d[y];}
class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    bool visited[1000];
    vector<int> v[1000];int n;
    vector<int> vv[1000];int depth[1000];
    unordered_set<int> s[1000];
    bool exist[1000];
    int calc(int root)
    {
        int res=1;
        for (auto cur : v[root]) if (!visited[cur])
        {
            for (auto y : v[cur])
            {
                if (visited[y])
                    if (depth[y]>depth[root]) return 0; else continue;
                if (s[root].find(y)==s[root].end()) return 0;
            }
            visited[cur]=true;depth[cur]=depth[root]+1;
            vv[root].push_back(cur);res*=calc(cur);
        }
        return res;
    }
    bool check_same(int x,int y)
    {
        if (d[x]!=d[y]) return false;
        for (auto item : v[x]) if (item!=y && s[y].find(item)==s[y].end()) return false;
        return true;
    }
public:
    int checkWays(vector<vector<int>>& pairs) {
        memset(d,0,sizeof(d));memset(visited,false,sizeof(visited));n=0;
        for (auto item : pairs)
        {
            d[item[0]]++;d[item[1]]++;
            v[item[0]].push_back(item[1]);v[item[1]].push_back(item[0]);
            s[item[0]].insert(item[1]);s[item[1]].insert(item[0]);
            n=max(n,max(item[0],item[1]));exist[item[0]]=exist[item[1]]=true;
        }
        rep(i,1,n) if (exist[i]) v[0].push_back(i),s[0].insert(i);
        rep(i,0,n) sort(v[i].begin(),v[i].end(),cmp);
        depth[0]=0; int res=calc(0); if (res==0) return 0;
        if (int(vv[0].size())>1) return 0; 
        rep(i,1,n) for (auto item : vv[i]) if (check_same(i,item)) return 2;
        return 1;
    }
};