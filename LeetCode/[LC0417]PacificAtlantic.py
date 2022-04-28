class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        n, m = len(heights), len(heights[0])
        cnt = [[0] * m for _ in range(0, n)]
        pvisited = [[False] * m for _ in range(0, n)]
        avisited = [[False] * m for _ in range(0, n)]
        q = [[0, i] for i in range(0, m)] + [[i, 0] for i in range(1, n)]
        dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        while len(q) > 0:
            x, y, q = q[0][0], q[0][1], q[1:]
            if pvisited[x][y] == True: continue
            cnt[x][y] += 1
            pvisited[x][y] = True
            for (dx, dy) in dirs:
                xx, yy = x + dx, y + dy
                if 0 <= xx <= n-1 and 0 <= yy <= m-1 and pvisited[xx][yy] == False and heights[xx][yy] >= heights[x][y]:
                    q.append([xx, yy])
        q = [[n-1, i] for i in range(0, m)] + [[i, m-1] for i in range(0, n)]
        while len(q) > 0:
            x, y, q = q[0][0], q[0][1], q[1:]
            if avisited[x][y] == True: continue
            cnt[x][y] += 1
            avisited[x][y] = True
            for (dx, dy) in dirs:
                xx, yy = x + dx, y + dy
                if 0 <= xx <= n-1 and 0 <= yy <= m-1 and avisited[xx][yy] == False and heights[xx][yy] >= heights[x][y]:
                    q.append([xx, yy])
        return [[x, y] for x in range(0, n) for y in range(0, m) if cnt[x][y] == 2]
