    #include <vector>
    #include <iostream>
     
    void dfs(int v, std::vector<std::vector<int>>& graph, std::vector<int>& colors, std::vector<int> &number_of_component, int &counter) {
        colors[v] = 1;
        number_of_component[v] = counter;
        for (int i = 0; i < graph[v].size(); ++i) {
            if (colors[graph[v][i]] >= 1) {
                continue;
            }
            else {
                dfs(graph[v][i], graph, colors, number_of_component, counter);
            }
        }
        colors[v] = 2;
        return;
    }
     
    int main()
    {
        int number_of_vertexes, number_of_edges,vertex_1,vertex_2;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<std::vector<int>> graph(number_of_vertexes);
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> vertex_1 >> vertex_2;
            graph[vertex_1 - 1].push_back(vertex_2 - 1);
            graph[vertex_2 - 1].push_back(vertex_1 - 1);
        }
        std::vector<int>colors(number_of_vertexes, 0);
        std::vector<int> number_of_component(number_of_vertexes,0);
        int counter = 1;
        for (int i = 0; i < number_of_vertexes; ++i) {
            if (colors[i] == 0) {
                dfs(i, graph, colors, number_of_component, counter);
                ++counter;
            }
        }
        std::cout << counter - 1<<'\n';
        for (int i = 0; i < number_of_vertexes; ++i) {
            std::cout << number_of_component[i] << " ";
        }
    }
