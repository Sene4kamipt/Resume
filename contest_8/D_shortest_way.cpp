    #include<iostream>
    #include<vector>
    #include<string>
    #include<queue>
     
    long long absent = 1000000000000000001;
    long long minus_cycle = 1000000000000000002;
     
    void dfs(long long v, std::vector<std::vector<long long>>& graph, std::vector<bool>& used) {
        used[v] = true;
        for (int i = 0; i < graph[v].size();++i) {
            if (used[graph[v][i]]) {
                continue;
            }
            dfs(graph[v][i], graph, used);
        }
    }
     
    std::vector<long long> Floyd_Bell(int number_of_vertexes, long long start_vertex, std::vector<std::vector<long long>>& graph, std::vector<std::vector<long long>>& to_graph, std::vector<std::vector<long long>>& from_graph) {
        std::vector<std::vector<long long>> dp(2, std::vector<long long>(number_of_vertexes + 1, INT64_MAX));
        dp[0][start_vertex] = 0;
        for (long long k = 1; k < number_of_vertexes + 1; ++k) {
            for (long long v = 0; v < number_of_vertexes; ++v) {
                dp[1][v] = dp[0][v];
                for (int from = 0; from < from_graph[v].size();++from) {
                    if (dp[0][from_graph[v][from]] != INT64_MAX) {
                        dp[1][v] = std::min(dp[1][v], dp[0][from_graph[v][from]] + graph[from_graph[v][from]][v]);
                    }
                }
            }
            std::swap(dp[0], dp[1]);
        }
        std::swap(dp[0], dp[1]);
        std::vector<long long> answer(number_of_vertexes);
        for (long long i = 0; i < number_of_vertexes; ++i) {
            if (dp[0][i] == INT64_MAX) {
                answer[i] = absent;
                continue;
            }
            answer[i] = dp[0][i];
        }
        std::vector<bool> visited(number_of_vertexes, false);
        for (long long i = 0; i < number_of_vertexes; ++i) {
            if (dp[0][i] == dp[1][i]) {
                continue;
            }
            dfs(i, to_graph, visited);
        }
     
        for (long long i = 0; i < number_of_vertexes; ++i) {
            if (visited[i]) {
                answer[i] = minus_cycle;
            }
        }
     
        return answer;
    }
     
    int main() {
        int64_t number_of_vertexes, number_of_edges, start_vertex, input_1, input_2, dist;
        std::cin >> number_of_vertexes >> number_of_edges >> start_vertex;
        --start_vertex;
        std::vector<std::vector<long long>> graph(number_of_vertexes, std::vector<int64_t>(number_of_vertexes, INT64_MAX));
        std::vector<std::vector<long long>> to_graph(number_of_vertexes);
        std::vector<std::vector<long long>> from_graph(number_of_vertexes);
        for (int64_t i = 0; i < number_of_edges; ++i) {
            std::cin >> input_1 >> input_2 >> dist;
            --input_1; --input_2;
            if (graph[input_1][input_2] == INT64_MAX) {
                to_graph[input_1].push_back(input_2);
                from_graph[input_2].push_back(input_1);
            }
            graph[input_1][input_2] = std::min(graph[input_1][input_2], dist);
        }
        for (long long i = 0; i < number_of_vertexes; ++i) {
            graph[i][i] = std::min(graph[i][i], (long long)0);
        }
        std::vector<long long> answer = Floyd_Bell(number_of_vertexes, start_vertex, graph, to_graph, from_graph);
        for (long long i = 0; i < number_of_vertexes; ++i) {
            if (answer[i] == minus_cycle) {
                std::cout << '-' << '\n';
            }
            else {
                if (answer[i] == absent) {
                    std::cout << '*' << '\n';
                }
                else {
                    std::cout << answer[i] << '\n';
                }
            }
        }
    }
