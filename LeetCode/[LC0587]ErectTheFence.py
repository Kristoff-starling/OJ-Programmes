class Solution:
    def outerTrees(self, trees: List[List[int]]) -> List[List[int]]:
        def det(p, q, r):
            return (p[0] - r[0]) * (q[1] - r[1]) - (p[1] - r[1]) * (q[0] - r[0])
        
        def check_valid(q, ptr):
            q.append(ptr)
            while len(q) >= 3 and det(q[-3], q[-2], q[-1]) < 0:
                q.pop(-2)
            return q

        trees.sort(key = lambda p: (p[0], p[1]))
        h1 = reduce(check_valid, trees, [])
        h2 = reduce(check_valid, trees[::-1], [])
        return h1 + [item for item in h2 if not item in h1]
        