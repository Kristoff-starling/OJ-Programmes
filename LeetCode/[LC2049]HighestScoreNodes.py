class treenode():
    def __init__(self, left=None, right=None):
        self.left = left
        self.right = right

class Solution:
    def countHighestScoreNodes(self, parents: List[int]) -> int:
        tree = [treenode() for _ in range(len(parents))]
        self.maxn, self.maxncnt = 0, 1

        def dfs(cur: treenode) -> int:
            if cur is None: return 0
            szl, szr = dfs(cur.left), dfs(cur.right)
            szu = len(parents) - szl - szr - 1
            tmp = 1
            if szl != 0: tmp *= szl
            if szr != 0: tmp *= szr
            if szu != 0: tmp *= szu
            if tmp > self.maxn:
                self.maxn, self.maxncnt = tmp, 1
            elif tmp == self.maxn:
                self.maxncnt += 1
            return szl + szr + 1
        
        def addedge(cur: treenode, son: int) -> None:
            if cur.left is None:
                cur.left = son
            elif cur.right is None:
                cur.right = son
            else:
                assert False

        for cur, father in enumerate(parents):
            if father != -1: addedge(tree[father], tree[cur])
        
        dfs(tree[0])
        return self.maxncnt