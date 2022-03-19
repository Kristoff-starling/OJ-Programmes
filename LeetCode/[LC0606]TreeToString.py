# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def tree2str(self, root: Optional[TreeNode]) -> str:
        if root is None: return ''
        res = str(root.val)
        if root.left: res += '(' + self.tree2str(root.left) + ')'
        elif root.right: res += '()'
        if root.right: res += '(' + self.tree2str(root.right) + ')'
        return res