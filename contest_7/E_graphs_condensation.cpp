    #include <vector>
    #include <iostream>
    #include <algorithm>
    #include <set>
     
    bool compa(const std::vector<int>a, const std::vector<int>b) {
        return a[1] > b[1];
    }
     
    void dfs(int v, std::vector<std::vector<int>>& graph, std::vector<int>& colors, std::vector<std::vector<int>>& tin, std::vector<std::vector<int>>& tout, int& timer) {
        colors[v] = 1;
        tin[v] = { v,timer++ };
        for (int i = 0; i < graph[v].size(); ++i) {
            if (colors[graph[v][i]] >= 1) {
                continue;
            }
            else {
                dfs(graph[v][i], graph, colors, tin, tout, timer);
            }
        }
        colors[v] = 2;
        tout[v] = { v,timer++ };
        return;
    }
     
    void anti_dfs(int v, std::vector<std::vector<int>>& graph, std::vector<int>& colors, int counter, std::vector<int> &number_of_kss) {
        colors[v] = 1;
        number_of_kss[v] = counter;
        for (int i = 0; i < graph[v].size(); ++i) {
            if (colors[graph[v][i]] >= 1) {
                continue;
            }
            else {
                anti_dfs(graph[v][i], graph, colors, counter, number_of_kss);
            }
        }
        colors[v] = 2;
        return;
    }
     
    int main()
    {
        int number_of_edges, number_of_vertexes, vertex_1, vertex_2;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<std::vector<int>> graph(number_of_vertexes);
        std::vector<std::vector<int>> anti_graph(number_of_vertexes);
        std::vector<std::vector<int>> tin(number_of_vertexes);
        std::vector<std::vector<int>> tout(number_of_vertexes);
        std::vector<std::vector<int>> edges(number_of_edges, { 0,0 });
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> vertex_1 >> vertex_2;
            graph[vertex_1 - 1].push_back(vertex_2 - 1);
            anti_graph[vertex_2 - 1].push_back(vertex_1 - 1);
            edges[i] = { vertex_1-1,vertex_2-1 };
        }
        std::vector<int> colors(number_of_vertexes, 0);
        std::vector<int> anti_colors(number_of_vertexes, 0);
        int timer = 0;
        for (int i = 0; i < number_of_vertexes; ++i) {
            if (colors[i] == 0) {
                dfs(i, graph, colors, tin, tout, timer);
            }
        }
        std::sort(tout.begin(), tout.end(), compa);
        std::vector<int> number_of_kss(number_of_vertexes, -1);
        int counter = 0;
        for (int i = 0; i < tout.size(); ++i) {
            if (number_of_kss[tout[i][0]] == -1) {
                anti_dfs(tout[i][0],anti_graph,anti_colors,counter,number_of_kss);
                ++counter;
            }
        }
        std::set<std::vector<int>> edges_btw_kss;
        for (int i = 0; i < number_of_edges; ++i) {
            if (number_of_kss[edges[i][0]] != number_of_kss[edges[i][1]]) {
                edges_btw_kss.insert({ number_of_kss[edges[i][0]], number_of_kss[edges[i][1]] });
            }
        }
        std::cout << edges_btw_kss.size();
    }
