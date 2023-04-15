    #include<iostream>
    #include<vector>
     
     
    bool augment(int v, std::vector<std::vector<int>>& graph, std::vector<bool>& used, std::vector<int>& match){
        if(used[v]){
            return false;
        }
        used[v] = true;
        for(int to : graph[v]){
            if(match[to] == -1 || augment(match[to], graph, used, match)){
                match[to] = v;
                return true;
            }
        }
        return false;
    }
     
     
     
    int main(){
        int n, m, start, finish;
        std::cin>>n>>m;
        std::vector<std::vector<int>> graph_1_to_2(n);
        for(int i = 0; i < m; ++i){
            std::cin>>start>>finish;
            --start; --finish;
            graph_1_to_2[start].push_back(finish);
        }
        std::vector<bool> used (n, false);
        std::vector<int> match(n, -1);
        for(int i = 0; i < n; ++i){
            if(augment(i, graph_1_to_2, used, match)){
                used = std::vector<bool> (n, false);
            }
        }
        int answer = 0;
        for(int i = 0; i < n; ++i){
            if(match[i] != -1){
                ++answer;
            }
        }
        std::cout<<n - answer;
    }
