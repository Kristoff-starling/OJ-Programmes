"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""

class Solution:
    def preorder(self, root: 'Node') -> List[int]:
        ans = []
        def dfs(cur: 'Node'):
            if cur == None: return
            ans.append(cur.val)
            for child in cur.children: dfs(child)
        dfs(root)
        return ans