    #include <iostream>
    #include <vector>
    #include <algorithm>
     
    class Edge {
    public:
        int64_t vertex_1;
        int64_t vertex_2;
        int64_t cost;
        Edge() {
            vertex_1 = 0;
            vertex_2 = 0;
            cost = 0;
        };
        Edge(int64_t ver_1, int64_t ver_2, int64_t cost) {
            vertex_1 = ver_1;
            vertex_2 = ver_2;
            this->cost = cost;
        };
    };
     
    int64_t get(int64_t v, std::vector<int64_t>& parent) {
        if (parent[v] == -1) {
            return v;
        }
        return get(parent[v], parent);
    }
     
    void unite(int64_t vertex_1, int64_t vertex_2, std::vector<int64_t>& size, std::vector<int64_t>& parent) {
        vertex_1 = get(vertex_1, parent);
        vertex_2 = get(vertex_2, parent);
        if (size[vertex_1] < size[vertex_2]) {
            std::swap(vertex_1, vertex_2);
        }
        parent[vertex_2] = vertex_1;
        size[vertex_1] += size[vertex_2];
    }
     
    bool comp(Edge edge1, Edge edge2) {
        return edge1.cost < edge2.cost;
    }
     
    int main(){
        int64_t number_of_vertexes, number_of_edges;
        std::cin>>number_of_vertexes>>number_of_edges;
        std::vector<Edge> edges;
        std::vector<int64_t> weights(number_of_vertexes);
        int64_t start =0;
        for(int64_t i =0;i<number_of_vertexes;++i){
            std::cin>>weights[i];
            if (weights[start]>=weights[i]){
                start = i;
            }
        }
        std::vector<int64_t> parents(number_of_vertexes, -1);
        std::vector<int64_t> size(number_of_vertexes, 1);
        std::vector<std::vector<Edge>> graph(number_of_vertexes);
        for(int64_t i =0;i<number_of_edges;++i){
            int64_t input_vertex_1, input_vertex_2, cost;
            std::cin>>input_vertex_1>>input_vertex_2>>cost;
            input_vertex_1--; input_vertex_2--;
            if (weights[input_vertex_1]+weights[input_vertex_2]<cost){
                graph[input_vertex_1].emplace_back(input_vertex_1, input_vertex_2, weights[input_vertex_1] + weights[input_vertex_2]);
                graph[input_vertex_2].emplace_back(input_vertex_1, input_vertex_2, weights[input_vertex_1] + weights[input_vertex_2]);
                edges.emplace_back(input_vertex_1, input_vertex_2, weights[input_vertex_1] + weights[input_vertex_2]);
            }
            else{
                graph[input_vertex_1].emplace_back(input_vertex_1, input_vertex_2, cost);
                graph[input_vertex_2].emplace_back(input_vertex_1, input_vertex_2, cost);
                edges.emplace_back(input_vertex_1, input_vertex_2, cost);
            }
        }
        for(int64_t i = 0;i<number_of_vertexes;++i){
            if (i!=start){
                Edge e(start, i, weights[start]+weights[i]);
                graph[i].emplace_back(start, i, weights[start] + weights[i]);
                graph[start].emplace_back(start, i, weights[start] + weights[i]);
                edges.emplace_back(start, i, weights[start] + weights[i]);
            }
        }
        int64_t ans =0;
        std::sort(edges.begin(), edges.end(), comp);
        for(int64_t i =0;i<edges.size();++i){
            int64_t parent_ver_1 = get(edges[i].vertex_1, parents);
            int64_t parent_ver_2 = get(edges[i].vertex_2, parents);
            if (parent_ver_1 != parent_ver_2) {
                unite(parent_ver_2, parent_ver_1, size, parents);
                ans += edges[i].cost;
            }
        }
        std::cout<<ans;
    }
