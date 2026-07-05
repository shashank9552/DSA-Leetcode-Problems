class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {

        int n = grid.size();

        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int,int>> q;

        // Multi-source BFS from all thieves
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i,j});
                }
            }
        }

        vector<int> dx = {1,-1,0,0};
        vector<int> dy = {0,0,1,-1};

        while(!q.empty()) {

            auto [x,y] = q.front();
            q.pop();

            for(int k=0;k<4;k++) {

                int nx = x + dx[k];
                int ny = y + dy[k];

                if(nx<0 || ny<0 || nx>=n || ny>=n)
                    continue;

                if(dist[nx][ny] != INT_MAX)
                    continue;

                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx,ny});
            }
        }

        auto check = [&](int safe)->bool{

            if(dist[0][0] < safe)
                return false;

            queue<pair<int,int>> q;
            vector<vector<bool>> vis(n, vector<bool>(n,false));

            q.push({0,0});
            vis[0][0]=true;

            while(!q.empty()){

                auto [x,y]=q.front();
                q.pop();

                if(x==n-1 && y==n-1)
                    return true;

                for(int k=0;k<4;k++){

                    int nx=x+dx[k];
                    int ny=y+dy[k];

                    if(nx<0 || ny<0 || nx>=n || ny>=n)
                        continue;

                    if(vis[nx][ny])
                        continue;

                    if(dist[nx][ny] < safe)
                        continue;

                    vis[nx][ny]=true;
                    q.push({nx,ny});
                }
            }

            return false;
        };

        int left=0;
        int right=2*n;
        int ans=0;

        while(left<=right){

            int mid=left+(right-left)/2;

            if(check(mid)){
                ans=mid;
                left=mid+1;
            }
            else{
                right=mid-1;
            }
        }

        return ans;
    }
};