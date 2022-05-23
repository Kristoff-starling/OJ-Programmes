class Solution:
    def cutOffTree(self, forest: List[List[int]]) -> int:
        n, m = len(forest), len(forest[0])
        dist = [[0 for _ in range(m)] for __ in range(n)]
        move = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        def bfs(sx: int, sy: int):
            for i in range(n):
                for j in range(m):
                    dist[i][j] = n * m * 2
            dist[sx][sy] = 0
            q = deque([(sx, sy)])
            while q:
                cx, cy = q.popleft()
                # print(cx, cy)
                for dx, dy in move: 
                    nx, ny = cx + dx, cy + dy
                    if 0 <= nx < n and 0 <= ny < m and forest[nx][ny] > 0 and dist[nx][ny] > dist[cx][cy] + 1:
                        dist[nx][ny] = dist[cx][cy] + 1
                        q.append((nx, ny))
        
        cx, cy, ans = 0, 0, 0
        while True:
            bfs(cx, cy)
            h, tx, ty = 1000000001, 0, 0
            for i in range(n):
                for j in range(m):
                    if 1 < forest[i][j] < h:
                        h, tx, ty = forest[i][j], i, j
            if h == 1000000001: break
            elif dist[tx][ty] > n * m: return -1
            else:
                ans += dist[tx][ty]
                forest[tx][ty] = 1
                cx, cy = tx, ty
        return ans