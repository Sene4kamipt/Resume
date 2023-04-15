    #include<iostream>
    #include<vector>
    #include<queue>
    #include<unordered_map>
    #include<climits>
     
    std::vector<int> BFS(std::vector<std::vector<int>>& graph, int start, int finish){
        int n = graph.size();
        std::vector<int> dist (n, INT_MAX);
        std::vector<int> from (n, INT_MAX);
        dist[start] = 0;
        from[start] = start;
        std::queue<int> q;
        q.push(start);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(int to : graph[v]){
                if(dist[to] == INT_MAX){
                    dist[to] = dist[v] + 1;
                    from[to] = v;
                    q.push(to);
                }
            }
        }
        if(dist[finish] == INT_MAX){
            std::vector<int> answer;
            return answer;
        }
        std::vector<int> answer (dist[finish] + 1);
        int last = finish;
        for(int i = dist[finish]; i >= 0; --i){
            answer[i] = last;
            last = from[last];
        }
        return answer;
    }
     
    int main(){
        int n, m, start, finish, first, second;
        std::cin>>n>>m>>start>>finish;
        --start; --finish;
        std::vector<std::vector<int>> graph(n);
        for(int i = 0; i < m; ++i){
            std::cin>>first>>second;
            graph[first-1].push_back(second-1);
        }
        std::vector<int> first_way = BFS(graph, start, finish);
        if(first_way.empty()){
            std::cout<<"NO";
            return 0;
        }
        for(int i = 0; i < first_way.size() - 1; ++i){
            first = first_way[i];
            second = first_way[i+1];
            graph[second].push_back(first);
            for(int j = 0; j < graph[first].size(); ++j){
                if(graph[first][j] == second){
                    std::swap(graph[first][j], graph[first][graph[first].size() - 1]);
                    graph[first].pop_back();
                    break;
                }
            }
        }
        std::vector<int> second_way = BFS(graph, start, finish);
        if(second_way.empty()){
            std::cout<<"NO";
            return 0;
        }
        std::vector<std::vector<int>> new_graph(n);
        for(int i = 0; i < first_way.size() - 1; ++i){
            new_graph[first_way[i]].push_back(first_way[i + 1]);
        }
        for(int i = 0; i < second_way.size() - 1; ++i){
            if(!new_graph[second_way[i+1]].empty() && new_graph[second_way[i+1]][0] == second_way[i]){
                new_graph[second_way[i+1]].pop_back();
            } else {
                new_graph[second_way[i]].push_back(second_way[i+1]);
            }
        }
     
        first_way = BFS(new_graph, start, finish);
     
        for(int i = 0; i < first_way.size() - 1; ++i){
            first = first_way[i];
            second = first_way[i+1];
            for(int j = 0; j < new_graph[first].size(); ++j){
                if(new_graph[first][j] == second){
                    std::swap(new_graph[first][j], new_graph[first][new_graph[first].size() - 1]);
                    new_graph[first].pop_back();
                    break;
                }
            }
        }
        second_way = BFS(new_graph, start, finish);
     
        std::cout<<"YES\n";
        for(int i = 0; i < first_way.size(); ++i){
            std::cout<<first_way[i] + 1<<' ';
        } std::cout<<'\n';
        for(int i = 0; i < second_way.size(); ++i){
            std::cout<<second_way[i] + 1<<' ';
        }
    }
     
