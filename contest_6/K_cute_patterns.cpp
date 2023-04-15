    #include <vector>
    #include <iostream>
    #include <math.h>
    #include <string>
    std::vector<std::vector<int>> multiplication(std::vector<std::vector<int>>& matrix1, std::vector<std::vector<int>>& matrix2, int modul) {
        std::vector<std::vector<int>> answer;
        for (int i = 0; i < matrix1.size(); ++i) {
            answer.push_back({});
            for (int j = 0; j < matrix2[0].size(); ++j) {
                answer[i].push_back(0);
                for (int k = 0; k < matrix2.size(); ++k) {
                    answer[i][j] = (answer[i][j] + matrix1[i][k] * matrix2[k][j]) % modul;
                }
            }
        }
        return answer;
    }
     
    std::vector<std::vector<int>> degree(std::vector<std::vector<int>>& matrix, long long deg, int modul) {
        if (deg == 1) return matrix;
        if (deg % 2 == 0) {
            std::vector<std::vector<int>> ans = multiplication(matrix, matrix, modul);
            return degree(ans, deg / 2, modul);
        }
        else {
            std::vector<std::vector<int>> ans = degree(matrix, deg - 1, modul);
            return multiplication(matrix, ans, modul);
        }
    }
     
    void creating_matrix(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& matrix_ans, int max_mask_size, int m, long long n) {
        for (int i = 0; i <= max_mask_size; ++i) {
            for (int j = i; j <= max_mask_size; ++j) {
                int j_copy, i_copy;
                j_copy = j;
                i_copy = i;
                for (int k = 0; k < m - 1; ++k) {
                    if ((n >= 2) && (m >= 2)) {
                        if ((i_copy % 2 == 0) && ((i_copy / 2) % 2 == 0) && (j_copy % 2 == 0) && ((j_copy / 2) % 2 == 0)) {
                            matrix[i][j] = 0;
                            matrix[j][i] = 0;
                            matrix_ans[i][j] = 0;
                            matrix_ans[j][i] = 0;
                            break;
                        }
                        if ((i_copy % 2 == 1) && ((i_copy / 2) % 2 == 1) && (j_copy % 2 == 1) && ((j_copy / 2) % 2 == 1)) {
                            matrix_ans[i][j] = 0;
                            matrix_ans[j][i] = 0;
                            matrix[i][j] = 0;
                            matrix[j][i] = 0;
                            break;
                        }
                    }
                    i_copy /= 2;
                    j_copy /= 2;
                }
            }
        }
    }
     
    int main()
    {
        int Number_Test, modul, m;
        long long n;
        std::cin >> Number_Test;
        for (int test = 0; test < Number_Test; ++test) {
            std::cin >> n >> m >> modul;
            if (m == 1) {
                std::string bit_n;
                while (n != 0) {
                    if (n % 2 == 0) {
                        bit_n = "0" + bit_n;
                    }
                    else {
                        bit_n = "1" + bit_n;
                    }
                    n /= 2;
                }
                long long answer = 2;
                for (int i = 1; i < bit_n.size(); ++i) {
                    answer = (answer * answer) % modul;
                    if (bit_n[i] == '1') {
                        answer = (answer * 2) % modul;
                    }
                }
                std::cout << answer % modul << std::endl;
                continue;
            }
            if (n == 1) {
                std::cout <<static_cast<long long>(std::pow(2,m)) % modul << std::endl;
                continue;
            }
            int max_mask_size = std::pow(2, m) - 1;
            std::vector<std::vector<int>> matrix(max_mask_size + 1, std::vector<int>(max_mask_size + 1, 1));
            std::vector<std::vector<int>> matrix_ans(max_mask_size + 1, std::vector<int>(max_mask_size + 1, 1));
            creating_matrix(matrix, matrix_ans, max_mask_size, m, n);
            std::string bit_n;
            long long n_cp = n;
            --n;
            while (n != 0) {
                if (n % 2 == 0) {
                    bit_n = "0" + bit_n;
                }
                else {
                    bit_n = "1" + bit_n;
                }
                n /= 2;
            }
            for (int i = 1; i < bit_n.size(); ++i) {
                matrix_ans = multiplication(matrix_ans, matrix_ans, modul);
                if (bit_n[i] == '1') {
                    matrix_ans = multiplication(matrix, matrix_ans, modul);
                }
            }
            {int ans = 0;
            for (int i = 0; i < max_mask_size + 1; ++i) {
                for (int j = 0; j < max_mask_size + 1; ++j) {
                    ans = (ans + matrix_ans[i][j]) % modul;
                }
            }
            std::cout << ans << '\n'; }
            //for (int i = 0; i < max_mask_size + 1; ++i) {
                //for (int j = 0; j < max_mask_size + 1; ++j) {
                    //std::cout << matrix[i][j]<<" ";
                //}
                //std::cout << std::endl;
            //}
        }
    }
