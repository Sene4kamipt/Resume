    #include <vector>
    #include <iostream>
    #include <math.h>
    #include <string>
    #include <algorithm>
    int main()
    {
        long long N;
        std::cin >> N;
        long long max_mask_size = std::pow(2, N) - 1;
        std::string input;
        std::vector<int> able_mask(max_mask_size+1, -1);
        std::vector<std::vector<char>> matrix_of_connections;
        for (int i = 0; i < N; ++i) {
            matrix_of_connections.push_back({});
            std::cin >> input;
            for (int k = 0; k < N; ++k) {
                matrix_of_connections[i].push_back(static_cast<char>(input[k]));
            }
            //std::cout << i;
        }
        //std::cout << "!";
        able_mask[0] = 0;
        int ans = 0;
        for (int mask = 1; mask <= max_mask_size; ++mask) {
            long long copy_mask_1 = mask;
            bool flag = false;
            for (int i = 0; i < N; ++i) {
                if (copy_mask_1 % 2 == 1) {
                    long long copy_mask_2 = mask/static_cast<long long>(std::pow(2,i+1));
                    for (int j = i+1; j <= N; ++j) {
                        if ((copy_mask_2 % 2 != 0) && (matrix_of_connections[i][j] == 'Y') && (able_mask[mask - std::pow(2, j) - std::pow(2, i)] != -1)) {
                            able_mask[mask] = able_mask[mask - std::pow(2, j) - std::pow(2, i)] + 2;
                            ans = std::max(ans, able_mask[mask]);
                            flag = true;
                            break;
                        }
                        copy_mask_2 /= 2;
                    }
                }
                if (flag) {
                    break;
                }
                copy_mask_1 /= 2;
            }
        }
        std::cout << ans;
    }
