#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int stot;
vector<string> sentences[1000048];

int ind;
map<pair<string,int>,int> id;

bool visited[2000048];
vector<int> v[2000048];

string getword(string cur)
{
    int st=0,ed=int(cur.size())-1;
    if (!islower(cur[st])) st++;
    if (!islower(cur[ed])) ed--;
    return cur.substr(st,ed-st+1);
}

void createnode(string word)
{
    if (id.find(make_pair(word,0))==id.end())
    {
        id[make_pair(word,0)]=++ind;
        id[make_pair(word,1)]=++ind;
    }
}

void addedge(string w1,string w2)
{
    v[id[make_pair(w1,1)]].push_back(id[make_pair(w2,0)]);
    v[id[make_pair(w2,0)]].push_back(id[make_pair(w1,1)]);
}

void dfs(int cur)
{
    visited[cur]=true;
    for (auto to : v[cur]) if (!visited[to]) dfs(to);
}

int main ()
{
    ios::sync_with_stdio(false);
    string last="",cur="",word;stot=0;
    while (cin>>cur)
    {
        word=getword(cur);createnode(word);
        if (last!="") addedge(getword(last),word);
        if (last=="") stot++;
        sentences[stot].push_back(cur);
        last=cur;if (last.back()=='.') last="";
    }
    rep(i,1,stot) for (auto word : sentences[i])
        if (word.back()==',') dfs(id[make_pair(getword(word),1)]);
    rep(i,1,stot) rep(j,0,int(sentences[i].size())-1)
    {
        if (!(i==1 && j==0)) cout<<" ";
        cout<<sentences[i][j];
        if (islower(sentences[i][j].back()) && visited[id[make_pair(getword(sentences[i][j]),1)]])
            cout<<",";
    }
    return 0;
}