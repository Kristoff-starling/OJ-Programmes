# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def findTarget(self, root: Optional[TreeNode], k: int) -> bool:
        dic, ans = {}, False
        def dfs(root: Optional[TreeNode]) -> bool:
            if root is None: return False
            if (k - root.val) in dic: return True
            dic[root.val] = True
            return True if dfs(root.left) or dfs(root.right) else False
        return dfs(root)