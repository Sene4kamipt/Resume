    #include <vector>
    #include <iostream>
     
    void dfs(int v, std::vector<std::vector<int>>& graph, std::vector<int> &colors, int & flag, std::vector<int> &cycle, int &beginning_vertex) {
        colors[v] = 1;
        for (int i = 0; i < graph[v].size(); ++i) {
            if (flag > 0) {
                break;
            }
            if (colors[graph[v][i]] == 2) {
                continue;
            }
            else {
                if (colors[graph[v][i]] == 1) {
                    beginning_vertex = graph[v][i];
                    flag = 1;
                    cycle.push_back(v);
                    colors[v] = 2;
                    return;
                }
                else {
                    dfs(graph[v][i], graph, colors, flag, cycle, beginning_vertex);
                }
            }
        }
        if (flag == 1) {
            cycle.push_back(v);
        }
        if (v == beginning_vertex) {
            flag = 2;
        }
        colors[v] = 2;
        return;
    }
     
    int main()
    {
        int number_of_edges, number_of_vertexes, vertex_1,vertex_2;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<std::vector<int>> graph(number_of_vertexes);
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> vertex_1 >> vertex_2;
            graph[vertex_1 - 1].push_back(vertex_2 - 1);
        }
        std::vector<int> colors(number_of_vertexes,0);
        int flag = 0;
        int beginning_vertex=-1;
        std::vector<int> cycle;
        for (int i = 0; i < number_of_vertexes; ++i) {
            if (colors[i] == 0) {
                dfs(i,graph,colors,flag,cycle,beginning_vertex);
            }
            if (flag > 0) {
                break;
            }
        }
        if (flag == 2) {
            std::cout << "YES" << '\n';
            for (int i = 0; i < cycle.size(); ++i) {
                std::cout << cycle[cycle.size()-1-i] +1<< " ";
            }
        }
        else {
            std::cout << "NO";
        }
    }
