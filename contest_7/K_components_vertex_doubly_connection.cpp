    #include <iostream>
    #include <vector>
    #include <unordered_map>
    #include <algorithm>
     
    int max_color = 0;
    long long modul = 500000;
     
    void dfs(int v, int p, std::vector<std::vector<int>> & graph, std::vector<bool> &used, std::vector<int> &tin, std::vector<int> &tout, std::vector<int> &parent, std::unordered_map<long long, int> &colors, int &timer) {
        if (used[v]) {
            return;
        }
        tin[v] = timer++;
        parent[v] = p;
        used[v] = true;
        tout[v] = tin[v];
        for (int to = 0; to < graph[v].size(); ++to) {
            if (graph[v][to] == p) {
                continue;
            }
            if (used[graph[v][to]]) {
                tout[v] = std::min(tout[v], tin[graph[v][to]]);
            }
            else {
                dfs(graph[v][to], v, graph, used, tin, tout, parent, colors, timer);
                tout[v] = std::min(tout[v], tout[graph[v][to]]);
            }
        }
    }
     
    void paint(int v, int color, int p, std::vector<std::vector<int>> &graph, std::vector<bool>& used, std::vector<int> &tin, std::vector<int> &tout, std::unordered_map<long long, int> &colors) {
        used[v] = true;
        for (int to = 0; to < graph[v].size();++to) {
            if (graph[v][to] == p) {
                continue;
            }
            if (!used[graph[v][to]]) {
                if (tout[graph[v][to]] >= tin[v]) {
                    int new_color = ++max_color;
                    colors[v * modul + graph[v][to]] = new_color;
                    colors[graph[v][to] * modul + v] = new_color;
                    paint(graph[v][to], new_color, v, graph, used, tin, tout, colors);
                }
                else {
                    colors[v * modul + graph[v][to]] = color;
                    colors[graph[v][to] * modul + v] = color;
                    paint(graph[v][to], color, v, graph, used, tin, tout, colors);
                }
            }
            else {
                if (tin[graph[v][to]] < tin[v]) {
                    colors[v * modul + graph[v][to]] = color;
                    colors[graph[v][to] * modul + v] = color;
                }
            }
        }
    }
     
    int main() {
        std::ios::sync_with_stdio(0);
        std::cin.tie(0);
        std::cout.tie(0);
        int number_of_vertex, number_of_edges, vertex_1, vertex_2;
        std::cin >> number_of_vertex >> number_of_edges;
        std::vector<std::vector<int>> graph(number_of_vertex);
        std::vector<std::vector<int>> edges(number_of_edges);
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> vertex_1 >> vertex_2;
            graph[vertex_1].push_back(vertex_2);
            graph[vertex_2].push_back(vertex_1);
            edges[i] = { vertex_1, vertex_2 };
        }
        int timer = 0;
        std::unordered_map<long long, int> colors;
        std::vector<int> tin(number_of_vertex);
        std::vector<bool> used(number_of_vertex);
        std::vector<int> parent(number_of_vertex, -1);
        std::vector<int> tout(number_of_vertex, 1000000);
        for (int i = 0; i < number_of_vertex; ++i) {
            dfs(i, -1, graph, used, tin, tout, parent, colors, timer);
        }
        used = std::vector<bool>(number_of_vertex, false);
        for (int v = 0; v < number_of_vertex; ++v) {
            if (!used[v]) {
                ++max_color;
                paint(v, max_color, -1, graph, used, tin, tout, colors);
            }
        }
        std::unordered_map<int, std::vector<int>> components;
        for (int i = 0; i < number_of_edges; ++i) {
            int color = colors[edges[i][0] * modul + edges[i][1]];
            components[color].push_back(i);
        }
        std::cout << components.size() << "\n";
        for (int i = 0; i < components.size();++i) {
            if (components[i].size() != 0) {
                std::cout << components[i].size() << " ";
                for (int j = 0; j < components[i].size(); ++j) {
                    std::cout << components[i][j] << " ";
                }
                std::cout << "\n";
            }
        }
    }
