    #include <vector>
    #include <iostream>
     
    void dfs(int v, std::vector<int>& tin, std::vector<int>& tout, int& timer, std::vector<std::vector<int>>& graph) {
        tin[v] = timer++;
        for (int i = 0; i < graph[v].size(); ++i) {
            dfs(graph[v][i], tin, tout, timer, graph);
        }
        tout[v] = timer++;
        return;
    }
     
    int main()
    {
        int number_of_vertexes,parent,very_parent, number_of_questions,vertex_1,vertex_2;
        std::cin >> number_of_vertexes;
        std::vector<std::vector<int>> graph(number_of_vertexes);
        for (int i = 0; i < number_of_vertexes; ++i) {
            std::cin >> parent;
            if (parent == 0) {
                very_parent = i;
            }
            else {
                //graph[i].push_back(parent - 1);
                graph[parent - 1].push_back(i);
            }
        }
        std::vector<int> tin(number_of_vertexes);
        std::vector<int> tout(number_of_vertexes);
        int timer = 0;
        dfs(very_parent, tin, tout, timer, graph);
        std::cin >> number_of_questions;
        for (int i = 0; i < number_of_questions; ++i) {
            std::cin >> vertex_1 >> vertex_2;
            std::cout << ((tin[vertex_1 - 1] < tin[vertex_2 - 1]) && (tout[vertex_1 - 1] > tout[vertex_2 - 1]))<<'\n';
        }
    }
