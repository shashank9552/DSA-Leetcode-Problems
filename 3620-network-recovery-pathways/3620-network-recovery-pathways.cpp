class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int, int>>> graph(n);
        vector<int> indegree(n, 0);
        vector<int> costs;

        // Build graph
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].push_back({v, w});
            indegree[v]++;
            costs.push_back(w);
        }

        // Topological Sort
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &[v, w] : graph[u]) {
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }

        sort(costs.begin(), costs.end());
        costs.erase(unique(costs.begin(), costs.end()), costs.end());

        auto check = [&](int limit) -> bool {
            const long long INF = LLONG_MAX / 4;
            vector<long long> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {
                if (dist[u] == INF)
                    continue;

                // Skip offline intermediate nodes
                if (u != 0 && u != n - 1 && !online[u])
                    continue;

                for (auto &[v, w] : graph[u]) {

                    if (w < limit)
                        continue;

                    if (v != 0 && v != n - 1 && !online[v])
                        continue;

                    dist[v] = min(dist[v], dist[u] + (long long)w);
                }
            }

            return dist[n - 1] <= k;
        };

        int left = 0;
        int right = (int)costs.size() - 1;
        int ans = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (check(costs[mid])) {
                ans = costs[mid];
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return ans;
    }
};