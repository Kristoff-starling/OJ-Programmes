#include <bits/stdc++.h>
using namespace std;
 
vector<string> wordList;
 
map<string, int> id_pool;
int N;
vector<int> v[200000];
void addWord(string word)
{
    if (id_pool.find(word) == id_pool.end())
    {
        N++;
        id_pool[word] = N;
    }
}
 
queue<int> q;
int dist[200000];
int bfs(int st, int ed)
{
    for (int i = 1; i <= N; i++) dist[i] = -1;
    dist[st] = 0; q.push(st);
    while (!q.empty())
    {
        int cur = q.front(); q.pop();
        for (auto to : v[cur])
            if (dist[to] == -1)
            {
                dist[to] = dist[cur] + 1;
                q.push(to);
            }
    }
    if (dist[ed] == -1)
        return 0;
    else
        return (dist[ed] >> 1) + 1;
}
 
int ladderLength(string beginWord, string endWord) {
    N = int(wordList.size());
    for (int i = 0; i < N; i++) id_pool[wordList[i]] = i + 1;
    if (id_pool.find(endWord) == id_pool.end())
        return 0;
    addWord(beginWord);
    wordList.push_back(beginWord);
    for (string word : wordList)
    {
        string iword;
        int id1 = id_pool[word], id2;
        for (int i = 0; i < int(word.size()); i++)
        {
            iword = word;
            iword.replace(i, 1, "*");
            addWord(iword);
            id2 = id_pool[iword];
            v[id1].push_back(id2); v[id2].push_back(id1);
        }
    }
    return bfs(id_pool[beginWord], id_pool[endWord]);
}
 
int main ()
{
    ios::sync_with_stdio(false);
    int n; string st, ed, s;
    cin >> n >> st >> ed;
    wordList.clear();
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        wordList.push_back(s);
    }
    cout << ladderLength(st, ed) << endl;
    return 0;
}