    #include <vector>
    #include <iostream>
    #include <algorithm>
     
    struct edge
    {
    public:
        int vertex;
        int number;
    };
     
    std::vector<int> bridges;
     
    void dfs(int v, std::vector<std::vector<edge>>& graph, std::vector<bool>& used,int p, std::vector<int>& ret, std::vector<int>& tin, int &timer) {
        used[v] = 1;
        tin[v] = timer++;
        ret[v] = tin[v];
        for (int i = 0; i < graph[v].size(); ++i) {
            if (graph[v][i].vertex==p) {
                continue;
            }
            else {
                if (used[graph[v][i].vertex]) {
                    ret[v] = std::min(ret[v], tin[graph[v][i].vertex]);
                }
                else {
                    dfs(graph[v][i].vertex, graph, used, v, ret, tin, timer);
                    ret[v] = std::min(ret[v], ret[graph[v][i].vertex]);
                    if (ret[graph[v][i].vertex] == tin[graph[v][i].vertex]) {
                        bridges.push_back(graph[v][i].number);
                    }
                }
            }
        }
        return;
    }
     
    int main()
    {
        int number_of_vertexes, number_of_edges, vertex_1, vertex_2;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<std::vector<edge>> graph(number_of_vertexes);
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> vertex_1>> vertex_2;
            graph[vertex_1 - 1].push_back(edge{ vertex_2 - 1,i });
            graph[vertex_2 - 1].push_back(edge{ vertex_1 - 1,i });
        }
        std::vector<bool> used(number_of_vertexes,0);
        std::vector<int> ret(number_of_vertexes, INT_MAX);
        std::vector<int> tin(number_of_vertexes, 0);
        int timer = 0;
        for (int i = 0; i < number_of_vertexes; ++i) {
            if (used[i] == 0) {
                dfs(i, graph, used,-1,ret,tin,timer);
            }
        }
        std::cout << bridges.size() << '\n';
        std::sort(bridges.begin(), bridges.end());
        for (int i = 0; i < bridges.size(); ++i) {
            std::cout << bridges[i]+1 << " ";
        }
        
    }
