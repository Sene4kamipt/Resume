    #include <iostream>
    #include <vector>
     
    int main() {
        std::ios::sync_with_stdio(0);
        std::cin.tie(0);
        std::cout.tie(0);
        int32_t n;
        std::cin >> n;
        std::vector<std::vector<int32_t>> graph(n + 1, std::vector<int32_t>(n + 1));
        for (int32_t i = 1; i <= n; ++i) {
            for (int32_t j = 1; j <= n; ++j) {
                std::cin >> graph[i][j];
            }
        }
        std::vector<int32_t> potentials_raws(n + 1);
        std::vector<int32_t>potentials_columns(n + 1);
        std::vector<int32_t>matching(n + 1);
        std::vector<int32_t>mins_places(n + 1);
        for (int32_t i = 1; i <= n; ++i) {
            matching[0] = i;
            int32_t curr_raw = 0;
            std::vector<int32_t> delta_for_col(n + 1, 214748364);
            std::vector<bool> used(n + 1, false);
            bool flag = true;
            while ( flag || (matching[curr_raw] != 0)) {
                used[curr_raw] = true;
                int32_t curr_column = matching[curr_raw];
                int32_t delta = 214748364;
                int32_t next_raw;
                for (int32_t j = 1; j <= n; ++j){
                    if (!used[j]) {
                        int32_t cur = graph[curr_column][j] - potentials_raws[curr_column] - potentials_columns[j];
                        if (cur < delta_for_col[j]) {
                            delta_for_col[j] = cur;
                            mins_places[j] = curr_raw;
                        }
                        if (delta_for_col[j] < delta) {
                            delta = delta_for_col[j];
                            next_raw = j;
                        }
                    }
                }
                for (int32_t j = 0; j <= n; ++j) {
                    if (used[j]){
                        potentials_raws[matching[j]] += delta;
                        potentials_columns[j] -= delta;
                    }
                   else{
                        delta_for_col[j] -= delta;
                    }
                }
                curr_raw = next_raw;
                flag = false;
            }
            flag = true;
            while(curr_raw || flag) {
                int32_t next_raw = mins_places[curr_raw];
                matching[curr_raw] = matching[next_raw];
                curr_raw = next_raw;
                flag = false;
            }
        }
        int32_t answer = 0;
        for (int32_t j = 1; j <= n; ++j){
            answer +=graph[matching[j]][j];
        }
        std::cout<<answer<<"\n";
        for(int32_t i =1;i<=n;++i){
            std::cout<<matching[i]<<" "<<i<<"\n";
        }
    }
