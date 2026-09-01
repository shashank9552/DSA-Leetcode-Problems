class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;

        vector<pair<int, int>> litter;

        // Find starting position and all litter cells.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } 
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int L = litter.size();

        // No litter to collect.
        if (L == 0) {
            return 0;
        }

        int fullMask = (1 << L) - 1;

        // Map every litter position to its bit.
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < L; i++) {
            litterId[litter[i].first][litter[i].second] = i;
        }

        /*
            visited[r][c][energy][mask]

            Since energy <= 50 and mask <= 1024,
            this is manageable.
        */
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << L, false)
                )
            )
        );

        struct State {
            int r;
            int c;
            int e;
            int mask;
            int dist;
        };

        queue<State> q;

        visited[sr][sc][energy][0] = true;
        q.push({sr, sc, energy, 0, 0});

        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

        while (!q.empty()) {
            State cur = q.front();
            q.pop();

            int r = cur.r;
            int c = cur.c;
            int e = cur.e;
            int mask = cur.mask;
            int dist = cur.dist;

            if (mask == fullMask) {
                return dist;
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // Outside grid.
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                    continue;
                }

                // Obstacle.
                if (classroom[nr][nc] == 'X') {
                    continue;
                }

                // Cannot move with zero energy.
                if (e == 0) {
                    continue;
                }

                int ne = e - 1;
                int nmask = mask;

                // Collect litter if this cell contains one.
                if (classroom[nr][nc] == 'L') {
                    int id = litterId[nr][nc];
                    nmask |= (1 << id);
                }

                // Reset energy on R.
                if (classroom[nr][nc] == 'R') {
                    ne = energy;
                }

                if (!visited[nr][nc][ne][nmask]) {
                    visited[nr][nc][ne][nmask] = true;
                    q.push({nr, nc, ne, nmask, dist + 1});
                }
            }
        }

        return -1;
    }
};