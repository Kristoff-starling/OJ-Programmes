"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""

class Solution:
    def postorder(self, root: 'Node') -> List[int]:
        self.ans = []

        def dfs(cur: 'Node'):
            if cur is not None:
                for child in cur.children: dfs(child)
                self.ans.append(cur.val)
        
        dfs(root)
        return self.ans