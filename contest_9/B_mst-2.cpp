    #include <iostream>
    #include <vector>
    #include <algorithm>
     
    class Edge{
    public:
        int vertex_1;
        int vertex_2;
        int cost;
        Edge() {
            vertex_1 = 0;
            vertex_2 = 0;
            cost = 0;
        };
        Edge(int ver_1, int ver_2, int cost) {
            vertex_1 = ver_1;
            vertex_2 = ver_2;
            this->cost = cost;
        };
    };
     
    int get(int v, std::vector<int> &p){
        if (p[v]==-1){
            return v;
        }
        return get(p[v], p);
    }
     
    void unite(int u, int v, std::vector<int> &size, std::vector<int> &p){
        u = get(u, p);
        v = get(v, p);
        if (size[u]<size[v]){
            std::swap(u, v);
        }
        p[v] = u;
        size[u] +=size[v];
    }
     
    bool comp(Edge edge1, Edge edge2) {
        return edge1.cost < edge2.cost;
    }
     
    int main() {
        int number_of_vertexes, number_of_edges;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<Edge> edges;
        std::vector<int> parents(number_of_vertexes, -1);
        std::vector<int> size(number_of_vertexes, 1);
        std::vector<std::vector<Edge>> graph(number_of_vertexes);
        for (int i = 0; i < number_of_edges; ++i) {
            int input_vertex_1, input_vertex_2, cost;
            std::cin >> input_vertex_1 >> input_vertex_2 >> cost;
            Edge input_edge(input_vertex_1 - 1, input_vertex_2 - 1, cost);
            graph[input_vertex_1 - 1].push_back(input_edge);
            graph[input_vertex_2 - 1].push_back(input_edge);
            edges.push_back(input_edge);
        }
        int ans = 0;
        std::sort(edges.begin(), edges.end(), comp);
        for (int i = 0; i < number_of_edges; ++i) {
            int parent_ver_1 = get(edges[i].vertex_1, parents);
            int parent_ver_2 = get(edges[i].vertex_2, parents);
            if (parent_ver_1 != parent_ver_2) {
                unite(parent_ver_2, parent_ver_1, size, parents);
                ans += edges[i].cost;
            }
        }
        std::cout << ans;
    }
