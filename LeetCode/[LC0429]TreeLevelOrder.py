"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""

class Solution:
    def levelOrder(self, root: 'Node') -> List[List[int]]:
        if root is None: return []
        ans, q, last = [], [root, 0], -1
        while len(q) > 0:
            cur, depth, q = q[0], q[1], q[2:]
            if depth == last: ans[-1].append(cur.val)
            else: ans.append([cur.val])
            last = depth
            if not cur.children is None:
                for child in cur.children:
                    q.append(child)
                    q.append(depth + 1)
        return ans