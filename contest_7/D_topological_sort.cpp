    #include <vector>
    #include <iostream>
    #include <algorithm>
     
    bool compa(const std::vector<int>a,const std::vector<int>b) {
        return a[1] > b[1];
    }
     
    void dfs(int v, std::vector<std::vector<int>>& graph, std::vector<int>& colors, int& flag, std::vector<std::vector<int>> &tin, std::vector<std::vector<int>> &tout, int &timer) {
        colors[v] = 1;
        tin[v] = { v,timer++ };
        for (int i = 0; i < graph[v].size(); ++i) {
            if (flag > 0) {
                break;
            }
            if (colors[graph[v][i]] == 2) {
                continue;
            }
            else {
                if (colors[graph[v][i]] == 1) {
                    flag = 1;
                    colors[v] = 2;
                    return;
                }
                else {
                    dfs(graph[v][i], graph, colors, flag,tin,tout,timer);
                }
            }
        }
        colors[v] = 2;
        tout[v] = { v,timer++ };
        return;
    }
     
    int main()
    {
        int number_of_edges, number_of_vertexes, vertex_1, vertex_2;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<std::vector<int>> graph(number_of_vertexes);
        std::vector<std::vector<int>> tin(number_of_vertexes);
        std::vector<std::vector<int>> tout(number_of_vertexes);
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> vertex_1 >> vertex_2;
            graph[vertex_1 - 1].push_back(vertex_2 - 1);
        }
        std::vector<int> colors(number_of_vertexes, 0);
        int flag = 0;
        int timer = 0;
        for (int i = 0; i < number_of_vertexes; ++i) {
            if (colors[i] == 0) {
                dfs(i, graph, colors, flag, tin, tout, timer);
            }
            if (flag > 0) {
                std::cout << "-1";
                return 0;
            }
        }
        std::sort(tout.begin(), tout.end(), compa);
        for (int i = 0; i < tout.size(); ++i) {
            std::cout << tout[i][0]+1<<" ";
        }
    }


