    #include<iostream>
    #include<vector>
    #include<string>
    #include<queue>
     
    struct edge {
        int where_to;
        int dist;
     
    };
     
    int64_t OKBFS(std::vector<std::vector<edge>>& graph, int start_vertex, int finish_vertex) {
        int n = graph.size();
     
        std::vector<std::queue<int>> q(101);
        q[0].push(start_vertex);
     
        std::vector<bool> used(n, false);
     
        std::vector<int64_t> dist(n, LLONG_MAX);
        dist[start_vertex] = 0;
     
        for (int x = 0; x < n * 100; ++x) {
            int y = x % 101;
            while (!q[y].empty()) {
                int v = q[y].front();
                q[y].pop();
                if (used[v]) {
                    continue;
                }
                if (v == finish_vertex) {
                    return dist[finish_vertex];
                }
                for (int i = 0; i < graph[v].size();++i) {
                    if (dist[graph[v][i].where_to] > dist[v] + graph[v][i].dist) {
                        dist[graph[v][i].where_to] = dist[v] + graph[v][i].dist;
                        q[dist[graph[v][i].where_to] % 101].push(graph[v][i].where_to);
                    }
                }
                used[v] = true;
            }
        }
        return dist[finish_vertex];
    }
     
    int main() {
        int number_of_vertexes, number_of_edges, vertex_1, vertex_2, input_1, input_2, dist;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::cin >> vertex_1 >> vertex_2;
        --vertex_1; --vertex_2;
        std::vector<std::vector<edge>> graph(number_of_vertexes);
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> input_1 >> input_2 >> dist;
            graph[input_1 - 1].emplace_back(edge{ input_2 - 1, dist });
            graph[input_2 - 1].emplace_back(edge{ input_1 - 1, dist });
        }
     
        long long len = OKBFS(graph, vertex_1, vertex_2);
        if (len == LLONG_MAX) {
            std::cout << -1;
        }
        else {
            std::cout << len;
        }
    }


