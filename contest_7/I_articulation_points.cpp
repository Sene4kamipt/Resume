    #include <vector>
    #include <iostream>
    #include <algorithm>
     
    struct edge
    {
    public:
        int vertex;
        int number;
    };
     
    std::vector<int> joints;
     
    void dfs(int v, std::vector<std::vector<int>>& graph, std::vector<bool>& used,int p, std::vector<int>& ret, std::vector<int>& tin, int &timer) {
        used[v] = 1;
        //std::cout << v << '\n';
        tin[v] = timer++;
        ret[v] = tin[v];
        bool flag=0;
        bool added = 0;
        if (timer == 1) {
            flag = 1;
        }
        int counter = 0;
        for (int i = 0; i < graph[v].size(); ++i) {
            if (graph[v][i]==p) {
                continue;
            }
            else {
                if (used[graph[v][i]]) {
                    ret[v] = std::min(ret[v], tin[graph[v][i]]);
                }
                else {
                    if (flag) {
                        ++counter;
                    }
                    dfs(graph[v][i], graph, used, v, ret, tin, timer);
                    ret[v] = std::min(ret[v], ret[graph[v][i]]);
                    if ((ret[graph[v][i]] >= tin[v])&&(!added)&&(!flag)) {
                        joints.push_back(v);
                        added = true;
                        //std::cout << flag << " "<<v;
                    }
                }
            }
        }
        if (counter > 1) {
            joints.push_back(v);
        }
        return;
    }
     
    int main()
    {
        int number_of_vertexes, number_of_edges, vertex_1, vertex_2;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<std::vector<int>> graph(number_of_vertexes);
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> vertex_1>> vertex_2;
            graph[vertex_1 - 1].push_back(vertex_2 - 1);
            graph[vertex_2 - 1].push_back(vertex_1 - 1);
        }
        std::vector<bool> used(number_of_vertexes,0);
        std::vector<int> ret(number_of_vertexes, INT_MAX);
        std::vector<int> tin(number_of_vertexes, 0);
        int timer = 0;
        for (int i = 0; i < number_of_vertexes; ++i) {
            timer = 0;
            if (used[i] == 0) {
                dfs(i, graph, used,-1,ret,tin,timer);
            }
        }
        std::cout << joints.size() << '\n';
        std::sort(joints.begin(), joints.end());
        for (int i = 0; i < joints.size(); ++i) {
            std::cout << joints[i]+1 << " ";
        }
    }
