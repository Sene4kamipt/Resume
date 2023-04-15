    #include<iostream>
    #include<vector>
    #include<queue>
     
    class Vertex_in_heap {
    public:
        long long dist;
        long long number;
    };
     
    class edge {
    public:
        long long where_to_go;
        long long dist;
    };
     
    struct Heap {
        std::vector<Vertex_in_heap> heap;
        std::vector<long long> links;
        long long size;
     
        void siftDown(long long curr_ver) {
            while (2 * curr_ver + 1 < size) {
                long long son = 2 * curr_ver + 1;
                if ((son + 1 < size) && (heap[son + 1].dist < heap[son].dist)) {
                    ++son;
                }
                if (heap[son].dist < heap[curr_ver].dist) {
                    std::swap(links[heap[curr_ver].number], links[heap[son].number]);
                    std::swap(heap[curr_ver], heap[son]);
                    curr_ver = son;
                }
                else {
                    break;
                }
            }
        }
     
        void extractMin() {
            heap[0] = heap[size - 1];
            links[heap[size - 1].number] = 0;
            heap.pop_back();
            --size;
            siftDown(0);
        }
     
        void siftUp(long long curr_ver) {
            while (curr_ver != 0) {
                long long parent = (curr_ver - 1) / 2;
                if (heap[curr_ver].dist < heap[parent].dist) {
                    std::swap(links[heap[curr_ver].number], links[heap[parent].number]);
                    std::swap(heap[curr_ver], heap[parent]);
                    curr_ver = parent;
                }
                else {
                    break;
                }
            }
        }
     
        void insert(long long new_elem, long long number) {
            links.push_back(size);
            heap.push_back(Vertex_in_heap{ new_elem, number });
            ++size;
            siftUp(size - 1);
        }
     
        void decreaseKey(long long delta, long long number) {
            heap[links[number]].dist -= delta;
            siftUp(links[number]);
        }
     
        Heap(long long number_of_vertexes, long long start) {
            size = 0;
            for (long long i = 0; i < number_of_vertexes; ++i) {
                this->insert(INT64_MAX, i);
            }
            this->decreaseKey(INT64_MAX, start);
           
        }
    };
     
     
     
    std::vector<long long> Deikstra(long long number_of_vertexes, std::vector<std::vector<edge>> graph, long long start) {
        std::vector<bool> used(number_of_vertexes, false);
        Heap unused(number_of_vertexes, start);
        std::vector<long long> dist(number_of_vertexes, INT64_MAX);
        dist[start] = 0;
        while (unused.size!=0) {
            if (unused.heap[0].dist == LLONG_MAX) {
                break;
            }
            long long v = unused.heap[0].number;
            dist[v] = unused.heap[0].dist;
            unused.extractMin();
            used[v] = true;
            for (int i = 0; i < graph[v].size();++i) {
                long long u = graph[v][i].where_to_go;
                if (used[u]) {
                    continue;
                }
                long long new_dist = dist[v] + graph[v][i].dist;
                if (new_dist < dist[u]) {
                    unused.decreaseKey(dist[u] - new_dist, u);
                    dist[u] = new_dist;
                }
            }
        }
        return dist;
    }
     
    int main() {
        long long heigth, a, b, c;
        std::cin >> heigth;
        std::cin >> a >> b >> c;
        if (b > c) {
            std::swap(b, c);
        }
        if (a > b) {
            std::swap(a, b);
        }
        if (a > heigth) {
            std::cout << 1;
            return 0;
        }
        if (a == 1) {
            std::cout << heigth;
            return 0;
        }
        std::vector<std::vector<edge>> graph(a);
        for (long long i = 0; i < a; ++i) {
            graph[i].push_back(edge{ (i + b) % a, b });
            graph[i].push_back(edge{ (i + c) % a, c });
        }
        std::vector<long long> mod_a_b_c_ans = Deikstra(graph.size(), graph, 0);
        long long answer = 0;
        for (long long i = 0; i < a; ++i) {
            long long remainder_a = mod_a_b_c_ans[i];
            if ((remainder_a != LLONG_MAX) && !(remainder_a >= heigth)) {
                answer += ((heigth - remainder_a - 1) / a) + 1;
            }
        }
        if (answer != 1) {
            std::cout << answer;
        }
        else {
            std::cout << "0";
        }
    }
