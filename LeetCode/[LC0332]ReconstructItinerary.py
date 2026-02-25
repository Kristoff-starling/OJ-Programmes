# Find the lexographically smallest Euler path in the directed graph.
# Hierholzer's algorithm: the path is composed of several cycles and a path. Search until there are no more edges, then append the current node to the path.
class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        from collections import defaultdict
        edges = defaultdict(list)
        for x, y in tickets:
            edges[x].append(y)
        for x in edges:
            edges[x].sort()
        ans = []
        def dfs(cur):
            while edges[cur]:
                nxt = edges[cur][0]
                edges[cur] = edges[cur][1:]
                dfs(nxt)
            ans.append(cur)
        dfs("JFK")
        return ans[::-1]