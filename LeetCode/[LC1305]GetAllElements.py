class Solution:
    def getAllElements(self, root1: TreeNode, root2: TreeNode) -> List[int]:
        self.vlist = []
        def dfs(self, cur: TreeNode):
            if cur is None: return
            self.vlist.append(cur.val)
            dfs(self, cur.left)
            dfs(self, cur.right)
        dfs(self, root1)
        dfs(self, root2)
        return sorted(self.vlist, key=None)